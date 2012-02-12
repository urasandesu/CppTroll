#pragma once

#ifndef INDIRETIONINTERFACES_H
#define INDIRETIONINTERFACES_H

#ifdef URASANDESU_PRIG_EXPORTS
#define URASANDESU_PRIG_API __declspec(dllexport)
#else
#define URASANDESU_PRIG_API __declspec(dllimport)
#endif

//struct IndirectionInfo
//{
//    LPCWSTR m_assemblyName;
//    LPCWSTR m_typeFullName;
//    LPCWSTR m_methodName;
//};

//EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(BOOL) IndirectionGetFunctionPointer(IndirectionInfo *pInfo, void const **ppFuncPtr);
//EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(BOOL) IndirectionSetFunctionPointer(IndirectionInfo *pInfo, void const *pFuncPtr);

EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(BOOL) InstanceGettersTryAdd(LPCWSTR key, void const *pFuncPtr);
EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(BOOL) InstanceGettersTryGet(LPCWSTR key, void const **ppFuncPtr);
EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(VOID) InstanceGettersUnload();

#endif  // #ifndef INDIRETIONINTERFACES_H