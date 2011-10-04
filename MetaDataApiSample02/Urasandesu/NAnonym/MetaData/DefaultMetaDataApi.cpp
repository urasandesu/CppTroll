
#include "stdafx.h"

#ifndef URASANDESU_NANONYM_METADATA_DEFAULTMETADATAAPI_H
#include "Urasandesu/NAnonym/MetaData/DefaultMetaDataApi.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    IID const DefaultMetaDataApi::CLSID_Dispenser = CLSID_CorMetaDataDispenser;
    IID const DefaultMetaDataApi::IID_IDispenser = IID_IMetaDataDispenserEx;
    IID const DefaultMetaDataApi::IID_IImport = IID_IMetaDataImport2;

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {
