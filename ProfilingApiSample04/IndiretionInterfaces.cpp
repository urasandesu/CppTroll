#include "StdAfx.h"
#include "IndiretionInterfaces.h"

#ifndef URASANDESU_CPPANONYM_HEAPPROVIDER_H
#include <Urasandesu/CppAnonym/HeapProvider.h>
#endif

#if 0
class IndirectionMethodInfo : 
    public Urasandesu::CppAnonym::IHeapContent<std::wstring>
{
public:
    IndirectionMethodInfo() : m_funcPtr(0) { }
private:
    INT m_funcPtr;
};

class IndirectionTypeInfo : 
    public Urasandesu::CppAnonym::IHeapContent<std::wstring>
{
    CPPANONYM_BEGIN_HEAP_PROVIDER_DECLARATION()
        CPPANONYM_HEAP_PROVIDER(IndirectionMethodInfo, std::wstring, m_pIndMethodFactory);
    CPPANONYM_END_HEAP_PROVIDER_DECLARATION()
};

class IndirectionAssemblyInfo : 
    public Urasandesu::CppAnonym::IHeapContent<std::wstring>
{
    CPPANONYM_BEGIN_HEAP_PROVIDER_DECLARATION()
        CPPANONYM_HEAP_PROVIDER(IndirectionTypeInfo, std::wstring, m_pIndTypeFactory);
    CPPANONYM_END_HEAP_PROVIDER_DECLARATION()
};

class IndiretionManager
{
    CPPANONYM_BEGIN_HEAP_PROVIDER_DECLARATION()
        CPPANONYM_HEAP_PROVIDER(IndirectionAssemblyInfo, std::wstring, m_pIndAsmFactory);
    CPPANONYM_END_HEAP_PROVIDER_DECLARATION()

public:
    static IndiretionManager const &GetInstance()
    {
        static IndiretionManager im;
        return im;
    }
};
#endif

EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(BOOL) IndiretionGetFunctionPointer(IndiretionInfo *pInfo, INT *pFuncPtr)
{
    using namespace std;
    using namespace boost;

    cout << "IndiretionGetFunctionPointer" << endl;

    return TRUE;
}

EXTERN_C URASANDESU_PRIG_API STDMETHODIMP_(BOOL) IndiretionSetFunctionPointer(IndiretionInfo *pInfo, INT funcPtr)
{
    using namespace std;
    using namespace boost;

    //IndiretionManager const &indMngr = IndiretionManager::GetInstance();
    //IndirectionAssemblyInfo *pIndAsmInfo = indMngr.New<IndirectionAssemblyInfo>(std::wstring(pInfo->m_assemblyName));

    cout << "IndiretionGetFunctionPointer" << endl;

    return TRUE;
}
