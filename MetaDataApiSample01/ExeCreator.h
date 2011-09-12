// ExeCreator.h : CExeCreator �̐錾

#pragma once
#include "resource.h"       // ���C�� �V���{��

#include "MetaDataApiSample01_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM �̊��S�T�|�[�g���܂�ł��Ȃ� Windows Mobile �v���b�g�t�H�[���̂悤�� Windows CE �v���b�g�t�H�[���ł́A�P��X���b�h COM �I�u�W�F�N�g�͐������T�|�[�g����Ă��܂���BATL ���P��X���b�h COM �I�u�W�F�N�g�̍쐬���T�|�[�g���邱�ƁA����т��̒P��X���b�h COM �I�u�W�F�N�g�̎����̎g�p�������邱�Ƃ���������ɂ́A_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ���`���Ă��������B���g�p�� rgs �t�@�C���̃X���b�h ���f���� 'Free' �ɐݒ肳��Ă���ADCOM Windows CE �ȊO�̃v���b�g�t�H�[���ŃT�|�[�g�����B��̃X���b�h ���f���Ɛݒ肳��Ă��܂����B"
#endif



// CExeCreator

class ATL_NO_VTABLE CExeCreator :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExeCreator, &CLSID_ExeCreator>,
    public ISupportErrorInfo,
	public IDispatchImpl<IExeCreator, &IID_IExeCreator, &LIBID_MetaDataApiSample01Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CExeCreator()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EXECREATOR)


BEGIN_COM_MAP(CExeCreator)
	COM_INTERFACE_ENTRY(IExeCreator)
	COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

    typedef CComCoClass<CExeCreator, &CLSID_ExeCreator> BaseCoClass; 
	HRESULT SystemError(DWORD errorNo);
	HRESULT COMError(HRESULT hr);


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

    STDMETHOD(Create)(BSTR fileName);
};

OBJECT_ENTRY_AUTO(__uuidof(ExeCreator), CExeCreator)