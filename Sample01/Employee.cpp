// Employee.cpp : CEmployee の実装

#include "stdafx.h"
#include "Employee.h"


// CEmployee


STDMETHODIMP CEmployee::get_Name(BSTR* pVal)
{
    *pVal = m_name.Copy();
    return S_OK;
}

STDMETHODIMP CEmployee::put_Name(BSTR newVal)
{
    m_name = newVal;
    return S_OK;
}

STDMETHODIMP CEmployee::get_Id(LONG* pVal)
{
    *pVal = m_lId;
    return S_OK;
}

STDMETHODIMP CEmployee::put_Id(LONG newVal)
{
    m_lId = newVal;
    return S_OK;
}
