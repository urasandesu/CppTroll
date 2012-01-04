// MetaDataObject.cpp : CMetaDataObject の実装

#include "stdafx.h"
#include "MetaDataObject.h"


// CMetaDataObject

STDMETHODIMP CMetaDataObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID *arr[] = 
	{
		&IID_IMetaDataObject
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CMetaDataObject::Get(BSTR fileName)
{
    using namespace std;
    using boost::format;
    using boost::diagnostic_information;
    using namespace Urasandesu::NAnonym;
    using namespace Urasandesu::NAnonym::MetaData;
    HRESULT hr = E_FAIL;
    
    try
    {
        Runtime<> runtime;
        Assembly<> *pAsm = runtime.OpenAssembly(fileName, ofRead);
        Module<> *pMod = pAsm->GetMainModule();
        TypeEnumerator<> *pTypeEnum = pMod->EnumerateType();
        for (Type<> *pType = NULL; (pType = pTypeEnum->Next()) != NULL; )
        {
            cout << "Type: " << format("0x%|1$08X|") % pType->GetToken() << endl;
            
            CustomAttributeEnumerator<Type<>> *pTypeCAEnum = pType->EnumerateCustomAttribute();
            for (CustomAttribute<Type<>> *pTypeCA = NULL; (pTypeCA = pTypeCAEnum->Next()) != NULL; )
            {
                cout << "  Custom Attribute: " << format("0x%|1$08X|") % pTypeCA->GetToken() << endl;
                cout << "    .ctor: " << format("0x%|1$08X|") % pTypeCA->GetConstructor()->GetToken() << endl;
            }
            
            MethodEnumerator<> *pMethodEnum = pType->EnumerateMethod();
            for (Method<> *pMethod = NULL; (pMethod = pMethodEnum->Next()) != NULL; )
            {
                cout << "  Method: " << format("0x%|1$08X|") % pMethod->GetToken() << endl;
                
                CustomAttributeEnumerator<Method<>> *pMethodCAEnum = pMethod->EnumerateCustomAttribute();
                for (CustomAttribute<Method<>> *pMethodCA = NULL; (pMethodCA = pMethodCAEnum->Next()) != NULL; )
                {
                    cout << "    Custom Attribute: " << format("0x%|1$08X|") % pMethodCA->GetToken() << endl;
                    
                }
                
                MethodDefSignature<> *pMethodSig = pMethod->GetMethodSignature();
                cout << "    Signature: " << endl;
                cout << "      Calling Conversion: " << format("0x%|1$08X|") % pMethodSig->GetCallingConversion() << endl;
                cout << "      Parameter Count: " << format("0x%|1$08X|") % pMethodSig->GetParameterCount() << endl;
                cout << "      Return Type: " << format("0x%|1$08X|") % pMethodSig->GetReturnTypeSignature()->GetType() << endl;
                cout << "      Parameter Type: " << endl;
                for (vector<TypeSignature<>*>::iterator i = pMethodSig->GetParameterTypeSignatures()->begin(), 
                                                        i_end = pMethodSig->GetParameterTypeSignatures()->end();
                     i != i_end;
                     ++i)
                {
                    cout << "        Type: " << format("0x%|1$08X|") % (*i)->GetType() << endl;
                }
            }
        }
        
        return S_OK;
    }
    catch (NAnonymCOMException &e)
    {
        return Error(CComBSTR(diagnostic_information(e).c_str()));
    }
}
