

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#ifndef __Sample03_i_h__
#define __Sample03_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyEnumerable_FWD_DEFINED__
#define __IMyEnumerable_FWD_DEFINED__
typedef interface IMyEnumerable IMyEnumerable;
#endif 	/* __IMyEnumerable_FWD_DEFINED__ */


#ifndef __IMyEnumerableGenerator_FWD_DEFINED__
#define __IMyEnumerableGenerator_FWD_DEFINED__
typedef interface IMyEnumerableGenerator IMyEnumerableGenerator;
#endif 	/* __IMyEnumerableGenerator_FWD_DEFINED__ */


#ifndef __MyEnumerable_FWD_DEFINED__
#define __MyEnumerable_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyEnumerable MyEnumerable;
#else
typedef struct MyEnumerable MyEnumerable;
#endif /* __cplusplus */

#endif 	/* __MyEnumerable_FWD_DEFINED__ */


#ifndef __MyEnumerableGenerator_FWD_DEFINED__
#define __MyEnumerableGenerator_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyEnumerableGenerator MyEnumerableGenerator;
#else
typedef struct MyEnumerableGenerator MyEnumerableGenerator;
#endif /* __cplusplus */

#endif 	/* __MyEnumerableGenerator_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IMyEnumerable_INTERFACE_DEFINED__
#define __IMyEnumerable_INTERFACE_DEFINED__

/* interface IMyEnumerable */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyEnumerable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("26251BAE-B229-48DC-9B3E-7C9F77BF7D17")
    IMyEnumerable : public IDispatch
    {
    public:
        virtual /* [restricted][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyEnumerableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyEnumerable * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyEnumerable * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyEnumerable * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMyEnumerable * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMyEnumerable * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMyEnumerable * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMyEnumerable * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [restricted][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IMyEnumerable * This,
            /* [retval][out] */ IUnknown **ppVal);
        
        END_INTERFACE
    } IMyEnumerableVtbl;

    interface IMyEnumerable
    {
        CONST_VTBL struct IMyEnumerableVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyEnumerable_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyEnumerable_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyEnumerable_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyEnumerable_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMyEnumerable_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMyEnumerable_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMyEnumerable_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMyEnumerable_get__NewEnum(This,ppVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyEnumerable_INTERFACE_DEFINED__ */


#ifndef __IMyEnumerableGenerator_INTERFACE_DEFINED__
#define __IMyEnumerableGenerator_INTERFACE_DEFINED__

/* interface IMyEnumerableGenerator */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyEnumerableGenerator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ACA95E6E-8AD2-4F69-BC53-A7F8DC8F20E8")
    IMyEnumerableGenerator : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateInstance( 
            /* [retval][out] */ IMyEnumerable **ppVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyEnumerableGeneratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyEnumerableGenerator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyEnumerableGenerator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyEnumerableGenerator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMyEnumerableGenerator * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMyEnumerableGenerator * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMyEnumerableGenerator * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMyEnumerableGenerator * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateInstance )( 
            IMyEnumerableGenerator * This,
            /* [retval][out] */ IMyEnumerable **ppVal);
        
        END_INTERFACE
    } IMyEnumerableGeneratorVtbl;

    interface IMyEnumerableGenerator
    {
        CONST_VTBL struct IMyEnumerableGeneratorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyEnumerableGenerator_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyEnumerableGenerator_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyEnumerableGenerator_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyEnumerableGenerator_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMyEnumerableGenerator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMyEnumerableGenerator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMyEnumerableGenerator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMyEnumerableGenerator_CreateInstance(This,ppVal)	\
    ( (This)->lpVtbl -> CreateInstance(This,ppVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyEnumerableGenerator_INTERFACE_DEFINED__ */



#ifndef __Sample03Lib_LIBRARY_DEFINED__
#define __Sample03Lib_LIBRARY_DEFINED__

/* library Sample03Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_Sample03Lib;

EXTERN_C const CLSID CLSID_MyEnumerable;

#ifdef __cplusplus

class DECLSPEC_UUID("732D6B0C-651E-4D5D-A706-447DDB84C6D5")
MyEnumerable;
#endif

EXTERN_C const CLSID CLSID_MyEnumerableGenerator;

#ifdef __cplusplus

class DECLSPEC_UUID("F9DAF8FA-8D6F-42C7-85CF-901911821456")
MyEnumerableGenerator;
#endif
#endif /* __Sample03Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


