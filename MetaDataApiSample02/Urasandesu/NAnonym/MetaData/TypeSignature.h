#pragma once
#ifndef URASANDESU_NANONYM_METADATA_TYPESIGNATURE_H
#define URASANDESU_NANONYM_METADATA_TYPESIGNATURE_H

#ifndef URASANDESU_NANONYM_SIMPLEHEAP_H
#include "Urasandesu/NAnonym/SimpleHeap.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    struct TypeSignature
    {
        TypeSignature() : 
            Type(ELEMENT_TYPE_END), 
            Token(mdTokenNil),
            IsArray(false),
            Rank(0),
            IsPinned(false),
            IsPointer(false),
            IsByRef(false)
        { }

        CorElementType Type;
        mdToken Token;
        bool IsArray;
        ULONG Rank;
        std::vector<ULONG> Sizes;
        std::vector<ULONG> Lowers;
        bool IsPinned;
        bool IsPointer;
        bool IsByRef;
    };
    typedef SimpleHeap<TypeSignature> TypeSignatureHeap;

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_TYPESIGNATURE_H