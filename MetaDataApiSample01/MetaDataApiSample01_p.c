

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "MetaDataApiSample01_i.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   1                                 
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _MetaDataApiSample01_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MetaDataApiSample01_MIDL_TYPE_FORMAT_STRING;

typedef struct _MetaDataApiSample01_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MetaDataApiSample01_MIDL_PROC_FORMAT_STRING;

typedef struct _MetaDataApiSample01_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } MetaDataApiSample01_MIDL_EXPR_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MetaDataApiSample01_MIDL_TYPE_FORMAT_STRING MetaDataApiSample01__MIDL_TypeFormatString;
extern const MetaDataApiSample01_MIDL_PROC_FORMAT_STRING MetaDataApiSample01__MIDL_ProcFormatString;
extern const MetaDataApiSample01_MIDL_EXPR_FORMAT_STRING MetaDataApiSample01__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAppDomainGen_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAppDomainGen_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAssemblyGen_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAssemblyGen_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAssemblyGenCollection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAssemblyGenCollection_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MetaDataApiSample01_MIDL_PROC_FORMAT_STRING MetaDataApiSample01__MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const MetaDataApiSample01_MIDL_TYPE_FORMAT_STRING MetaDataApiSample01__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IAppDomainGen, ver. 0.0,
   GUID={0xCB372775,0xEF3B,0x4D44,{0xB0,0x33,0xCC,0x66,0x38,0xC3,0xAB,0x55}} */

#pragma code_seg(".orpc")
static const unsigned short IAppDomainGen_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAppDomainGen_ProxyInfo =
    {
    &Object_StubDesc,
    MetaDataApiSample01__MIDL_ProcFormatString.Format,
    &IAppDomainGen_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAppDomainGen_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    MetaDataApiSample01__MIDL_ProcFormatString.Format,
    &IAppDomainGen_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IAppDomainGenProxyVtbl = 
{
    0,
    &IID_IAppDomainGen,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IAppDomainGen_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IAppDomainGenStubVtbl =
{
    &IID_IAppDomainGen,
    &IAppDomainGen_ServerInfo,
    7,
    &IAppDomainGen_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IAssemblyGen, ver. 0.0,
   GUID={0x940B2252,0xDB28,0x414D,{0xA6,0x15,0x49,0xF7,0xE7,0xB1,0xEF,0xD0}} */

#pragma code_seg(".orpc")
static const unsigned short IAssemblyGen_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAssemblyGen_ProxyInfo =
    {
    &Object_StubDesc,
    MetaDataApiSample01__MIDL_ProcFormatString.Format,
    &IAssemblyGen_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAssemblyGen_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    MetaDataApiSample01__MIDL_ProcFormatString.Format,
    &IAssemblyGen_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IAssemblyGenProxyVtbl = 
{
    0,
    &IID_IAssemblyGen,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IAssemblyGen_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IAssemblyGenStubVtbl =
{
    &IID_IAssemblyGen,
    &IAssemblyGen_ServerInfo,
    7,
    &IAssemblyGen_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IAssemblyGenCollection, ver. 0.0,
   GUID={0x8DC18C9B,0x60C7,0x415C,{0xAD,0x30,0x2B,0x09,0xE5,0x66,0x54,0xDB}} */

#pragma code_seg(".orpc")
static const unsigned short IAssemblyGenCollection_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAssemblyGenCollection_ProxyInfo =
    {
    &Object_StubDesc,
    MetaDataApiSample01__MIDL_ProcFormatString.Format,
    &IAssemblyGenCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAssemblyGenCollection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    MetaDataApiSample01__MIDL_ProcFormatString.Format,
    &IAssemblyGenCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IAssemblyGenCollectionProxyVtbl = 
{
    0,
    &IID_IAssemblyGenCollection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IAssemblyGenCollection_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IAssemblyGenCollectionStubVtbl =
{
    &IID_IAssemblyGenCollection,
    &IAssemblyGenCollection_ServerInfo,
    7,
    &IAssemblyGenCollection_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    MetaDataApiSample01__MIDL_TypeFormatString.Format,
    0, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x70001f4, /* MIDL Version 7.0.500 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * _MetaDataApiSample01_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IAssemblyGenProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAppDomainGenProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAssemblyGenCollectionProxyVtbl,
    0
};

const CInterfaceStubVtbl * _MetaDataApiSample01_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IAssemblyGenStubVtbl,
    ( CInterfaceStubVtbl *) &_IAppDomainGenStubVtbl,
    ( CInterfaceStubVtbl *) &_IAssemblyGenCollectionStubVtbl,
    0
};

PCInterfaceName const _MetaDataApiSample01_InterfaceNamesList[] = 
{
    "IAssemblyGen",
    "IAppDomainGen",
    "IAssemblyGenCollection",
    0
};

const IID *  _MetaDataApiSample01_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _MetaDataApiSample01_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _MetaDataApiSample01, pIID, n)

int __stdcall _MetaDataApiSample01_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _MetaDataApiSample01, 3, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _MetaDataApiSample01, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _MetaDataApiSample01, 3, *pIndex )
    
}

const ExtendedProxyFileInfo MetaDataApiSample01_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _MetaDataApiSample01_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _MetaDataApiSample01_StubVtblList,
    (const PCInterfaceName * ) & _MetaDataApiSample01_InterfaceNamesList,
    (const IID ** ) & _MetaDataApiSample01_BaseIIDList,
    & _MetaDataApiSample01_IID_Lookup, 
    3,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

