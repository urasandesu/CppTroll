// EmployeeCollection.h : CEmployeeCollection �̐錾

#pragma once
#include "resource.h"       // ���C�� �V���{��

#include "Sample01_i.h"
#include "dllmain.h"

#include "Employee.h"
#include "ComUtilities.h"
#include "CComEnumOnRange.h"
#include "Copies.h"
#include "AnyRanges.h"
#include <map>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM �̊��S�T�|�[�g���܂�ł��Ȃ� Windows Mobile �v���b�g�t�H�[���̂悤�� Windows CE �v���b�g�t�H�[���ł́A�P��X���b�h COM �I�u�W�F�N�g�͐������T�|�[�g����Ă��܂���BATL ���P��X���b�h COM �I�u�W�F�N�g�̍쐬���T�|�[�g���邱�ƁA����т��̒P��X���b�h COM �I�u�W�F�N�g�̎����̎g�p�������邱�Ƃ���������ɂ́A_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ���`���Ă��������B���g�p�� rgs �t�@�C���̃X���b�h ���f���� 'Free' �ɐݒ肳��Ă���ADCOM Windows CE �ȊO�̃v���b�g�t�H�[���ŃT�|�[�g�����B��̃X���b�h ���f���Ɛݒ肳��Ă��܂����B"
#endif


typedef std::map<CComBSTR, EmployeePtr> EmployeeMap;
typedef EmployeeMap::iterator EmployeeMapItr;
typedef EmployeeMap::value_type EmployeePair;
typedef My::MapCopy2nd<EmployeeMap, VARIANT> CopyType;
typedef My::SinglePassCopyAnyRangeGenerator<EmployeeMap>::type EmployeeRange;
typedef My::CComEnumOnRange<IEnumVARIANT, VARIANT, CopyType, EmployeeRange> EmployeeEnumerator;


// CEmployeeCollection

class ATL_NO_VTABLE CEmployeeCollection :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEmployeeCollection, &CLSID_EmployeeCollection>,
	public IDispatchImpl<IEmployeeCollection, &IID_IEmployeeCollection, &LIBID_Sample01Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CEmployeeCollection()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EMPLOYEECOLLECTION)


BEGIN_COM_MAP(CEmployeeCollection)
	COM_INTERFACE_ENTRY(IEmployeeCollection)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
        EmployeeMap _coll;
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

    STDMETHOD(Add)(IEmployee* pVal);
    STDMETHOD(get_Count)(LONG* pVal);
    STDMETHOD(Item)(VARIANT index, IEmployee** ppItem);
    STDMETHOD(get__NewEnum)(IUnknown** ppVal);

private:
    EmployeeMap m_coll;
};

OBJECT_ENTRY_AUTO(__uuidof(EmployeeCollection), CEmployeeCollection)
