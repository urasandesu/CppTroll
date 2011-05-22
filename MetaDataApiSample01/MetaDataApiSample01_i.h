

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#ifndef __MetaDataApiSample01_i_h__
#define __MetaDataApiSample01_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAppDomainGen_FWD_DEFINED__
#define __IAppDomainGen_FWD_DEFINED__
typedef interface IAppDomainGen IAppDomainGen;
#endif 	/* __IAppDomainGen_FWD_DEFINED__ */


#ifndef __IAssemblyGen_FWD_DEFINED__
#define __IAssemblyGen_FWD_DEFINED__
typedef interface IAssemblyGen IAssemblyGen;
#endif 	/* __IAssemblyGen_FWD_DEFINED__ */


#ifndef __IAssemblyGenCollection_FWD_DEFINED__
#define __IAssemblyGenCollection_FWD_DEFINED__
typedef interface IAssemblyGenCollection IAssemblyGenCollection;
#endif 	/* __IAssemblyGenCollection_FWD_DEFINED__ */


#ifndef __AppDomainGen_FWD_DEFINED__
#define __AppDomainGen_FWD_DEFINED__

#ifdef __cplusplus
typedef class AppDomainGen AppDomainGen;
#else
typedef struct AppDomainGen AppDomainGen;
#endif /* __cplusplus */

#endif 	/* __AppDomainGen_FWD_DEFINED__ */


#ifndef __AssemblyGen_FWD_DEFINED__
#define __AssemblyGen_FWD_DEFINED__

#ifdef __cplusplus
typedef class AssemblyGen AssemblyGen;
#else
typedef struct AssemblyGen AssemblyGen;
#endif /* __cplusplus */

#endif 	/* __AssemblyGen_FWD_DEFINED__ */


#ifndef __AssemblyGenCollection_FWD_DEFINED__
#define __AssemblyGenCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class AssemblyGenCollection AssemblyGenCollection;
#else
typedef struct AssemblyGenCollection AssemblyGenCollection;
#endif /* __cplusplus */

#endif 	/* __AssemblyGenCollection_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IAppDomainGen_INTERFACE_DEFINED__
#define __IAppDomainGen_INTERFACE_DEFINED__

/* interface IAppDomainGen */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAppDomainGen;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CB372775-EF3B-4D44-B033-CC6638C3AB55")
    IAppDomainGen : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IAppDomainGenVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAppDomainGen * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAppDomainGen * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAppDomainGen * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAppDomainGen * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAppDomainGen * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAppDomainGen * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAppDomainGen * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IAppDomainGenVtbl;

    interface IAppDomainGen
    {
        CONST_VTBL struct IAppDomainGenVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAppDomainGen_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAppDomainGen_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAppDomainGen_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAppDomainGen_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAppDomainGen_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAppDomainGen_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAppDomainGen_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAppDomainGen_INTERFACE_DEFINED__ */


#ifndef __IAssemblyGen_INTERFACE_DEFINED__
#define __IAssemblyGen_INTERFACE_DEFINED__

/* interface IAssemblyGen */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAssemblyGen;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("940B2252-DB28-414D-A615-49F7E7B1EFD0")
    IAssemblyGen : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IAssemblyGenVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAssemblyGen * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAssemblyGen * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAssemblyGen * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAssemblyGen * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAssemblyGen * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAssemblyGen * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAssemblyGen * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IAssemblyGenVtbl;

    interface IAssemblyGen
    {
        CONST_VTBL struct IAssemblyGenVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAssemblyGen_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAssemblyGen_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAssemblyGen_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAssemblyGen_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAssemblyGen_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAssemblyGen_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAssemblyGen_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAssemblyGen_INTERFACE_DEFINED__ */


#ifndef __IAssemblyGenCollection_INTERFACE_DEFINED__
#define __IAssemblyGenCollection_INTERFACE_DEFINED__

/* interface IAssemblyGenCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAssemblyGenCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8DC18C9B-60C7-415C-AD30-2B09E56654DB")
    IAssemblyGenCollection : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IAssemblyGenCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAssemblyGenCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAssemblyGenCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAssemblyGenCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAssemblyGenCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAssemblyGenCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAssemblyGenCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAssemblyGenCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IAssemblyGenCollectionVtbl;

    interface IAssemblyGenCollection
    {
        CONST_VTBL struct IAssemblyGenCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAssemblyGenCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAssemblyGenCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAssemblyGenCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAssemblyGenCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAssemblyGenCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAssemblyGenCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAssemblyGenCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAssemblyGenCollection_INTERFACE_DEFINED__ */



#ifndef __MetaDataApiSample01Lib_LIBRARY_DEFINED__
#define __MetaDataApiSample01Lib_LIBRARY_DEFINED__

/* library MetaDataApiSample01Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MetaDataApiSample01Lib;

EXTERN_C const CLSID CLSID_AppDomainGen;

#ifdef __cplusplus

class DECLSPEC_UUID("965DB760-A27B-4592-8A32-23F4E22EB167")
AppDomainGen;
#endif

EXTERN_C const CLSID CLSID_AssemblyGen;

#ifdef __cplusplus

class DECLSPEC_UUID("6D2E93D6-6364-4FA7-90CF-E7861E875D9F")
AssemblyGen;
#endif

EXTERN_C const CLSID CLSID_AssemblyGenCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("FA217239-6436-4D05-80AA-CFAB4A86A16F")
AssemblyGenCollection;
#endif
#endif /* __MetaDataApiSample01Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


