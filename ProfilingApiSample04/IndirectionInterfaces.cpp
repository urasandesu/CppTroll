#include "StdAfx.h"
#include "IndirectionInterfaces.h"

#if 0
#ifndef URASANDESU_CPPANONYM_HEAPPROVIDER_H
#include <Urasandesu/CppAnonym/HeapProvider.h>
#endif

class IndirectionMethodInfo : 
    public Urasandesu::CppAnonym::IHeapContent<std::wstring>, 
    boost::noncopyable
{
public:
    IndirectionMethodInfo() : m_pFuncPtr(NULL) { }

    void const *GetFunctionPointer() const
    {
        return m_pFuncPtr;
    }

    void SetFunctionPointer(void const *pFuncPtr)
    {
        m_pFuncPtr = pFuncPtr;
    }

private:
    void const *m_pFuncPtr;
};

class IndirectionTypeInfo : 
    public Urasandesu::CppAnonym::IHeapContent<std::wstring>, 
    public Urasandesu::CppAnonym::HeapProvider<std::wstring, boost::mpl::vector<IndirectionMethodInfo> >
{
public:
    typedef type_decided_by<IndirectionMethodInfo>::type indirection_method_heap;
};

class IndirectionAssemblyInfo : 
    public Urasandesu::CppAnonym::IHeapContent<std::wstring>,
    public Urasandesu::CppAnonym::HeapProvider<std::wstring, boost::mpl::vector<IndirectionTypeInfo> >
{
public:
    typedef type_decided_by<IndirectionTypeInfo>::type indirection_type_heap;
};


class IndirectionManager :
    public Urasandesu::CppAnonym::HeapProvider<std::wstring, boost::mpl::vector<IndirectionAssemblyInfo> >
{
public:
    typedef type_decided_by<IndirectionAssemblyInfo>::type indirection_assembly_heap;

    static IndirectionManager &GetInstance()
    {
        static IndirectionManager im;
        return im;
    }

    BOOL TryAdd(LPCWSTR key, void const *pFuncPtr)
    {
        using namespace std;

        wstring wkey(key);
        if (m_funcPtrMap.find(wkey) == m_funcPtrMap.end())
        {
            m_funcPtrMap[wkey] = pFuncPtr;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

    BOOL TryGet(LPCWSTR key, void const **ppFuncPtr)
    {
        using namespace std;

        _ASSERTE(ppFuncPtr != NULL);

        wstring wkey(key);
        if (m_funcPtrMap.find(wkey) == m_funcPtrMap.end())
        {
            *ppFuncPtr = NULL;
            return FALSE;
        }
        else
        {
            *ppFuncPtr = m_funcPtrMap[wkey];
            return TRUE;
        }
    }

    void Unload()
    {
        m_funcPtrMap.clear();
    }

private:
    // Ç±Ç±Ç… boost::unordered_map<std::wstring, void const *> ÇÃÉÅÉìÉoÇ
    boost::unordered_map<std::wstring, void const *> m_funcPtrMap;
};
#endif

template<
    typename Key, 
    typename Value, 
    typename Hash = boost::hash<Key>, 
    typename Pred = std::equal_to<Key>, 
    typename Alloc = std::allocator<std::pair<Key const, Value>> 
> 
class GlobalSafeDictionary : boost::noncopyable
{
public:
    typedef typename boost::call_traits<Key>::param_type in_key_type;
    typedef typename boost::call_traits<Value>::param_type in_value_type;
    typedef typename boost::call_traits<Value>::reference out_value_type;

    static GlobalSafeDictionary &GetInstance()
    {
        static GlobalSafeDictionary im;
        return im;
    }

    BOOL TryAdd(in_key_type key, in_value_type value)
    {
        m_lock.Lock();
        BOOST_SCOPE_EXIT((&m_lock))
        {
            m_lock.Unlock();
        }
        BOOST_SCOPE_EXIT_END


        if (m_map.find(key) == m_map.end())
        {
            m_map[key] = value;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

    BOOL TryGet(in_key_type key, out_value_type rValue)
    {
        m_lock.Lock();
        BOOST_SCOPE_EXIT((&m_lock))
        {
            m_lock.Unlock();
        }
        BOOST_SCOPE_EXIT_END


        if (m_map.find(key) == m_map.end())
        {
            return FALSE;
        }
        else
        {
            rValue = m_map[key];
            return TRUE;
        }
    }

    void Unload()
    {
        m_lock.Lock();
        BOOST_SCOPE_EXIT((&m_lock))
        {
            m_lock.Unlock();
        }
        BOOST_SCOPE_EXIT_END

        
        m_map.clear();
    }

private:
    GlobalSafeDictionary() { }
    ATL::CComAutoCriticalSection m_lock;
    boost::unordered_map<Key, Value, Hash, Pred, Alloc> m_map;
};

#if 0
EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(BOOL) IndirectionGetFunctionPointer(IndirectionInfo *pInfo, void const **ppFuncPtr)
{
    using namespace boost;
    using namespace std;
    using namespace Urasandesu::CppAnonym;

    *ppFuncPtr = NULL;

    IndirectionManager const &indMngr = IndirectionManager::GetInstance();

    wstring asmName(pInfo->m_assemblyName);
    IndirectionManager::indirection_assembly_heap const &indAsmHeap = indMngr.Of<IndirectionAssemblyInfo>();
    IndirectionAssemblyInfo const *pIndAsmInfo = NULL;
    if (!indAsmHeap.Exists(asmName))
        return TRUE;
    pIndAsmInfo = indAsmHeap.Get(asmName);

    wstring typeFullName(pInfo->m_typeFullName);
    IndirectionAssemblyInfo::indirection_type_heap const &indTypeHeap = pIndAsmInfo->Of<IndirectionTypeInfo>();
    IndirectionTypeInfo const *pIndTypeInfo = NULL;
    if (!indTypeHeap.Exists(typeFullName))
        return TRUE;
    pIndTypeInfo = indTypeHeap.Get(typeFullName);

    wstring methodName(pInfo->m_methodName);
    IndirectionTypeInfo::indirection_method_heap const &indMethodHeap = pIndTypeInfo->Of<IndirectionMethodInfo>();
    IndirectionMethodInfo const *pIndMethodInfo = NULL;
    if (!indMethodHeap.Exists(methodName))
        return TRUE;
    pIndMethodInfo = indMethodHeap.Get(methodName);

    *ppFuncPtr = pIndMethodInfo->GetFunctionPointer();

    return TRUE;
}

EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(BOOL) IndirectionSetFunctionPointer(IndirectionInfo *pInfo, void const *pFuncPtr)
{
    using namespace boost;
    using namespace std;
    using namespace Urasandesu::CppAnonym;

    IndirectionManager &indMngr = IndirectionManager::GetInstance();

    wstring asmName(pInfo->m_assemblyName);
    IndirectionManager::indirection_assembly_heap &indAsmHeap = indMngr.Of<IndirectionAssemblyInfo>();
    IndirectionAssemblyInfo *pIndAsmInfo = NULL;
    pIndAsmInfo = indAsmHeap.Exists(asmName) ? indAsmHeap.Get(asmName) : indAsmHeap.New(asmName);

    wstring typeFullName(pInfo->m_typeFullName);
    IndirectionAssemblyInfo::indirection_type_heap &indTypeHeap = pIndAsmInfo->Of<IndirectionTypeInfo>();
    IndirectionTypeInfo *pIndTypeInfo = NULL;
    pIndTypeInfo = indTypeHeap.Exists(typeFullName) ? indTypeHeap.Get(typeFullName) : indTypeHeap.New(typeFullName);

    wstring methodName(pInfo->m_methodName);
    IndirectionTypeInfo::indirection_method_heap &indMethodHeap = pIndTypeInfo->Of<IndirectionMethodInfo>();
    IndirectionMethodInfo *pIndMethodInfo = NULL;
    pIndMethodInfo = indMethodHeap.Exists(methodName) ? indMethodHeap.Get(methodName) : indMethodHeap.New(methodName);

    pIndMethodInfo->SetFunctionPointer(pFuncPtr);

    return TRUE;
}
#endif

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
