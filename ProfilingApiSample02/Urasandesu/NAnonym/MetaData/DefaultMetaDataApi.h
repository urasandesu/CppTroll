#pragma once
#ifndef URASANDESU_NANONYM_METADATA_DEFAULTMETADATAAPI_H
#define URASANDESU_NANONYM_METADATA_DEFAULTMETADATAAPI_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    struct DefaultDispenserMetaDataApi
    {        
        typedef IMetaDataDispenserEx IDispenser;
        static IID const CLSID_Dispenser;
        static IID const IID_IDispenser;
        CComPtr<IDispenser> Dispenser;
        
        inline static HRESULT CoCreateInstance(REFCLSID rclsid, 
                                             LPUNKNOWN pUnkOuter,
                                             DWORD dwClsContext, 
                                             REFIID riid, 
                                             LPVOID FAR* ppv)
        {
            return ::CoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppv);
        }
    };

    struct DefaultAssemblyMetaDataApi
    {        
        typedef IMetaDataImport2 IImport;
        static IID const IID_IImport;
        CComPtr<IImport> Import;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_DEFAULTMETADATAAPI_H