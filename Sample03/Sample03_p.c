

/* this ALWAYS GENERATED file contains the proxy stub code */


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


#include "Sample03_i.h"

#define TYPE_FORMAT_STRING_SIZE   47                                
#define PROC_FORMAT_STRING_SIZE   73                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _Sample03_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } Sample03_MIDL_TYPE_FORMAT_STRING;

typedef struct _Sample03_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } Sample03_MIDL_PROC_FORMAT_STRING;

typedef struct _Sample03_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } Sample03_MIDL_EXPR_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const Sample03_MIDL_TYPE_FORMAT_STRING Sample03__MIDL_TypeFormatString;
extern const Sample03_MIDL_PROC_FORMAT_STRING Sample03__MIDL_ProcFormatString;
extern const Sample03_MIDL_EXPR_FORMAT_STRING Sample03__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMyEnumerable_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMyEnumerable_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMyEnumerableGenerator_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMyEnumerableGenerator_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const Sample03_MIDL_PROC_FORMAT_STRING Sample03__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure get__NewEnum */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppVal */

/* 24 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateInstance */

/* 36 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x7 ),	/* 7 */
/* 44 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x8 ),	/* 8 */
/* 50 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 52 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppVal */

/* 60 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 64 */	NdrFcShort( 0x18 ),	/* Type Offset=24 */

	/* Return value */

/* 66 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 68 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 70 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const Sample03_MIDL_TYPE_FORMAT_STRING Sample03__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/*  4 */	NdrFcShort( 0x2 ),	/* Offset= 2 (6) */
/*  6 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/*  8 */	NdrFcLong( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x0 ),	/* 0 */
/* 14 */	NdrFcShort( 0x0 ),	/* 0 */
/* 16 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 18 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 20 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 22 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 24 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 26 */	NdrFcShort( 0x2 ),	/* Offset= 2 (28) */
/* 28 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 30 */	NdrFcLong( 0x26251bae ),	/* 639966126 */
/* 34 */	NdrFcShort( 0xb229 ),	/* -19927 */
/* 36 */	NdrFcShort( 0x48dc ),	/* 18652 */
/* 38 */	0x9b,		/* 155 */
			0x3e,		/* 62 */
/* 40 */	0x7c,		/* 124 */
			0x9f,		/* 159 */
/* 42 */	0x77,		/* 119 */
			0xbf,		/* 191 */
/* 44 */	0x7d,		/* 125 */
			0x17,		/* 23 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IMyEnumerable, ver. 0.0,
   GUID={0x26251BAE,0xB229,0x48DC,{0x9B,0x3E,0x7C,0x9F,0x77,0xBF,0x7D,0x17}} */

#pragma code_seg(".orpc")
static const unsigned short IMyEnumerable_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IMyEnumerable_ProxyInfo =
    {
    &Object_StubDesc,
    Sample03__MIDL_ProcFormatString.Format,
    &IMyEnumerable_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMyEnumerable_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    Sample03__MIDL_ProcFormatString.Format,
    &IMyEnumerable_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IMyEnumerableProxyVtbl = 
{
    &IMyEnumerable_ProxyInfo,
    &IID_IMyEnumerable,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMyEnumerable::get__NewEnum */
};


static const PRPC_STUB_FUNCTION IMyEnumerable_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IMyEnumerableStubVtbl =
{
    &IID_IMyEnumerable,
    &IMyEnumerable_ServerInfo,
    8,
    &IMyEnumerable_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMyEnumerableGenerator, ver. 0.0,
   GUID={0xACA95E6E,0x8AD2,0x4F69,{0xBC,0x53,0xA7,0xF8,0xDC,0x8F,0x20,0xE8}} */

#pragma code_seg(".orpc")
static const unsigned short IMyEnumerableGenerator_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    36
    };

static const MIDL_STUBLESS_PROXY_INFO IMyEnumerableGenerator_ProxyInfo =
    {
    &Object_StubDesc,
    Sample03__MIDL_ProcFormatString.Format,
    &IMyEnumerableGenerator_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMyEnumerableGenerator_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    Sample03__MIDL_ProcFormatString.Format,
    &IMyEnumerableGenerator_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IMyEnumerableGeneratorProxyVtbl = 
{
    &IMyEnumerableGenerator_ProxyInfo,
    &IID_IMyEnumerableGenerator,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMyEnumerableGenerator::CreateInstance */
};


static const PRPC_STUB_FUNCTION IMyEnumerableGenerator_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IMyEnumerableGeneratorStubVtbl =
{
    &IID_IMyEnumerableGenerator,
    &IMyEnumerableGenerator_ServerInfo,
    8,
    &IMyEnumerableGenerator_table[-3],
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
    Sample03__MIDL_TypeFormatString.Format,
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

const CInterfaceProxyVtbl * _Sample03_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IMyEnumerableGeneratorProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMyEnumerableProxyVtbl,
    0
};

const CInterfaceStubVtbl * _Sample03_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IMyEnumerableGeneratorStubVtbl,
    ( CInterfaceStubVtbl *) &_IMyEnumerableStubVtbl,
    0
};

PCInterfaceName const _Sample03_InterfaceNamesList[] = 
{
    "IMyEnumerableGenerator",
    "IMyEnumerable",
    0
};

const IID *  _Sample03_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _Sample03_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _Sample03, pIID, n)

int __stdcall _Sample03_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _Sample03, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _Sample03, 2, *pIndex )
    
}

const ExtendedProxyFileInfo Sample03_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _Sample03_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _Sample03_StubVtblList,
    (const PCInterfaceName * ) & _Sample03_InterfaceNamesList,
    (const IID ** ) & _Sample03_BaseIIDList,
    & _Sample03_IID_Lookup, 
    2,
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

