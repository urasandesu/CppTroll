

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Sat May 21 11:41:00 2011
 */
/* Compiler settings for .\MetaDataApiSample01.idl:
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

MIDL_DEFINE_GUID(IID, IID_IAppDomainGen,0xCB372775,0xEF3B,0x4D44,0xB0,0x33,0xCC,0x66,0x38,0xC3,0xAB,0x55);


MIDL_DEFINE_GUID(IID, IID_IAssemblyGen,0x940B2252,0xDB28,0x414D,0xA6,0x15,0x49,0xF7,0xE7,0xB1,0xEF,0xD0);


MIDL_DEFINE_GUID(IID, IID_IAssemblyGenCollection,0x8DC18C9B,0x60C7,0x415C,0xAD,0x30,0x2B,0x09,0xE5,0x66,0x54,0xDB);


MIDL_DEFINE_GUID(IID, LIBID_MetaDataApiSample01Lib,0x300EAE93,0x937E,0x4B29,0xA0,0x2A,0x29,0xFB,0x75,0x32,0x8E,0xC4);


MIDL_DEFINE_GUID(CLSID, CLSID_AppDomainGen,0x965DB760,0xA27B,0x4592,0x8A,0x32,0x23,0xF4,0xE2,0x2E,0xB1,0x67);


MIDL_DEFINE_GUID(CLSID, CLSID_AssemblyGen,0x6D2E93D6,0x6364,0x4FA7,0x90,0xCF,0xE7,0x86,0x1E,0x87,0x5D,0x9F);


MIDL_DEFINE_GUID(CLSID, CLSID_AssemblyGenCollection,0xFA217239,0x6436,0x4D05,0x80,0xAA,0xCF,0xAB,0x4A,0x86,0xA1,0x6F);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



