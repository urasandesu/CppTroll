#pragma once

#ifndef INDIRETIONINTERFACES_H
#define INDIRETIONINTERFACES_H

#ifdef URASANDESU_PRIG_EXPORTS
#define URASANDESU_PRIG_API __declspec(dllexport)
#else
#define URASANDESU_PRIG_API __declspec(dllimport)
#endif

struct IndiretionInfo
{
    LPCWSTR m_assemblyName;
    LPCWSTR m_typeFullName;
    LPCWSTR m_methodName;
};

EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(BOOL) IndiretionGetFunctionPointer(IndiretionInfo *pInfo, void const **ppFuncPtr);
EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(BOOL) IndiretionSetFunctionPointer(IndiretionInfo *pInfo, void const *pFuncPtr);

#endif  // #ifndef INDIRETIONINTERFACES_H