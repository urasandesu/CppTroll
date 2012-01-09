// ExeWeaver4.cpp : CExeWeaver4 ‚ÌŽÀ‘•

#include "stdafx.h"
#include "ExeWeaver4.h"


// CExeWeaver4
HRESULT CExeWeaver4::FinalConstruct()
{
    return S_OK;
}

void CExeWeaver4::FinalRelease()
{
}

HRESULT CExeWeaver4::InitializeCore(
    /* [in] */ IUnknown *pICorProfilerInfoUnk)
{
    using namespace std;
    using namespace Urasandesu::CppAnonym;
    HRESULT hr = E_FAIL;

    // Initialize the profiling API.
    hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo2, 
                                              reinterpret_cast<void**>(&m_pInfo));
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));


    // Set a value that specifies the types of events for which the profiler 
    // wants to receive notification from CLR.
    // NOTE: If you want to profile core APIs such as types in mscorlib, 
    //       you should set COR_PRF_USE_PROFILE_IMAGES.
    DWORD event_ = COR_PRF_MONITOR_MODULE_LOADS | 
                   COR_PRF_MONITOR_JIT_COMPILATION | 
                   COR_PRF_USE_PROFILE_IMAGES;
    hr = m_pInfo->SetEventMask(event_);
    if (FAILED(hr)) 
        BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));

    return S_OK;
}

HRESULT CExeWeaver4::ShutdownCore(void)
{ 
    using namespace std;
    using namespace boost;

    return S_OK; 
}
