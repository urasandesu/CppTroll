#include "StdAfx.h"
#include "IndirectionInterfaces.h"
#include "GlobalSafeDictionary.h"

typedef GlobalSafeDictionary<std::wstring, void const *> InstanceGetters;

EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(BOOL) InstanceGettersTryAdd(LPCWSTR key, void const *pFuncPtr)
{
    InstanceGetters &ing = InstanceGetters::GetInstance();
    return ing.TryAdd(std::wstring(key), pFuncPtr);
}

EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(BOOL) InstanceGettersTryGet(LPCWSTR key, void const **ppFuncPtr)
{
    _ASSERTE(ppFuncPtr != NULL);
    InstanceGetters &ing = InstanceGetters::GetInstance();
    return ing.TryGet(std::wstring(key), *ppFuncPtr);
}

EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(VOID) InstanceGettersUnload()
{
    InstanceGetters &ing = InstanceGetters::GetInstance();
    ing.Unload();
}
