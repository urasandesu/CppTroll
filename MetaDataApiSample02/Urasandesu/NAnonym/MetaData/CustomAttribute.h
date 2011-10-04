#pragma once
#ifndef URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTE_H
#define URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTE_H

#ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H
#include "Urasandesu/NAnonym/MetaData/IMetaDataOperable.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_ITOKENIZABLE_H
#include "Urasandesu/NAnonym/MetaData/ITokenizable.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class MetaDataApiType>
    class Method;

    template<class TokenizableType, class MetaDataApiType = boost::use_default>
    class CustomAttribute : public IMetaDataOperable<MetaDataApiType>, public ITokenizable
    {
    public:
        TokenizableType *Target;
        
        CustomAttribute() : m_pMethod(NULL) { }
    
        Method<MetaDataApiType> *GetConstructor()
        {
            FillPropertiesIfNecessary();
            return m_pMethod;
        }
    
    private:
        void FillPropertiesIfNecessary()
        {
            if (!HasGotProperties())
                FillProperties();
        }
        
        bool HasGotProperties()
        {
            return m_pMethod != NULL;
        }
        
        void FillProperties()
        {
            HRESULT hr = E_FAIL;
            
            mdToken mdtTarget = mdTokenNil;
            mdToken mdtCtor = mdTokenNil;
            void const *pBlob = NULL;
            ULONG blobSize = 0;
            hr = m_pApi->Import->GetCustomAttributeProps(GetToken(), &mdtTarget, &mdtCtor, &pBlob, &blobSize);
            if (FAILED(hr)) 
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            hr = m_pRuntime->GetHeap<Method<MetaDataApiType>>()->New(&m_pMethod);
            if (FAILED(hr)) 
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));
            
            m_pMethod->SetToken(mdtCtor);

            //cout << "Blob: ";
            //for (BYTE const *i = reinterpret_cast<BYTE*>(const_cast<void*>(pBlob)), 
            //                *i_end = i + blobSize; 
            //     i != i_end; 
            //     ++i)
            //{
            //    cout << format("%|1$02X|") % static_cast<INT>(*i) << " ";
            //}
            //cout << endl;
            //return S_OK;
        }
        
        Method<MetaDataApiType> *m_pMethod;    
    };


}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTE_H