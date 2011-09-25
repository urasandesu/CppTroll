#pragma once
#ifndef URASANDESU_NANONYM_METADATA_METHODDEFSIGNATURE_H
#define URASANDESU_NANONYM_METADATA_METHODDEFSIGNATURE_H

#ifndef URASANDESU_NANONYM_METADATA_TYPESIGNATURE_H
#include "Urasandesu/NAnonym/MetaData/TypeSignature.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    struct MethodDefSignature
    {
        ULONG CallingConversion;
        ULONG ParamerCount;

        TypeSignatureHeap TypeSignatureFactory;
        
        TypeSignature* ReturnTypeSignature;        
        std::vector<TypeSignature*> ParameterTypeSignatures;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_METHODDEFSIGNATURE_H