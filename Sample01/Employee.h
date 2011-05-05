// Employee.h : CEmployee �̐錾

#pragma once
#include "resource.h"       // ���C�� �V���{��

#include "Sample01_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM �̊��S�T�|�[�g���܂�ł��Ȃ� Windows Mobile �v���b�g�t�H�[���̂悤�� Windows CE �v���b�g�t�H�[���ł́A�P��X���b�h COM �I�u�W�F�N�g�͐������T�|�[�g����Ă��܂���BATL ���P��X���b�h COM �I�u�W�F�N�g�̍쐬���T�|�[�g���邱�ƁA����т��̒P��X���b�h COM �I�u�W�F�N�g�̎����̎g�p�������邱�Ƃ���������ɂ́A_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ���`���Ă��������B���g�p�� rgs �t�@�C���̃X���b�h ���f���� 'Free' �ɐݒ肳��Ă���ADCOM Windows CE �ȊO�̃v���b�g�t�H�[���ŃT�|�[�g�����B��̃X���b�h ���f���Ɛݒ肳��Ă��܂����B"
#endif



// CEmployee

class ATL_NO_VTABLE CEmployee :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEmployee, &CLSID_Employee>,
	public IDispatchImpl<IEmployee, &IID_IEmployee, &LIBID_Sample01Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
    CEmployee() : m_lId(0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EMPLOYEE)


BEGIN_COM_MAP(CEmployee)
	COM_INTERFACE_ENTRY(IEmployee)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

    STDMETHOD(get_Name)(BSTR* pVal);
    STDMETHOD(put_Name)(BSTR newVal);
    STDMETHOD(get_Id)(LONG* pVal);
    STDMETHOD(put_Id)(LONG newVal);

private:
    CComBSTR m_name;
    LONG m_lId;
};

OBJECT_ENTRY_AUTO(__uuidof(Employee), CEmployee)
