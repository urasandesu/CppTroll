#pragma once
#ifndef URASANDESU_NANONYM_METADATA_FIXEDARGARRAYSIGNATURE_H
#define URASANDESU_NANONYM_METADATA_FIXEDARGARRAYSIGNATURE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class AssemblyMetaDataApiType>
    class FixedArgSignature;

    template<class AssemblyMetaDataApiType = boost::use_default>
    class FixedArgArraySignature : public FixedArgSignature<AssemblyMetaDataApiType>
    {
    public:
        virtual ~FixedArgArraySignature() { }
        virtual bool IsArray()
        {
            return true;
        }
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_FIXEDARGARRAYSIGNATURE_H