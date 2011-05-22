

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Sun May 22 18:44:45 2011
 */
/* Compiler settings for .\Sample03.idl:
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

MIDL_DEFINE_GUID(IID, IID_IMyEnumerable,0x26251BAE,0xB229,0x48DC,0x9B,0x3E,0x7C,0x9F,0x77,0xBF,0x7D,0x17);


MIDL_DEFINE_GUID(IID, IID_IMyEnumerableGenerator,0xACA95E6E,0x8AD2,0x4F69,0xBC,0x53,0xA7,0xF8,0xDC,0x8F,0x20,0xE8);


MIDL_DEFINE_GUID(IID, LIBID_Sample03Lib,0x4F3639A6,0xBF3E,0x4D50,0xBE,0xF2,0xA1,0xAF,0xF6,0xC0,0x94,0xDF);


MIDL_DEFINE_GUID(CLSID, CLSID_MyEnumerable,0x732D6B0C,0x651E,0x4D5D,0xA7,0x06,0x44,0x7D,0xDB,0x84,0xC6,0xD5);


MIDL_DEFINE_GUID(CLSID, CLSID_MyEnumerableGenerator,0xF9DAF8FA,0x8D6F,0x42C7,0x85,0xCF,0x90,0x19,0x11,0x82,0x14,0x56);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



