

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Sun May 22 17:55:35 2011
 */
/* Compiler settings for .\Sample02.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IMyCache,0x324FA781,0x2E07,0x415E,0xB6,0x0B,0x93,0xD2,0xA5,0x35,0xDD,0x90);


MIDL_DEFINE_GUID(IID, IID_IPairBStrVariant,0x4C29DB1F,0xA3FA,0x47C9,0x98,0x74,0xB7,0xFF,0x64,0x86,0x4E,0xF6);


MIDL_DEFINE_GUID(IID, IID_IMyCachePrinter,0xF794302C,0xAD7E,0x4DA9,0xA0,0x00,0x79,0x4F,0xDC,0x32,0xAF,0x49);


MIDL_DEFINE_GUID(IID, LIBID_Sample02Lib,0x66E14A4E,0xF4D6,0x4EE3,0xA6,0xCB,0xEC,0xB3,0x83,0xF2,0x36,0xA0);


MIDL_DEFINE_GUID(CLSID, CLSID_MyCache,0x206584CE,0xD105,0x4FB6,0x9B,0x13,0xE6,0xFA,0x6C,0xE2,0x27,0xB9);


MIDL_DEFINE_GUID(CLSID, CLSID_PairBStrVariant,0x37C6DACC,0x3125,0x4568,0xB6,0xC5,0x0E,0xED,0x93,0x73,0xC7,0xC2);


MIDL_DEFINE_GUID(CLSID, CLSID_MyCachePrinter,0xE8A92313,0x2962,0x4844,0x80,0x86,0x51,0x20,0xA2,0x9A,0xD7,0xFF);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



