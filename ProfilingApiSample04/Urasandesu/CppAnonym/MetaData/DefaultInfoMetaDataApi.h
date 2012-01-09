#pragma once
#ifndef URASANDESU_CPPANONYM_METADATA_DEFAULTINFOMETADATAAPI_H
#define URASANDESU_CPPANONYM_METADATA_DEFAULTINFOMETADATAAPI_H

namespace Urasandesu { namespace CppAnonym { namespace MetaData {

    struct DefaultInfoMetaDataApi
    {
        typedef IMetaDataDispenserEx IDispenser;
        static IID const CLSID_Dispenser;
        static IID const IID_IDispenser;
        ATL::CComPtr<IDispenser> Dispenser;
        
        static HRESULT CoCreateInstance(REFCLSID rclsid, 
                                             LPUNKNOWN pUnkOuter,
                                             DWORD dwClsContext, 
                                             REFIID riid, 
                                             LPVOID FAR* ppv);
    };

}}}   // namespace Urasandesu { namespace CppAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_CPPANONYM_METADATA_DEFAULTINFOMETADATAAPI_H