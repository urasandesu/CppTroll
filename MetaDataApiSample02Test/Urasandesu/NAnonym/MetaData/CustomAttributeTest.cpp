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

#ifndef URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTESIGNATURE_H
#include <Urasandesu/NAnonym/MetaData/CustomAttributeSignature.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_FIXEDARGSIGNATURE_H
#include <Urasandesu/NAnonym/MetaData/FixedArgSignature.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_FIXEDARGELEMSIGNATURE_H
#include <Urasandesu/NAnonym/MetaData/FixedArgElemSignature.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_ELEMSIGNATURE_H
#include <Urasandesu/NAnonym/MetaData/ElemSignature.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_SIMPLEORENUMELEMSIGNATURE_H
#include <Urasandesu/NAnonym/MetaData/SimpleOrEnumElemSignature.h>
#endif

#ifndef URASANDESU_NANONYM_NANONYMCOMEXCEPTION_H
#include "Urasandesu/NAnonym/NAnonymCOMException.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_METHODDEFSIGNATURE_H
#include <Urasandesu/NAnonym/MetaData/MethodDefSignature.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_TYPESIGNATURE_H
#include <Urasandesu/NAnonym/MetaData/TypeSignature.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_NAMEDARGSIGNATURE_H
#include <Urasandesu/NAnonym/MetaData/NamedArgSignature.h>
#endif

#ifndef URASANDESU_NANONYM_METADATA_STRINGORTYPEELEMSIGNATURE_H
#include <Urasandesu/NAnonym/MetaData/StringOrTypeElemSignature.h>
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
        EXPECT_EQ(0x06000005, methodCA.GetConstructor()->GetToken());

        CustomAttributeSignature<> *pCASig = methodCA.GetSignature();
        cout << format("Prologue: 0x%|1$04X|") % pCASig->GetPrologue() << endl;
        EXPECT_EQ(0x0001, pCASig->GetPrologue());
        
        std::vector<FixedArgSignature<>*> *pFixedArgSigs = pCASig->GetFixedArgSignatures();
        EXPECT_EQ(2, pFixedArgSigs->size());
        int fixedArgSigsCount = 0;
        for (std::vector<FixedArgSignature<>*>::iterator i = pFixedArgSigs->begin(), 
                                                         i_end = pFixedArgSigs->end(); 
             i != i_end; 
             ++i)
        {
            switch (fixedArgSigsCount++)
            {
                case 0:
                    {
                        EXPECT_FALSE((*i)->IsArray());
                        FixedArgElemSignature<> *pFixedArgElemSig = dynamic_cast<FixedArgElemSignature<>*>(*i);
                        EXPECT_TRUE(pFixedArgElemSig != NULL);
                        
                        ElemSignature<> *pElemSig = pFixedArgElemSig->GetElem();
                        EXPECT_TRUE(pElemSig != NULL);
                        EXPECT_EQ(ELEMENT_TYPE_I4, pElemSig->GetType());
                        
                        typedef ElemSignatureTrait<ELEMENT_TYPE_I4_TYPE> con_elem_sig_trait;
                        con_elem_sig_trait::type *pConElemSig = con_elem_sig_trait::ToConcrete(pElemSig);
                        EXPECT_TRUE(pConElemSig != NULL);
                        
                        cout << format("Constructor Arg[0]: 0x%|1$08X|") % pConElemSig->GetValue() << endl;
                        EXPECT_EQ(0x02000003, pConElemSig->GetValue());
                    }
                    break;
                case 1:
                    {
                        EXPECT_FALSE((*i)->IsArray());
                        FixedArgElemSignature<> *pFixedArgElemSig = dynamic_cast<FixedArgElemSignature<>*>(*i);
                        EXPECT_TRUE(pFixedArgElemSig != NULL);
                        
                        ElemSignature<> *pElemSig = pFixedArgElemSig->GetElem();
                        EXPECT_TRUE(pElemSig != NULL);
                        EXPECT_EQ(ELEMENT_TYPE_I4, pElemSig->GetType());
                        
                        typedef ElemSignatureTrait<ELEMENT_TYPE_I4_TYPE> con_elem_sig_trait;
                        con_elem_sig_trait::type *pConElemSig = con_elem_sig_trait::ToConcrete(pElemSig);
                        EXPECT_TRUE(pConElemSig != NULL);
                        
                        cout << format("Constructor Arg[1]: 0x%|1$08X|") % pConElemSig->GetValue() << endl;
                        EXPECT_EQ(0x06000003, pConElemSig->GetValue());
                    }
                    break;
                default:
                    FAIL() << "Fixed Arg signature count is too many.";
                    break;
            }
        }

        std::vector<NamedArgSignature<>*> *pNamedArgSigs = pCASig->GetNamedArgSignatures();
        EXPECT_EQ(1, pNamedArgSigs->size());
        cout << format("Named Arg Count: %|1|") % pNamedArgSigs->size() << endl;
        for (std::vector<NamedArgSignature<>*>::iterator i = pNamedArgSigs->begin(), 
                                                         i_end = pNamedArgSigs->end(); 
             i != i_end; 
             ++i)
        {
            EXPECT_EQ(SERIALIZATION_TYPE_PROPERTY, (*i)->GetKind());
            cout << format("Named Arg[0] Type: %|1|") % ((*i)->GetKind() == SERIALIZATION_TYPE_FIELD ? "Field" : "Property") << endl;

            EXPECT_EQ(ELEMENT_TYPE_STRING, (*i)->GetTypeSignature()->GetType());
            cout << format("Named Arg[0] Type signature type: 0x%|1$08X|") % (*i)->GetTypeSignature()->GetType() << endl;

            EXPECT_STREQ("Value", (*i)->GetName().c_str());
            cout << format("Named Arg[0] Name: %|1|") % (*i)->GetName().c_str() << endl;

            EXPECT_EQ(ELEMENT_TYPE_STRING, (*i)->GetTypeSignature()->GetType());

            FixedArgSignature<> *pFixedArgSig = (*i)->GetFixedArgSignature();
            EXPECT_FALSE(pFixedArgSig->IsArray());

            FixedArgElemSignature<> *pFixedArgElemSig = dynamic_cast<FixedArgElemSignature<>*>(pFixedArgSig);
            EXPECT_TRUE(pFixedArgElemSig != NULL);

            ElemSignature<> *pElemSig = pFixedArgElemSig->GetElem();
            EXPECT_TRUE(pElemSig != NULL);
            EXPECT_EQ(ELEMENT_TYPE_STRING, pElemSig->GetType());

            typedef ElemSignatureTrait<ELEMENT_TYPE_STRING_TYPE> con_elem_sig_trait;
            con_elem_sig_trait::type *pConElemSig = con_elem_sig_trait::ToConcrete(pElemSig);
            EXPECT_TRUE(pConElemSig != NULL);
            
            cout << format("Named Arg[0] Value: %|1|") % pConElemSig->GetValue() << endl;
            EXPECT_STREQ("aiueo", pConElemSig->GetValue().c_str());
        }
    }
}
