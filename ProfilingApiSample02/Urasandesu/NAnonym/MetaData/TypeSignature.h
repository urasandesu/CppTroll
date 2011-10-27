#pragma once
#ifndef URASANDESU_NANONYM_METADATA_TYPESIGNATURE_H
#define URASANDESU_NANONYM_METADATA_TYPESIGNATURE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class ATL_NO_VTABLE IMetaDataOperable;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class TypeSignature : public IMetaDataOperable<AssemblyMetaDataApiType>
    {
    public:
        TypeSignature() : 
            Blob(NULL),
            m_pParsedBlob(NULL),
            m_type(ELEMENT_TYPE_END), 
            m_token(mdTokenNil),
            m_rank(-1),
            m_pSizes(NULL),
            m_pLowers(NULL),
            m_isArray(false),
            m_isPinned(false),
            m_isPointer(false),
            m_isByRef(false)
        { 
        }

        PCCOR_SIGNATURE Blob;

        PCCOR_SIGNATURE GetParsedBlob()
        {
            FillPropertiesIfNecessary();
            return m_pParsedBlob;
        }
        
        CorElementType GetType()
        {
            FillPropertiesIfNecessary();
            return m_type;
        }
        
        mdToken GetToken()
        {
            FillPropertiesIfNecessary();
            return m_token;
        }
        
        bool IsArray()
        {
            FillPropertiesIfNecessary();
            return m_isArray;
        }
        
        ULONG GetRank()
        {
            FillPropertiesIfNecessary();
            return m_rank;
        }
        
        std::vector<ULONG> *GetSizes()
        {
            FillPropertiesIfNecessary();
            return m_pSizes;
        }
        
        std::vector<ULONG> *GetLowers()
        {
            FillPropertiesIfNecessary();
            return m_pLowers;
        }
        
        bool IsPinned()
        {
            FillPropertiesIfNecessary();
            return m_isPinned;
        }
        
        bool IsPointer()
        {
            FillPropertiesIfNecessary();
            return m_isPointer;
        }
        
        bool IsByRef()
        {
            FillPropertiesIfNecessary();
            return m_isByRef;
        }

    private:
        void FillPropertiesIfNecessary()
        {
            if (!HasGotProperties())
                FillProperties();
        }
        
        bool HasGotProperties()
        {
            return m_type != ELEMENT_TYPE_END && m_pParsedBlob != NULL;
        }
        
        void GetTypeSignature(PCCOR_SIGNATURE &pSigBlob, TypeSignature<AssemblyMetaDataApiType> *this_)
        {
            pSigBlob += ::CorSigUncompressElementType(pSigBlob, &this_->m_type);
            switch (this_->m_type)
            {
	            case ELEMENT_TYPE_VOID:
	            case ELEMENT_TYPE_BOOLEAN:	
	            case ELEMENT_TYPE_CHAR:
	            case ELEMENT_TYPE_I1:
	            case ELEMENT_TYPE_U1:
	            case ELEMENT_TYPE_I2:
	            case ELEMENT_TYPE_U2:
	            case ELEMENT_TYPE_I4:
	            case ELEMENT_TYPE_U4:
	            case ELEMENT_TYPE_I8:
	            case ELEMENT_TYPE_U8:
	            case ELEMENT_TYPE_R4:
	            case ELEMENT_TYPE_R8:
	            case ELEMENT_TYPE_U:
	            case ELEMENT_TYPE_I:
	            case ELEMENT_TYPE_OBJECT:
	            case ELEMENT_TYPE_STRING:
	            case ELEMENT_TYPE_TYPEDBYREF:
                    // do nothing
		            break;				       
                case ELEMENT_TYPE_CLASS:    
                case ELEMENT_TYPE_VALUETYPE:
                case ELEMENT_TYPE_CMOD_REQD:
                case ELEMENT_TYPE_CMOD_OPT:
                    pSigBlob += ::CorSigUncompressToken(pSigBlob, &this_->m_token); 
                    break;
                case ELEMENT_TYPE_SZARRAY:     
                    this_->m_isArray = true;
                    this_->m_rank = 1;
                    GetTypeSignature(pSigBlob, this_);
                    break;
                case ELEMENT_TYPE_ARRAY:
                    {    
                        this_->m_isArray = true;
                        pSigBlob += ::CorSigUncompressData(pSigBlob, &this_->m_rank);
                        _ASSERTE(0 < this_->m_rank);
                        GetTypeSignature(pSigBlob, this_);
                        
                        
                        ULONG sizesSize = 0;
                        pSigBlob += ::CorSigUncompressData(pSigBlob, &sizesSize);
                        _ASSERTE(sizesSize <= this_->m_rank);
                        
                        this_->m_pSizes = this_->m_pAsm->GetHeap<std::vector<ULONG>>()->New();
                        for (ULONG i = 0; i < sizesSize; ++i)
                        {
                            ULONG size = 0;
                            pSigBlob += ::CorSigUncompressData(pSigBlob, &size);
                            this_->m_pSizes->push_back(size);
                        }
                        
                        
                        ULONG lowersSize = 0;
                        pSigBlob += ::CorSigUncompressData(pSigBlob, &lowersSize);
                        _ASSERTE(lowersSize <= this_->m_rank);
                        
                        this_->m_pLowers = this_->m_pAsm->GetHeap<std::vector<ULONG>>()->New();
                        for (ULONG i = 0; i < lowersSize; ++i)
                        {
                            ULONG lower = 0;
                            pSigBlob += ::CorSigUncompressData(pSigBlob, &lower);
                            this_->m_pLowers->push_back(lower);
                        }
                    }
                    break;    
                case ELEMENT_TYPE_PINNED:
                    this_->m_isPinned = true;
                    GetTypeSignature(pSigBlob, this_);
                    break;    
                case ELEMENT_TYPE_PTR:   
                    this_->m_isPointer = true;
                    GetTypeSignature(pSigBlob, this_);
                    break;    
                case ELEMENT_TYPE_BYREF:
                    this_->m_isByRef = true;
                    GetTypeSignature(pSigBlob, this_);   
                    break;    
                case ELEMENT_TYPE_END:    
                case ELEMENT_TYPE_SENTINEL:    
                default:
                    break;                                                                  
            }
        }
        
        void FillProperties()
        {
            m_pParsedBlob = Blob;
            GetTypeSignature(m_pParsedBlob, this);    
        }
        
        PCCOR_SIGNATURE m_pParsedBlob;
        CorElementType m_type;
        mdToken m_token;
        ULONG m_rank;
        std::vector<ULONG> *m_pSizes;
        std::vector<ULONG> *m_pLowers;
        #pragma pack(push, 1)
        bool m_isArray;
        bool m_isPinned;
        bool m_isPointer;
        bool m_isByRef;
        #pragma pack(pop)
    };


}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_TYPESIGNATURE_H