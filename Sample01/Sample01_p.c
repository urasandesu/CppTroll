

/* this ALWAYS GENERATED file contains the proxy stub code */


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


#include "Sample01_i.h"

#define TYPE_FORMAT_STRING_SIZE   1093                              
#define PROC_FORMAT_STRING_SIZE   295                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _Sample01_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } Sample01_MIDL_TYPE_FORMAT_STRING;

typedef struct _Sample01_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } Sample01_MIDL_PROC_FORMAT_STRING;

typedef struct _Sample01_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } Sample01_MIDL_EXPR_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const Sample01_MIDL_TYPE_FORMAT_STRING Sample01__MIDL_TypeFormatString;
extern const Sample01_MIDL_PROC_FORMAT_STRING Sample01__MIDL_ProcFormatString;
extern const Sample01_MIDL_EXPR_FORMAT_STRING Sample01__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IEmployee_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IEmployee_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IEmployeeCollection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IEmployeeCollection_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const Sample01_MIDL_PROC_FORMAT_STRING Sample01__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure get_Name */

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
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 18 */	NdrFcShort( 0x1 ),	/* 1 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 24 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Name */

/* 36 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x8 ),	/* 8 */
/* 44 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x8 ),	/* 8 */
/* 50 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 52 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x1 ),	/* 1 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 60 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 64 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Return value */

/* 66 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 68 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 70 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Id */

/* 72 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 74 */	NdrFcLong( 0x0 ),	/* 0 */
/* 78 */	NdrFcShort( 0x9 ),	/* 9 */
/* 80 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 82 */	NdrFcShort( 0x0 ),	/* 0 */
/* 84 */	NdrFcShort( 0x24 ),	/* 36 */
/* 86 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 88 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 90 */	NdrFcShort( 0x0 ),	/* 0 */
/* 92 */	NdrFcShort( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 96 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 98 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 100 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 102 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 104 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Id */

/* 108 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 110 */	NdrFcLong( 0x0 ),	/* 0 */
/* 114 */	NdrFcShort( 0xa ),	/* 10 */
/* 116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 118 */	NdrFcShort( 0x8 ),	/* 8 */
/* 120 */	NdrFcShort( 0x8 ),	/* 8 */
/* 122 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 124 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 128 */	NdrFcShort( 0x0 ),	/* 0 */
/* 130 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 132 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 134 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 136 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 138 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 140 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 142 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Add */

/* 144 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 146 */	NdrFcLong( 0x0 ),	/* 0 */
/* 150 */	NdrFcShort( 0x7 ),	/* 7 */
/* 152 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 156 */	NdrFcShort( 0x8 ),	/* 8 */
/* 158 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 160 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x0 ),	/* 0 */
/* 166 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 168 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 170 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 172 */	NdrFcShort( 0x3c ),	/* Type Offset=60 */

	/* Return value */

/* 174 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 176 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 178 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Count */

/* 180 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 182 */	NdrFcLong( 0x0 ),	/* 0 */
/* 186 */	NdrFcShort( 0x8 ),	/* 8 */
/* 188 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 192 */	NdrFcShort( 0x24 ),	/* 36 */
/* 194 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 196 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 202 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 204 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 206 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 208 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 210 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 212 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 214 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Item */

/* 216 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 218 */	NdrFcLong( 0x0 ),	/* 0 */
/* 222 */	NdrFcShort( 0x9 ),	/* 9 */
/* 224 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 226 */	NdrFcShort( 0x0 ),	/* 0 */
/* 228 */	NdrFcShort( 0x8 ),	/* 8 */
/* 230 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 232 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 236 */	NdrFcShort( 0xa5 ),	/* 165 */
/* 238 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 240 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 242 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 244 */	NdrFcShort( 0x432 ),	/* Type Offset=1074 */

	/* Parameter ppItem */

/* 246 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 248 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 250 */	NdrFcShort( 0x43c ),	/* Type Offset=1084 */

	/* Return value */

/* 252 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 254 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 256 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get__NewEnum */

/* 258 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 260 */	NdrFcLong( 0x0 ),	/* 0 */
/* 264 */	NdrFcShort( 0xa ),	/* 10 */
/* 266 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 270 */	NdrFcShort( 0x8 ),	/* 8 */
/* 272 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 274 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 280 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppVal */

/* 282 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 284 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 286 */	NdrFcShort( 0x440 ),	/* Type Offset=1088 */

	/* Return value */

/* 288 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 290 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 292 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const Sample01_MIDL_TYPE_FORMAT_STRING Sample01__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x1c ),	/* Offset= 28 (32) */
/*  6 */	
			0x13, 0x0,	/* FC_OP */
/*  8 */	NdrFcShort( 0xe ),	/* Offset= 14 (22) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 20 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 22 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 24 */	NdrFcShort( 0x8 ),	/* 8 */
/* 26 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (10) */
/* 28 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 30 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 32 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x4 ),	/* 4 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0xffde ),	/* Offset= -34 (6) */
/* 42 */	
			0x12, 0x0,	/* FC_UP */
/* 44 */	NdrFcShort( 0xffea ),	/* Offset= -22 (22) */
/* 46 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x4 ),	/* 4 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (42) */
/* 56 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 58 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 60 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 62 */	NdrFcLong( 0x49562fa4 ),	/* 1230385060 */
/* 66 */	NdrFcShort( 0x2e88 ),	/* 11912 */
/* 68 */	NdrFcShort( 0x44b2 ),	/* 17586 */
/* 70 */	0xb3,		/* 179 */
			0xbc,		/* 188 */
/* 72 */	0x95,		/* 149 */
			0xe5,		/* 229 */
/* 74 */	0xd5,		/* 213 */
			0x96,		/* 150 */
/* 76 */	0xad,		/* 173 */
			0xe1,		/* 225 */
/* 78 */	
			0x12, 0x0,	/* FC_UP */
/* 80 */	NdrFcShort( 0x3ce ),	/* Offset= 974 (1054) */
/* 82 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 84 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 86 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 88 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 90 */	NdrFcShort( 0x2 ),	/* Offset= 2 (92) */
/* 92 */	NdrFcShort( 0x10 ),	/* 16 */
/* 94 */	NdrFcShort( 0x2f ),	/* 47 */
/* 96 */	NdrFcLong( 0x14 ),	/* 20 */
/* 100 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 102 */	NdrFcLong( 0x3 ),	/* 3 */
/* 106 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 108 */	NdrFcLong( 0x11 ),	/* 17 */
/* 112 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 114 */	NdrFcLong( 0x2 ),	/* 2 */
/* 118 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 120 */	NdrFcLong( 0x4 ),	/* 4 */
/* 124 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 126 */	NdrFcLong( 0x5 ),	/* 5 */
/* 130 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 132 */	NdrFcLong( 0xb ),	/* 11 */
/* 136 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 138 */	NdrFcLong( 0xa ),	/* 10 */
/* 142 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 144 */	NdrFcLong( 0x6 ),	/* 6 */
/* 148 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (380) */
/* 150 */	NdrFcLong( 0x7 ),	/* 7 */
/* 154 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 156 */	NdrFcLong( 0x8 ),	/* 8 */
/* 160 */	NdrFcShort( 0xff8a ),	/* Offset= -118 (42) */
/* 162 */	NdrFcLong( 0xd ),	/* 13 */
/* 166 */	NdrFcShort( 0xdc ),	/* Offset= 220 (386) */
/* 168 */	NdrFcLong( 0x9 ),	/* 9 */
/* 172 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (404) */
/* 174 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 178 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (422) */
/* 180 */	NdrFcLong( 0x24 ),	/* 36 */
/* 184 */	NdrFcShort( 0x31c ),	/* Offset= 796 (980) */
/* 186 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 190 */	NdrFcShort( 0x316 ),	/* Offset= 790 (980) */
/* 192 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 196 */	NdrFcShort( 0x314 ),	/* Offset= 788 (984) */
/* 198 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 202 */	NdrFcShort( 0x312 ),	/* Offset= 786 (988) */
/* 204 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 208 */	NdrFcShort( 0x310 ),	/* Offset= 784 (992) */
/* 210 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 214 */	NdrFcShort( 0x30e ),	/* Offset= 782 (996) */
/* 216 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 220 */	NdrFcShort( 0x30c ),	/* Offset= 780 (1000) */
/* 222 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 226 */	NdrFcShort( 0x30a ),	/* Offset= 778 (1004) */
/* 228 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 232 */	NdrFcShort( 0x2f4 ),	/* Offset= 756 (988) */
/* 234 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 238 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (992) */
/* 240 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 244 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (1008) */
/* 246 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 250 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (1004) */
/* 252 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 256 */	NdrFcShort( 0x2f4 ),	/* Offset= 756 (1012) */
/* 258 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 262 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (1016) */
/* 264 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 268 */	NdrFcShort( 0x2f0 ),	/* Offset= 752 (1020) */
/* 270 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 274 */	NdrFcShort( 0x2ee ),	/* Offset= 750 (1024) */
/* 276 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 280 */	NdrFcShort( 0x2ec ),	/* Offset= 748 (1028) */
/* 282 */	NdrFcLong( 0x10 ),	/* 16 */
/* 286 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 288 */	NdrFcLong( 0x12 ),	/* 18 */
/* 292 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 294 */	NdrFcLong( 0x13 ),	/* 19 */
/* 298 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 300 */	NdrFcLong( 0x15 ),	/* 21 */
/* 304 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 306 */	NdrFcLong( 0x16 ),	/* 22 */
/* 310 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 312 */	NdrFcLong( 0x17 ),	/* 23 */
/* 316 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 318 */	NdrFcLong( 0xe ),	/* 14 */
/* 322 */	NdrFcShort( 0x2ca ),	/* Offset= 714 (1036) */
/* 324 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 328 */	NdrFcShort( 0x2ce ),	/* Offset= 718 (1046) */
/* 330 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 334 */	NdrFcShort( 0x2cc ),	/* Offset= 716 (1050) */
/* 336 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 340 */	NdrFcShort( 0x288 ),	/* Offset= 648 (988) */
/* 342 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 346 */	NdrFcShort( 0x286 ),	/* Offset= 646 (992) */
/* 348 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 352 */	NdrFcShort( 0x284 ),	/* Offset= 644 (996) */
/* 354 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 358 */	NdrFcShort( 0x27a ),	/* Offset= 634 (992) */
/* 360 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 364 */	NdrFcShort( 0x274 ),	/* Offset= 628 (992) */
/* 366 */	NdrFcLong( 0x0 ),	/* 0 */
/* 370 */	NdrFcShort( 0x0 ),	/* Offset= 0 (370) */
/* 372 */	NdrFcLong( 0x1 ),	/* 1 */
/* 376 */	NdrFcShort( 0x0 ),	/* Offset= 0 (376) */
/* 378 */	NdrFcShort( 0xffff ),	/* Offset= -1 (377) */
/* 380 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 382 */	NdrFcShort( 0x8 ),	/* 8 */
/* 384 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 386 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 388 */	NdrFcLong( 0x0 ),	/* 0 */
/* 392 */	NdrFcShort( 0x0 ),	/* 0 */
/* 394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 396 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 398 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 400 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 402 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 404 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 406 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 410 */	NdrFcShort( 0x0 ),	/* 0 */
/* 412 */	NdrFcShort( 0x0 ),	/* 0 */
/* 414 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 416 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 418 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 420 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 422 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 424 */	NdrFcShort( 0x2 ),	/* Offset= 2 (426) */
/* 426 */	
			0x12, 0x0,	/* FC_UP */
/* 428 */	NdrFcShort( 0x216 ),	/* Offset= 534 (962) */
/* 430 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 432 */	NdrFcShort( 0x18 ),	/* 24 */
/* 434 */	NdrFcShort( 0xa ),	/* 10 */
/* 436 */	NdrFcLong( 0x8 ),	/* 8 */
/* 440 */	NdrFcShort( 0x5a ),	/* Offset= 90 (530) */
/* 442 */	NdrFcLong( 0xd ),	/* 13 */
/* 446 */	NdrFcShort( 0x7e ),	/* Offset= 126 (572) */
/* 448 */	NdrFcLong( 0x9 ),	/* 9 */
/* 452 */	NdrFcShort( 0x9e ),	/* Offset= 158 (610) */
/* 454 */	NdrFcLong( 0xc ),	/* 12 */
/* 458 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (658) */
/* 460 */	NdrFcLong( 0x24 ),	/* 36 */
/* 464 */	NdrFcShort( 0x124 ),	/* Offset= 292 (756) */
/* 466 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 470 */	NdrFcShort( 0x140 ),	/* Offset= 320 (790) */
/* 472 */	NdrFcLong( 0x10 ),	/* 16 */
/* 476 */	NdrFcShort( 0x15a ),	/* Offset= 346 (822) */
/* 478 */	NdrFcLong( 0x2 ),	/* 2 */
/* 482 */	NdrFcShort( 0x174 ),	/* Offset= 372 (854) */
/* 484 */	NdrFcLong( 0x3 ),	/* 3 */
/* 488 */	NdrFcShort( 0x18e ),	/* Offset= 398 (886) */
/* 490 */	NdrFcLong( 0x14 ),	/* 20 */
/* 494 */	NdrFcShort( 0x1a8 ),	/* Offset= 424 (918) */
/* 496 */	NdrFcShort( 0xffff ),	/* Offset= -1 (495) */
/* 498 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 500 */	NdrFcShort( 0x4 ),	/* 4 */
/* 502 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 506 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 508 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 510 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 512 */	NdrFcShort( 0x4 ),	/* 4 */
/* 514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 516 */	NdrFcShort( 0x1 ),	/* 1 */
/* 518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 522 */	0x12, 0x0,	/* FC_UP */
/* 524 */	NdrFcShort( 0xfe0a ),	/* Offset= -502 (22) */
/* 526 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 528 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 530 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 532 */	NdrFcShort( 0x8 ),	/* 8 */
/* 534 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 536 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 538 */	NdrFcShort( 0x4 ),	/* 4 */
/* 540 */	NdrFcShort( 0x4 ),	/* 4 */
/* 542 */	0x11, 0x0,	/* FC_RP */
/* 544 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (498) */
/* 546 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 548 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 550 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 554 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 558 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 560 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 564 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 566 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 568 */	NdrFcShort( 0xff4a ),	/* Offset= -182 (386) */
/* 570 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 572 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 574 */	NdrFcShort( 0x8 ),	/* 8 */
/* 576 */	NdrFcShort( 0x0 ),	/* 0 */
/* 578 */	NdrFcShort( 0x6 ),	/* Offset= 6 (584) */
/* 580 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 582 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 584 */	
			0x11, 0x0,	/* FC_RP */
/* 586 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (550) */
/* 588 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 592 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 596 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 598 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 602 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 604 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 606 */	NdrFcShort( 0xff36 ),	/* Offset= -202 (404) */
/* 608 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 610 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 612 */	NdrFcShort( 0x8 ),	/* 8 */
/* 614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 616 */	NdrFcShort( 0x6 ),	/* Offset= 6 (622) */
/* 618 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 620 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 622 */	
			0x11, 0x0,	/* FC_RP */
/* 624 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (588) */
/* 626 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 628 */	NdrFcShort( 0x4 ),	/* 4 */
/* 630 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 634 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 636 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 638 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 640 */	NdrFcShort( 0x4 ),	/* 4 */
/* 642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 644 */	NdrFcShort( 0x1 ),	/* 1 */
/* 646 */	NdrFcShort( 0x0 ),	/* 0 */
/* 648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 650 */	0x12, 0x0,	/* FC_UP */
/* 652 */	NdrFcShort( 0x192 ),	/* Offset= 402 (1054) */
/* 654 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 656 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 658 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 660 */	NdrFcShort( 0x8 ),	/* 8 */
/* 662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 664 */	NdrFcShort( 0x6 ),	/* Offset= 6 (670) */
/* 666 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 668 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 670 */	
			0x11, 0x0,	/* FC_RP */
/* 672 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (626) */
/* 674 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 676 */	NdrFcLong( 0x2f ),	/* 47 */
/* 680 */	NdrFcShort( 0x0 ),	/* 0 */
/* 682 */	NdrFcShort( 0x0 ),	/* 0 */
/* 684 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 686 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 688 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 690 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 692 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 694 */	NdrFcShort( 0x1 ),	/* 1 */
/* 696 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 698 */	NdrFcShort( 0x4 ),	/* 4 */
/* 700 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 702 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 704 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 706 */	NdrFcShort( 0x10 ),	/* 16 */
/* 708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 710 */	NdrFcShort( 0xa ),	/* Offset= 10 (720) */
/* 712 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 714 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 716 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (674) */
/* 718 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 720 */	
			0x12, 0x0,	/* FC_UP */
/* 722 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (692) */
/* 724 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 726 */	NdrFcShort( 0x4 ),	/* 4 */
/* 728 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 732 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 734 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 736 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 738 */	NdrFcShort( 0x4 ),	/* 4 */
/* 740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 742 */	NdrFcShort( 0x1 ),	/* 1 */
/* 744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 748 */	0x12, 0x0,	/* FC_UP */
/* 750 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (704) */
/* 752 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 754 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 756 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 758 */	NdrFcShort( 0x8 ),	/* 8 */
/* 760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0x6 ),	/* Offset= 6 (768) */
/* 764 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 766 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 768 */	
			0x11, 0x0,	/* FC_RP */
/* 770 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (724) */
/* 772 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 774 */	NdrFcShort( 0x8 ),	/* 8 */
/* 776 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 778 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 780 */	NdrFcShort( 0x10 ),	/* 16 */
/* 782 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 784 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 786 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (772) */
			0x5b,		/* FC_END */
/* 790 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 792 */	NdrFcShort( 0x18 ),	/* 24 */
/* 794 */	NdrFcShort( 0x0 ),	/* 0 */
/* 796 */	NdrFcShort( 0xa ),	/* Offset= 10 (806) */
/* 798 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 800 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 802 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (778) */
/* 804 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 806 */	
			0x11, 0x0,	/* FC_RP */
/* 808 */	NdrFcShort( 0xfefe ),	/* Offset= -258 (550) */
/* 810 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 812 */	NdrFcShort( 0x1 ),	/* 1 */
/* 814 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 818 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 820 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 822 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 824 */	NdrFcShort( 0x8 ),	/* 8 */
/* 826 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 828 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 830 */	NdrFcShort( 0x4 ),	/* 4 */
/* 832 */	NdrFcShort( 0x4 ),	/* 4 */
/* 834 */	0x12, 0x0,	/* FC_UP */
/* 836 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (810) */
/* 838 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 840 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 842 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 844 */	NdrFcShort( 0x2 ),	/* 2 */
/* 846 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 850 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 852 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 854 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 856 */	NdrFcShort( 0x8 ),	/* 8 */
/* 858 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 860 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 862 */	NdrFcShort( 0x4 ),	/* 4 */
/* 864 */	NdrFcShort( 0x4 ),	/* 4 */
/* 866 */	0x12, 0x0,	/* FC_UP */
/* 868 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (842) */
/* 870 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 872 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 874 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 876 */	NdrFcShort( 0x4 ),	/* 4 */
/* 878 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 880 */	NdrFcShort( 0x0 ),	/* 0 */
/* 882 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 884 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 886 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 888 */	NdrFcShort( 0x8 ),	/* 8 */
/* 890 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 892 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 894 */	NdrFcShort( 0x4 ),	/* 4 */
/* 896 */	NdrFcShort( 0x4 ),	/* 4 */
/* 898 */	0x12, 0x0,	/* FC_UP */
/* 900 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (874) */
/* 902 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 904 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 906 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 908 */	NdrFcShort( 0x8 ),	/* 8 */
/* 910 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 912 */	NdrFcShort( 0x0 ),	/* 0 */
/* 914 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 916 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 918 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 920 */	NdrFcShort( 0x8 ),	/* 8 */
/* 922 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 924 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 926 */	NdrFcShort( 0x4 ),	/* 4 */
/* 928 */	NdrFcShort( 0x4 ),	/* 4 */
/* 930 */	0x12, 0x0,	/* FC_UP */
/* 932 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (906) */
/* 934 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 936 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 938 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 940 */	NdrFcShort( 0x8 ),	/* 8 */
/* 942 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 944 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 946 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 948 */	NdrFcShort( 0x8 ),	/* 8 */
/* 950 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 952 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 954 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 956 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 958 */	NdrFcShort( 0xffec ),	/* Offset= -20 (938) */
/* 960 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 962 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 964 */	NdrFcShort( 0x28 ),	/* 40 */
/* 966 */	NdrFcShort( 0xffec ),	/* Offset= -20 (946) */
/* 968 */	NdrFcShort( 0x0 ),	/* Offset= 0 (968) */
/* 970 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 972 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 974 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 976 */	NdrFcShort( 0xfdde ),	/* Offset= -546 (430) */
/* 978 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 980 */	
			0x12, 0x0,	/* FC_UP */
/* 982 */	NdrFcShort( 0xfeea ),	/* Offset= -278 (704) */
/* 984 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 986 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 988 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 990 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 992 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 994 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 996 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 998 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 1000 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1002 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 1004 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1006 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 1008 */	
			0x12, 0x0,	/* FC_UP */
/* 1010 */	NdrFcShort( 0xfd8a ),	/* Offset= -630 (380) */
/* 1012 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1014 */	NdrFcShort( 0xfc34 ),	/* Offset= -972 (42) */
/* 1016 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1018 */	NdrFcShort( 0xfd88 ),	/* Offset= -632 (386) */
/* 1020 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1022 */	NdrFcShort( 0xfd96 ),	/* Offset= -618 (404) */
/* 1024 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1026 */	NdrFcShort( 0xfda4 ),	/* Offset= -604 (422) */
/* 1028 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1030 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1032) */
/* 1032 */	
			0x12, 0x0,	/* FC_UP */
/* 1034 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1054) */
/* 1036 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 1038 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1040 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 1042 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 1044 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1046 */	
			0x12, 0x0,	/* FC_UP */
/* 1048 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1036) */
/* 1050 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1052 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 1054 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1056 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1058 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1060 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1060) */
/* 1062 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1064 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1066 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1068 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1070 */	NdrFcShort( 0xfc24 ),	/* Offset= -988 (82) */
/* 1072 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1074 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1076 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1078 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1080 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1082 */	NdrFcShort( 0xfc14 ),	/* Offset= -1004 (78) */
/* 1084 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1086 */	NdrFcShort( 0xfbfe ),	/* Offset= -1026 (60) */
/* 1088 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1090 */	NdrFcShort( 0xfd40 ),	/* Offset= -704 (386) */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IEmployee, ver. 0.0,
   GUID={0x49562FA4,0x2E88,0x44B2,{0xB3,0xBC,0x95,0xE5,0xD5,0x96,0xAD,0xE1}} */

#pragma code_seg(".orpc")
static const unsigned short IEmployee_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    36,
    72,
    108
    };

static const MIDL_STUBLESS_PROXY_INFO IEmployee_ProxyInfo =
    {
    &Object_StubDesc,
    Sample01__MIDL_ProcFormatString.Format,
    &IEmployee_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IEmployee_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    Sample01__MIDL_ProcFormatString.Format,
    &IEmployee_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IEmployeeProxyVtbl = 
{
    &IEmployee_ProxyInfo,
    &IID_IEmployee,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IEmployee::get_Name */ ,
    (void *) (INT_PTR) -1 /* IEmployee::put_Name */ ,
    (void *) (INT_PTR) -1 /* IEmployee::get_Id */ ,
    (void *) (INT_PTR) -1 /* IEmployee::put_Id */
};


static const PRPC_STUB_FUNCTION IEmployee_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IEmployeeStubVtbl =
{
    &IID_IEmployee,
    &IEmployee_ServerInfo,
    11,
    &IEmployee_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IEmployeeCollection, ver. 0.0,
   GUID={0x45C6C575,0x91C4,0x4DB3,{0x8B,0x0D,0x74,0xBD,0xDD,0xF7,0xD3,0xB4}} */

#pragma code_seg(".orpc")
static const unsigned short IEmployeeCollection_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    144,
    180,
    216,
    258
    };

static const MIDL_STUBLESS_PROXY_INFO IEmployeeCollection_ProxyInfo =
    {
    &Object_StubDesc,
    Sample01__MIDL_ProcFormatString.Format,
    &IEmployeeCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IEmployeeCollection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    Sample01__MIDL_ProcFormatString.Format,
    &IEmployeeCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IEmployeeCollectionProxyVtbl = 
{
    &IEmployeeCollection_ProxyInfo,
    &IID_IEmployeeCollection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IEmployeeCollection::Add */ ,
    (void *) (INT_PTR) -1 /* IEmployeeCollection::get_Count */ ,
    (void *) (INT_PTR) -1 /* IEmployeeCollection::Item */ ,
    (void *) (INT_PTR) -1 /* IEmployeeCollection::get__NewEnum */
};


static const PRPC_STUB_FUNCTION IEmployeeCollection_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IEmployeeCollectionStubVtbl =
{
    &IID_IEmployeeCollection,
    &IEmployeeCollection_ServerInfo,
    11,
    &IEmployeeCollection_table[-3],
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
    Sample01__MIDL_TypeFormatString.Format,
    0, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x70001f4, /* MIDL Version 7.0.500 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * _Sample01_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IEmployeeCollectionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IEmployeeProxyVtbl,
    0
};

const CInterfaceStubVtbl * _Sample01_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IEmployeeCollectionStubVtbl,
    ( CInterfaceStubVtbl *) &_IEmployeeStubVtbl,
    0
};

PCInterfaceName const _Sample01_InterfaceNamesList[] = 
{
    "IEmployeeCollection",
    "IEmployee",
    0
};

const IID *  _Sample01_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _Sample01_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _Sample01, pIID, n)

int __stdcall _Sample01_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _Sample01, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _Sample01, 2, *pIndex )
    
}

const ExtendedProxyFileInfo Sample01_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _Sample01_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _Sample01_StubVtblList,
    (const PCInterfaceName * ) & _Sample01_InterfaceNamesList,
    (const IID ** ) & _Sample01_BaseIIDList,
    & _Sample01_IID_Lookup, 
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

