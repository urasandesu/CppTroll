

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Sat May 21 11:16:34 2011
 */
/* Compiler settings for .\Sample01.idl:
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

MIDL_DEFINE_GUID(IID, IID_IEmployee,0x49562FA4,0x2E88,0x44B2,0xB3,0xBC,0x95,0xE5,0xD5,0x96,0xAD,0xE1);


MIDL_DEFINE_GUID(IID, IID_IEmployeeCollection,0x45C6C575,0x91C4,0x4DB3,0x8B,0x0D,0x74,0xBD,0xDD,0xF7,0xD3,0xB4);


MIDL_DEFINE_GUID(IID, LIBID_Sample01Lib,0xE1D94705,0x9C97,0x4104,0x8B,0x97,0x89,0xA1,0xEE,0x53,0x45,0x6D);


MIDL_DEFINE_GUID(CLSID, CLSID_Employee,0x7307F922,0x2C35,0x482F,0xB8,0x87,0x96,0x41,0x7C,0x05,0x80,0xA2);


MIDL_DEFINE_GUID(CLSID, CLSID_EmployeeCollection,0xDA02B766,0x1C6A,0x4399,0x90,0x2B,0xB6,0xB2,0x74,0x75,0x28,0xC1);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



