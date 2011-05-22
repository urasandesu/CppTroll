

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Sample02_i_h__
#define __Sample02_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyCache_FWD_DEFINED__
#define __IMyCache_FWD_DEFINED__
typedef interface IMyCache IMyCache;
#endif 	/* __IMyCache_FWD_DEFINED__ */


#ifndef __IPairBStrVariant_FWD_DEFINED__
#define __IPairBStrVariant_FWD_DEFINED__
typedef interface IPairBStrVariant IPairBStrVariant;
#endif 	/* __IPairBStrVariant_FWD_DEFINED__ */


#ifndef __IMyCachePrinter_FWD_DEFINED__
#define __IMyCachePrinter_FWD_DEFINED__
typedef interface IMyCachePrinter IMyCachePrinter;
#endif 	/* __IMyCachePrinter_FWD_DEFINED__ */


#ifndef __MyCache_FWD_DEFINED__
#define __MyCache_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyCache MyCache;
#else
typedef struct MyCache MyCache;
#endif /* __cplusplus */

#endif 	/* __MyCache_FWD_DEFINED__ */


#ifndef __PairBStrVariant_FWD_DEFINED__
#define __PairBStrVariant_FWD_DEFINED__

#ifdef __cplusplus
typedef class PairBStrVariant PairBStrVariant;
#else
typedef struct PairBStrVariant PairBStrVariant;
#endif /* __cplusplus */

#endif 	/* __PairBStrVariant_FWD_DEFINED__ */


#ifndef __MyCachePrinter_FWD_DEFINED__
#define __MyCachePrinter_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyCachePrinter MyCachePrinter;
#else
typedef struct MyCachePrinter MyCachePrinter;
#endif /* __cplusplus */

#endif 	/* __MyCachePrinter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IMyCache_INTERFACE_DEFINED__
#define __IMyCache_INTERFACE_DEFINED__

/* interface IMyCache */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyCache;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("324FA781-2E07-415E-B60B-93D2A535DD90")
    IMyCache : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR key,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ BSTR key,
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [restricted][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyCacheVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyCache * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyCache * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyCache * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMyCache * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMyCache * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMyCache * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMyCache * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IMyCache * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IMyCache * This,
            /* [in] */ BSTR key,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IMyCache * This,
            /* [in] */ BSTR key,
            /* [in] */ VARIANT newVal);
        
        /* [restricted][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IMyCache * This,
            /* [retval][out] */ IUnknown **ppVal);
        
        END_INTERFACE
    } IMyCacheVtbl;

    interface IMyCache
    {
        CONST_VTBL struct IMyCacheVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyCache_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyCache_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyCache_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyCache_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMyCache_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMyCache_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMyCache_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMyCache_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IMyCache_get_Item(This,key,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,key,pVal) ) 

#define IMyCache_put_Item(This,key,newVal)	\
    ( (This)->lpVtbl -> put_Item(This,key,newVal) ) 

#define IMyCache_get__NewEnum(This,ppVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyCache_INTERFACE_DEFINED__ */


#ifndef __IPairBStrVariant_INTERFACE_DEFINED__
#define __IPairBStrVariant_INTERFACE_DEFINED__

/* interface IPairBStrVariant */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPairBStrVariant;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4C29DB1F-A3FA-47C9-9874-B7FF64864EF6")
    IPairBStrVariant : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_First( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_First( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Second( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Second( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPairBStrVariantVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPairBStrVariant * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPairBStrVariant * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPairBStrVariant * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPairBStrVariant * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPairBStrVariant * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPairBStrVariant * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPairBStrVariant * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_First )( 
            IPairBStrVariant * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_First )( 
            IPairBStrVariant * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Second )( 
            IPairBStrVariant * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Second )( 
            IPairBStrVariant * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IPairBStrVariantVtbl;

    interface IPairBStrVariant
    {
        CONST_VTBL struct IPairBStrVariantVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPairBStrVariant_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPairBStrVariant_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPairBStrVariant_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPairBStrVariant_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPairBStrVariant_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPairBStrVariant_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPairBStrVariant_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPairBStrVariant_get_First(This,pVal)	\
    ( (This)->lpVtbl -> get_First(This,pVal) ) 

#define IPairBStrVariant_put_First(This,newVal)	\
    ( (This)->lpVtbl -> put_First(This,newVal) ) 

#define IPairBStrVariant_get_Second(This,pVal)	\
    ( (This)->lpVtbl -> get_Second(This,pVal) ) 

#define IPairBStrVariant_put_Second(This,newVal)	\
    ( (This)->lpVtbl -> put_Second(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPairBStrVariant_INTERFACE_DEFINED__ */


#ifndef __IMyCachePrinter_INTERFACE_DEFINED__
#define __IMyCachePrinter_INTERFACE_DEFINED__

/* interface IMyCachePrinter */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyCachePrinter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F794302C-AD7E-4DA9-A000-794FDC32AF49")
    IMyCachePrinter : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Print( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyCachePrinterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyCachePrinter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyCachePrinter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyCachePrinter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMyCachePrinter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMyCachePrinter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMyCachePrinter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMyCachePrinter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Print )( 
            IMyCachePrinter * This);
        
        END_INTERFACE
    } IMyCachePrinterVtbl;

    interface IMyCachePrinter
    {
        CONST_VTBL struct IMyCachePrinterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyCachePrinter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyCachePrinter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyCachePrinter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyCachePrinter_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMyCachePrinter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMyCachePrinter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMyCachePrinter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMyCachePrinter_Print(This)	\
    ( (This)->lpVtbl -> Print(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyCachePrinter_INTERFACE_DEFINED__ */



#ifndef __Sample02Lib_LIBRARY_DEFINED__
#define __Sample02Lib_LIBRARY_DEFINED__

/* library Sample02Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_Sample02Lib;

EXTERN_C const CLSID CLSID_MyCache;

#ifdef __cplusplus

class DECLSPEC_UUID("206584CE-D105-4FB6-9B13-E6FA6CE227B9")
MyCache;
#endif

EXTERN_C const CLSID CLSID_PairBStrVariant;

#ifdef __cplusplus

class DECLSPEC_UUID("37C6DACC-3125-4568-B6C5-0EED9373C7C2")
PairBStrVariant;
#endif

EXTERN_C const CLSID CLSID_MyCachePrinter;

#ifdef __cplusplus

class DECLSPEC_UUID("E8A92313-2962-4844-8086-5120A29AD7FF")
MyCachePrinter;
#endif
#endif /* __Sample02Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


