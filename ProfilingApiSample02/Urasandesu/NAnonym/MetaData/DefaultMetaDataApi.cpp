
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_METADATA_DEFAULTMETADATAAPI_H
#include <Urasandesu/NAnonym/MetaData/DefaultMetaDataApi.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    IID const DefaultDispenserMetaDataApi::CLSID_Dispenser = CLSID_CorMetaDataDispenser;
    IID const DefaultDispenserMetaDataApi::IID_IDispenser = IID_IMetaDataDispenserEx;
    IID const DefaultAssemblyMetaDataApi::IID_IImport = IID_IMetaDataImport2;

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {
