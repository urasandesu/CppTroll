#include "stdafx.h"

#ifndef URASANDESU_NANONYM_METADATA_RUNTIME_H
#include <Urasandesu/NAnonym/MetaData/Runtime.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_ASSEMBLY_H
#include <Urasandesu/NAnonym/MetaData/Assembly.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_METHOD_H
#include <Urasandesu/NAnonym/MetaData/Method.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H
#include <Urasandesu/NAnonym/MetaData/IMetaDataOperable.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_ITOKENIZABLE_H
#include <Urasandesu/NAnonym/MetaData/ITokenizable.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_DEFAULTMETADATAAPI_H
#include <Urasandesu/NAnonym/MetaData/DefaultMetaDataApi.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTE_H
#include <Urasandesu/NAnonym/MetaData/CustomAttribute.h>
#endif

#ifndef URASANDESU_NANONYM_NANONYMCOMEXCEPTION_H
#include "Urasandesu/NAnonym/NAnonymCOMException.h"
#endif

namespace {

    // MetaDataApiSample02Test.exe --gtest_filter=MetaDataApiSample02TestSuite.CustomAttributeTest
    TEST(MetaDataApiSample02TestSuite, CustomAttributeTest)
    {
        using namespace std;
        using namespace boost;
        using namespace Urasandesu::NAnonym::MetaData;
        HRESULT hr = E_FAIL;

        CComPtr<IMetaDataDispenserEx> pDisp;
        ASSERT_HRESULT_SUCCEEDED(
            ::CoCreateInstance(CLSID_CorMetaDataDispenser, NULL, CLSCTX_INPROC_SERVER, 
                               IID_IMetaDataDispenserEx, reinterpret_cast<void**>(&pDisp))
        );

        CComPtr<IMetaDataImport2> pImport;
        ASSERT_HRESULT_SUCCEEDED(
            pDisp->OpenScope(L"..\\MetaDataApiSample02Target\\bin\\Debug\\MetaDataApiSample02Target.exe", 
                             ofRead, IID_IMetaDataImport2, reinterpret_cast<IUnknown**>(&pImport))
        );
        
        Runtime<> runtime;

        Assembly<> asm_;   
        DefaultAssemblyMetaDataApi api;
        api.Import = pImport;

        Method<> method;        
        method.Init(&asm_, &api);
        method.SetToken(0x06000001);
             
        Method<>::custom_attribute_type methodCA;
        methodCA.Init(&asm_, &api);
        methodCA.SetToken(0x0C000001);
        methodCA.Target = &method;
        
        cout << format("Constructor Token: 0x%|1$08X|") % methodCA.GetConstructor()->GetToken() << endl;
        
        
        SUCCEED();
    }
}
