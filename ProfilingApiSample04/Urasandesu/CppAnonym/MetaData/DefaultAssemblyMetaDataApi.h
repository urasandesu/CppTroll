#pragma once
#ifndef URASANDESU_CPPANONYM_METADATA_DEFAULTASSEMBLYMETADATAAPI_H
#define URASANDESU_CPPANONYM_METADATA_DEFAULTASSEMBLYMETADATAAPI_H

namespace Urasandesu { namespace CppAnonym { namespace MetaData {

    struct DefaultAssemblyMetaDataApi
    {        
        typedef IMetaDataImport2 IImport;
        static IID const IID_IImport;
        ATL::CComPtr<IImport> Import;
        typedef IMetaDataAssemblyImport IAssemblyImport;
        static IID const IID_IAssemblyImport;
        ATL::CComPtr<IAssemblyImport> AssemblyImport;
    };

}}}   // namespace Urasandesu { namespace CppAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_CPPANONYM_METADATA_DEFAULTASSEMBLYMETADATAAPI_H