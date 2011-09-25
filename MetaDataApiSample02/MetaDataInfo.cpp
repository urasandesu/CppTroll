// MetaDataInfo.cpp : CMetaDataInfo の実装

#include "stdafx.h"
#include "MetaDataInfo.h"


// CMetaDataInfo

STDMETHODIMP CMetaDataInfo::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMetaDataInfo
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CMetaDataInfo::SystemError(DWORD errorNo, LPCSTR filePath, INT line)
{
    using boost::system::system_category;
    using std::wostringstream;
    using Urasandesu::NAnonym::SystemError;

    wostringstream msg;
    msg << SystemError(errorNo, system_category()).GetBSTRMessage().m_str;
    msg << ", File: " << filePath;
    msg << ", Line: " << line;
    return Error(msg.str().c_str());
}

HRESULT CMetaDataInfo::COMError(HRESULT hr, LPCSTR filePath, INT line)
{
    using std::wostringstream;

    wostringstream msg;
    msg << _com_error(hr).ErrorMessage();
    msg << ", File: " << filePath;
    msg << ", Line: " << line;
    return Error(msg.str().c_str());
}

HRESULT CMetaDataInfo::GetTypeSignature(PCCOR_SIGNATURE &pSigBlob, 
                                   Urasandesu::NAnonym::MetaData::TypeSignature* pTypeSig)
{
    using namespace std;
    HRESULT hr = E_FAIL;
    
    pSigBlob += ::CorSigUncompressElementType(pSigBlob, &pTypeSig->Type);
    switch (pTypeSig->Type)
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
            pSigBlob += ::CorSigUncompressToken(pSigBlob, &pTypeSig->Token); 
            break;
        case ELEMENT_TYPE_SZARRAY:     
            pTypeSig->IsArray = true;
            pTypeSig->Rank = 1;
            hr = GetTypeSignature(pSigBlob, pTypeSig);
            if (FAILED(hr)) 
                return COMError(hr, __FILE__, __LINE__);
            break;
        case ELEMENT_TYPE_ARRAY:
            {    
                pTypeSig->IsArray = true;
                pSigBlob += ::CorSigUncompressData(pSigBlob, &pTypeSig->Rank);
                _ASSERTE(0 < pTypeSig->Rank);
                hr = GetTypeSignature(pSigBlob, pTypeSig);
                if (FAILED(hr)) 
                    return COMError(hr, __FILE__, __LINE__);
                
                
                ULONG sizesSize = 0;
                pSigBlob += ::CorSigUncompressData(pSigBlob, &sizesSize);
                _ASSERTE(sizesSize <= pTypeSig->Rank);
                
                for (ULONG i = 0; i < sizesSize; ++i)
                {
                    ULONG size = 0;
                    pSigBlob += ::CorSigUncompressData(pSigBlob, &size);
                    pTypeSig->Sizes.push_back(size);
                }
                
                
                ULONG lowersSize = 0;
                pSigBlob += ::CorSigUncompressData(pSigBlob, &lowersSize);
                _ASSERTE(lowersSize <= pTypeSig->Rank);
                
                for (ULONG i = 0; i < lowersSize; ++i)
                {
                    ULONG lower = 0;
                    pSigBlob += ::CorSigUncompressData(pSigBlob, &lower);
                    pTypeSig->Lowers.push_back(lower);
                }
            }
            break;    
        case ELEMENT_TYPE_PINNED:
            pTypeSig->IsPinned = true;
            hr = GetTypeSignature(pSigBlob, pTypeSig);
            if (FAILED(hr)) 
                return COMError(hr, __FILE__, __LINE__);
            break;    
        case ELEMENT_TYPE_PTR:   
            pTypeSig->IsPointer = true;
            hr = GetTypeSignature(pSigBlob, pTypeSig);
            if (FAILED(hr)) 
                return COMError(hr, __FILE__, __LINE__);
            break;    
        case ELEMENT_TYPE_BYREF:
            pTypeSig->IsByRef = true;
            hr = GetTypeSignature(pSigBlob, pTypeSig);   
            if (FAILED(hr)) 
                return COMError(hr, __FILE__, __LINE__);
            break;    
        case ELEMENT_TYPE_END:    
        case ELEMENT_TYPE_SENTINEL:    
        default:
            break;                                                                  
    }
    return S_OK;
}

HRESULT CMetaDataInfo::GetMethodDef(mdMethodDef mdmd, CComPtr<IMetaDataImport2>& pImp)
{
    using namespace std;
    using boost::format;
    using Urasandesu::NAnonym::MetaData::MethodDefSignature;
    using Urasandesu::NAnonym::MetaData::TypeSignature;
    HRESULT hr = E_FAIL;
    
    mdTypeDef mdtd = mdTypeDefNil;
    PCCOR_SIGNATURE pSigBlob = NULL;
    ULONG sigBlobSize = 0;
    hr = pImp->GetMethodProps(mdmd, &mdtd, 0, 0, 0, 0, &pSigBlob, &sigBlobSize, 0, 0);
    if (FAILED(hr)) 
        return COMError(hr, __FILE__, __LINE__);
    
    MethodDefSignature sig;
    
    pSigBlob += ::CorSigUncompressData(pSigBlob, &sig.CallingConversion);
    cout << format("Calling Conversion: 0x%|1$08X|") % sig.CallingConversion << endl;        

    pSigBlob += ::CorSigUncompressData(pSigBlob, &sig.ParamerCount);
    cout << format("Parameter Count: 0x%|1$08X|") % sig.ParamerCount << endl;
    
    sig.TypeSignatureFactory.New(&sig.ReturnTypeSignature);
    hr = GetTypeSignature(pSigBlob, sig.ReturnTypeSignature);
    if (FAILED(hr)) 
        return COMError(hr, __FILE__, __LINE__);
    cout << format("Return Type: 0x%|1$08X|") % sig.ReturnTypeSignature->Type << endl;

    cout << "Parameter Types" << endl;        
    for (ULONG i = 0; i < sig.ParamerCount; ++i)   
    {
        TypeSignature *pTypeSig;
        sig.TypeSignatureFactory.New(&pTypeSig);
        hr = GetTypeSignature(pSigBlob, pTypeSig);
        if (FAILED(hr)) 
            return COMError(hr, __FILE__, __LINE__);
        sig.ParameterTypeSignatures.push_back(pTypeSig);
        cout << format("  Type: 0x%|1$08X|") % pTypeSig->Type << endl;
    }
    return S_OK;
}

HRESULT CMetaDataInfo::GetCustomAttribute(mdCustomAttribute mdca, CComPtr<IMetaDataImport2>& pImp)
{
    using namespace std;
    using boost::format;
    HRESULT hr = E_FAIL;
    
    mdToken mdtObj = mdTokenNil;
    mdToken mdtType = mdTokenNil;
    void const *pBlob = NULL;
    ULONG blobSize = 0;
    hr = pImp->GetCustomAttributeProps(mdca, &mdtObj, &mdtType, &pBlob, &blobSize);
    if (FAILED(hr)) 
        return COMError(hr, __FILE__, __LINE__);
    
    cout << format("Target: 0x%|1$08X|") % mdtObj << endl;
    cout << format(".ctor: 0x%|1$08X|") % mdtType << endl;
    hr = GetMethodDef(mdtType, pImp);
    if (FAILED(hr)) 
        return COMError(hr, __FILE__, __LINE__);

    cout << "Blob: ";
    for (BYTE const *i = reinterpret_cast<BYTE*>(const_cast<void*>(pBlob)), 
                    *i_end = i + blobSize; 
         i != i_end; 
         ++i)
    {
        cout << format("%|1$02X|") % static_cast<INT>(*i) << " ";
    }
    cout << endl;
    return S_OK;
}

HRESULT CMetaDataInfo::EnumCustomAttributes(mdToken mdt, CComPtr<IMetaDataImport2>& pImp)
{
    using namespace std;
    using boost::format;
    using boost::array;
    HRESULT hr = E_FAIL;

    HCORENUM hcaEnum = NULL;
    array<mdTypeRef, 10> mdtrs;
    ULONG count = 0;

    BOOST_SCOPE_EXIT((hcaEnum)(pImp))
    {
        pImp->CloseEnum(hcaEnum);
    }
    BOOST_SCOPE_EXIT_END

    while(SUCCEEDED(hr = pImp->EnumCustomAttributes(&hcaEnum, mdt, 0, mdtrs.c_array(), 
                                                    mdtrs.size(), &count)) && 
          0 < count)
    {
        for (ULONG i = 0; i < count; ++i)
        {
            cout << format("CustomAttribute: 0x%|1$08X|") % mdtrs[i] << endl;
            hr = GetCustomAttribute(mdtrs[i], pImp);
            if (FAILED(hr)) 
                return COMError(hr, __FILE__, __LINE__);
        }
    }
    return S_OK;    
}

HRESULT CMetaDataInfo::EnumMethods(mdToken mdt, CComPtr<IMetaDataImport2>& pImp)
{
    using namespace std;
    using boost::format;
    using boost::array;
    HRESULT hr = E_FAIL;

    HCORENUM hmdEnum = NULL;
    array<mdMethodDef, 10> mdmds;
    ULONG count = 0;
    
    BOOST_SCOPE_EXIT((hmdEnum)(pImp))
    {
        pImp->CloseEnum(hmdEnum);
    }
    BOOST_SCOPE_EXIT_END

    while (SUCCEEDED(hr = pImp->EnumMethods(&hmdEnum, mdt, mdmds.c_array(), mdmds.size(), 
                                            &count)) && 
           0 < count)
    {
        for (ULONG i = 0; i < count; ++i)
        {
            cout << format("MethodDef: 0x%|1$08X|") % mdmds[i] << endl;
            hr = EnumCustomAttributes(mdmds[i], pImp);
            if (FAILED(hr)) 
                return COMError(hr, __FILE__, __LINE__);
        }
    }
    return S_OK;
}

STDMETHODIMP CMetaDataInfo::Get(BSTR fileName)
{
    using namespace std;
    using boost::format;
    using boost::array;
    HRESULT hr = E_FAIL;
    
    CComPtr<IMetaDataDispenserEx> pDisp;
    hr = ::CoCreateInstance(CLSID_CorMetaDataDispenser, NULL, CLSCTX_INPROC_SERVER, 
                            IID_IMetaDataDispenserEx, 
                            reinterpret_cast<void**>(&pDisp));
    if (FAILED(hr)) 
        return COMError(hr, __FILE__, __LINE__);

    CComPtr<IMetaDataImport2> pImp;
    hr = pDisp->OpenScope(fileName, ofRead, IID_IMetaDataImport2, 
                          reinterpret_cast<IUnknown**>(&pImp));
    if (FAILED(hr)) 
        return COMError(hr, __FILE__, __LINE__);

    HCORENUM htdEnum = NULL;
    array<mdTypeDef, 10> mdtds;
    ULONG count = 0;

    BOOST_SCOPE_EXIT((htdEnum)(pImp))
    {
        pImp->CloseEnum(htdEnum);
    }
    BOOST_SCOPE_EXIT_END
    
    while (SUCCEEDED(hr = pImp->EnumTypeDefs(&htdEnum, mdtds.c_array(), mdtds.size(), 
                                             &count)) && 
           0 < count)
    {
        for (ULONG i = 0; i < count; ++i)
        {
            cout << format("TypeDef: 0x%|1$08X|") % mdtds[i] << endl;
            hr = EnumCustomAttributes(mdtds[i], pImp);
            if (FAILED(hr)) 
                return COMError(hr, __FILE__, __LINE__);
            hr = EnumMethods(mdtds[i], pImp);
            if (FAILED(hr)) 
                return COMError(hr, __FILE__, __LINE__);
        }
    }

    return S_OK;
}
