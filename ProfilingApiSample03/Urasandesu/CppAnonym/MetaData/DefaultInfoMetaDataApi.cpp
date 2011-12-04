
#include "stdafx.h"

#ifndef URASANDESU_CPPANONYM_METADATA_DEFAULTINFOMETADATAAPI_H
#include <Urasandesu/CppAnonym/MetaData/DefaultInfoMetaDataApi.h>
#endif

namespace Urasandesu { namespace CppAnonym { namespace MetaData {

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

}}}   // namespace Urasandesu { namespace CppAnonym { namespace MetaData {
