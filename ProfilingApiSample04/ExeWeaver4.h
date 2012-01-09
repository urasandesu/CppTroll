// ExeWeaver4.h : CExeWeaver4 �̐錾

#pragma once
#include "resource.h"       // ���C�� �V���{��



#include "ProfilingApiSample04_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM �̊��S�T�|�[�g���܂�ł��Ȃ� Windows Mobile �v���b�g�t�H�[���̂悤�� Windows CE �v���b�g�t�H�[���ł́A�P��X���b�h COM �I�u�W�F�N�g�͐������T�|�[�g����Ă��܂���BATL ���P��X���b�h COM �I�u�W�F�N�g�̍쐬���T�|�[�g���邱�ƁA����т��̒P��X���b�h COM �I�u�W�F�N�g�̎����̎g�p�������邱�Ƃ���������ɂ́A_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ���`���Ă��������B���g�p�� rgs �t�@�C���̃X���b�h ���f���� 'Free' �ɐݒ肳��Ă���ADCOM Windows CE �ȊO�̃v���b�g�t�H�[���ŃT�|�[�g�����B��̃X���b�h ���f���Ɛݒ肳��Ă��܂����B"
#endif

using namespace ATL;


// CExeWeaver4
#ifdef UNP
#error This .h temporarily reserves the word "UNP" that means "Urasandesu::CppAnonym::Profiling".
#else
#define UNP Urasandesu::CppAnonym::Profiling

class ATL_NO_VTABLE CExeWeaver4 :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CExeWeaver4, &CLSID_ExeWeaver4>,
    public UNP::ICorProfilerCallback2Impl<ICorProfilerCallback2>,
	public IDispatchImpl<IExeWeaver4, &IID_IExeWeaver4, &LIBID_ProfilingApiSample04Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CExeWeaver4()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EXEWEAVER4)


BEGIN_COM_MAP(CExeWeaver4)
	COM_INTERFACE_ENTRY(IExeWeaver4)
	COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ICorProfilerCallback2)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct();

    void FinalRelease();

protected:
    STDMETHOD(InitializeCore)(
        /* [in] */ IUnknown *pICorProfilerInfoUnk);

    STDMETHOD(ShutdownCore)(void);

private:
    ATL::CComPtr<ICorProfilerInfo2> m_pInfo;
};

OBJECT_ENTRY_AUTO(__uuidof(ExeWeaver4), CExeWeaver4)

#undef UNP
#endif
