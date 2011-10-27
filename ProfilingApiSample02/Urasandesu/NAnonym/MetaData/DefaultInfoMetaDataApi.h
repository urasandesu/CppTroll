#pragma once
#ifndef URASANDESU_NANONYM_METADATA_DEFAULTINFOMETADATAAPI_H
#define URASANDESU_NANONYM_METADATA_DEFAULTINFOMETADATAAPI_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    struct DefaultInfoMetaDataApi
    {
        typedef IMetaDataDispenserEx IDispenser;
        static IID const CLSID_Dispenser;
        static IID const IID_IDispenser;
        CComPtr<IDispenser> Dispenser;
        
        static HRESULT CoCreateInstance(REFCLSID rclsid, 
                                             LPUNKNOWN pUnkOuter,
                                             DWORD dwClsContext, 
                                             REFIID riid, 
                                             LPVOID FAR* ppv);
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_DEFAULTINFOMETADATAAPI_H