
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_METADATA_DEFAULTINFOMETADATAAPI_H
#include <Urasandesu/NAnonym/MetaData/DefaultInfoMetaDataApi.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    HRESULT DefaultInfoMetaDataApi::CoCreateInstance(REFCLSID rclsid, 
                                         LPUNKNOWN pUnkOuter,
                                         DWORD dwClsContext, 
                                         REFIID riid, 
                                         LPVOID FAR* ppv)
    {
        return ::CoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppv);
    }

    IID const DefaultInfoMetaDataApi::CLSID_Dispenser = CLSID_CorMetaDataDispenser;
    IID const DefaultInfoMetaDataApi::IID_IDispenser = IID_IMetaDataDispenserEx;

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {
