// MyCollectionGenerator.h : CMyCollectionGenerator �̐錾

#pragma once
#include "resource.h"       // ���C�� �V���{��

#include "Sample03_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM �̊��S�T�|�[�g���܂�ł��Ȃ� Windows Mobile �v���b�g�t�H�[���̂悤�� Windows CE �v���b�g�t�H�[���ł́A�P��X���b�h COM �I�u�W�F�N�g�͐������T�|�[�g����Ă��܂���BATL ���P��X���b�h COM �I�u�W�F�N�g�̍쐬���T�|�[�g���邱�ƁA����т��̒P��X���b�h COM �I�u�W�F�N�g�̎����̎g�p�������邱�Ƃ���������ɂ́A_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ���`���Ă��������B���g�p�� rgs �t�@�C���̃X���b�h ���f���� 'Free' �ɐݒ肳��Ă���ADCOM Windows CE �ȊO�̃v���b�g�t�H�[���ŃT�|�[�g�����B��̃X���b�h ���f���Ɛݒ肳��Ă��܂����B"
#endif


typedef std::vector<CAdapt<CComBSTR>> StrVector;
typedef My::CComEnumerator<IEnumVARIANT, VARIANT, My::GenericCopy<VARIANT, CAdapt<CComBSTR>>, StrVector> StrEnumerator;
typedef My::CComCollection<IStrVectorCollection, BSTR, StrEnumerator, StrVector, My::GenericCopy<BSTR, BSTR>> CStrVectorCollection;
typedef CComObject<CStrVectorCollection> CStrVectorCollectionObject;

// CMyCollectionGenerator

class ATL_NO_VTABLE CMyCollectionGenerator :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CMyCollectionGenerator, &CLSID_MyCollectionGenerator>,
    public IDispatchImpl<IMyCollectionGenerator, &IID_IMyCollectionGenerator, &LIBID_Sample03Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
    CMyCollectionGenerator()
    {
    }

DECLARE_REGISTRY_RESOURCEID(IDR_MYCOLLECTIONGENERATOR)


BEGIN_COM_MAP(CMyCollectionGenerator)
    COM_INTERFACE_ENTRY(IMyCollectionGenerator)
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

    STDMETHOD(CreateStrVectorCollection)(IStrVectorCollection** ppVal);
};

OBJECT_ENTRY_AUTO(__uuidof(MyCollectionGenerator), CMyCollectionGenerator)
