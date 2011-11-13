#pragma once
#ifndef URASANDESU_CPPANONYM_METADATA_OPCODES_H
#define URASANDESU_CPPANONYM_METADATA_OPCODES_H

namespace Urasandesu { namespace CppAnonym { namespace MetaData {

namespace OpCodes {

    enum Types_ {
        #define OPDEF(canonicalName, stringName, stackBehaviour0, stackBehaviour1, \
                      operandParams, opcodeKind, length, byte1, byte2, controlFlow) \
                      canonicalName,
        #include "opcode.def"
        #undef  OPDEF
        CEE_COUNT,
        CEE_UNREACHED
    };
    
    struct CEncoding {
        BYTE byte1;
        BYTE byte2;
    };

    CEncoding const Encodings[] = {
        #define OPDEF(canonicalName, stringName, stackBehaviour0, stackBehaviour1, \
                      operandParams, opcodeKind, length, byte1, byte2, controlFlow) \
                      { byte1, byte2 },
        #include "opcode.def"
        #undef  OPDEF
        { 0, 0 },
        { 0, 0 }
    };

}   // namespace OpCodes

}}}   // namespace Urasandesu { namespace CppAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_CPPANONYM_METADATA_OPCODES_H