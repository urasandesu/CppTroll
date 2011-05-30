// EmployeeCollection.cpp : CEmployeeCollection ‚ÌŽÀ‘•

#include "stdafx.h"
#include "EmployeeCollection.h"

#include "Employee.h"
#include <boost/range/adaptor/transformed.hpp>

// CEmployeeCollection


STDMETHODIMP CEmployeeCollection::Add(IEmployee* pVal)
{
    HRESULT hr;
    CComQIPtr<IEmployee> pEmployee(pVal);
    CComBSTR name;
    hr = pEmployee->get_Name(&name);
    ATLASSERT(SUCCEEDED(hr));
    ATLASSERT(0 < name.Length());
    m_coll[name] = pEmployee;
    return S_OK;
}

STDMETHODIMP CEmployeeCollection::get_Count(LONG* pVal)
{
    *pVal = m_coll.size();
    return S_OK;
}

STDMETHODIMP CEmployeeCollection::Item(VARIANT index, IEmployee** ppItem)
{
    if (index.vt == VT_I4)
    {
        if (index.lVal < 0 || m_coll.size() <= static_cast<size_t>(index.lVal))
        {
            return E_INVALIDARG;
        }

        INT n = 0;
        EmployeeMapItr i = m_coll.begin(), i_end = m_coll.end();
        for ( ; i != i_end; ++i, ++n)
        {
            if (n == index.llVal)
            {
                CComQIPtr<IEmployee> pEmployee((*i).second);
                *ppItem = pEmployee;
                return S_OK;
            }
        }
        return E_INVALIDARG;
    }
    else if (index.vt == VT_BSTR)
    {
        EmployeeMapItr i;
        i = m_coll.find(CComBSTR(index.bstrVal));
        VariantClear(&index);
        if (i == m_coll.end())
        {
            return E_INVALIDARG;
        }
        CComQIPtr<IEmployee> pEmployee((*i).second);
        *ppItem = pEmployee;
        return S_OK;
    }
    else
    {
        return E_INVALIDARG;
    }
}

STDMETHODIMP CEmployeeCollection::get__NewEnum(IUnknown** ppVal)
{
    // Let's make a version becoming the employee's ID to +1.
    using namespace std;
    using namespace boost::adaptors;

    struct AddIDPlus : 
        public unary_function<const EmployeePair&, EmployeePair>
    {
        explicit AddIDPlus(LONG value) : m_value(value) { }

        EmployeePair operator()(const EmployeePair& pair) const
        {
            HRESULT hr;

            CEmployeeObject* pEmployee;
            hr = CEmployeeObject::CreateInstance(&pEmployee);
            ATLASSERT(SUCCEEDED(hr));

            CComBSTR name;
            hr = pair.second->get_Name(&name);
            ATLASSERT(SUCCEEDED(hr));

            LONG id = 0;
            hr = pair.second->get_Id(&id);
            ATLASSERT(SUCCEEDED(hr));

            pEmployee->put_Name(name);
            pEmployee->put_Id(id + m_value);
            return EmployeePair(pair.first, pEmployee);
        }

        LONG m_value;
    };

    static EmployeeRange result;
    result = m_coll | transformed(AddIDPlus(1));
    return My::CreateRangeEnumerator<EmployeeEnumerator>(ppVal, this, result);
}
