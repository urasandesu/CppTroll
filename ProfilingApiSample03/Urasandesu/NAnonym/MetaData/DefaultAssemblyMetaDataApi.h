#pragma once
#ifndef URASANDESU_NANONYM_METADATA_DEFAULTASSEMBLYMETADATAAPI_H
#define URASANDESU_NANONYM_METADATA_DEFAULTASSEMBLYMETADATAAPI_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    struct DefaultAssemblyMetaDataApi
    {        
        typedef IMetaDataImport2 IImport;
        static IID const IID_IImport;
        CComPtr<IImport> Import;
        typedef IMetaDataAssemblyImport IAssemblyImport;
        static IID const IID_IAssemblyImport;
        CComPtr<IAssemblyImport> AssemblyImport;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_DEFAULTASSEMBLYMETADATAAPI_H