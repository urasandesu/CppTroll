#pragma once
#include "Concepts.h"
#include "AnyRanges.h"
#include "Traits.h"

namespace My
{
    template <class Base, class T, class Copy, class RangeType, class ThreadModel = CComObjectThreadModel>
    class ATL_NO_VTABLE CComEnumerator :
        public IEnumOnSTLImpl<Base, &__uuidof(Base), T, Copy, RangeType>,
        public CComObjectRootEx<ThreadModel>
    {
    public:
        typedef CComEnumOnSTL<Base, &__uuidof(Base), T, Copy, RangeType, ThreadModel> _CComEnum;
        typedef IEnumOnSTLImpl<Base, &__uuidof(Base), T, Copy, RangeType> _CComEnumBase;
        BEGIN_COM_MAP(_CComEnum)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), _CComEnumBase)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComEnumerator

    template <class EnumType, class RangeType>
    HRESULT CreateRangeEnumerator(IUnknown** ppUnk, IUnknown* pUnkForRelease, RangeType& range)
    {
        using namespace boost;

        BOOST_MPL_ASSERT((is_convertible<EnumType, AddImplicitConversion<IgnoreParam5<CComEnumerator>>>));
        BOOST_CONCEPT_ASSERT((SinglePassRangeConcept<RangeType>));

        if (ppUnk == NULL)
            return E_POINTER;
        *ppUnk = NULL;

        CComObject<EnumType>* pEnum = NULL;
        HRESULT hr = CComObject<EnumType>::CreateInstance(&pEnum);

        if (FAILED(hr))
            return hr;

        hr = pEnum->Init(pUnkForRelease, range);

        if (SUCCEEDED(hr))
            hr = pEnum->QueryInterface(ppUnk);

        if (FAILED(hr))
            pEnum->Release();

        return hr;
    } // HRESULT CreateRangeEnumerator(IUnknown** ppUnk, IUnknown* pUnkForRelease, RangeType& range)

    template<
        class Base,
        class EnumType, 
        class RangeType
    >
    class ATL_NO_VTABLE IEnumerableImpl : 
        public Base
    {
        BOOST_CONCEPT_ASSERT((ComEnumerable<Base>));
        BOOST_CONCEPT_ASSERT((boost::SinglePassRangeConcept<RangeType>));

    public:
        STDMETHOD(get__NewEnum)(IUnknown** ppVal)
        {
            return My::CreateRangeEnumerator<EnumType>(ppVal, this, m_coll);
        }

        RangeType m_coll;
    };  // class ATL_NO_VTABLE IEnumerableImpl

    template<
        class Base, 
        class EnumType, 
        class RangeType,
        const GUID* plibid = &CAtlModule::m_libid,
        WORD wMajor = 1,
        WORD wMinor = 0, 
        class tihclass = CComTypeInfoHolder,
        class ThreadModel = CComObjectThreadModel
    >
    class ATL_NO_VTABLE CComEnumerable :
        public CComObjectRootEx<ThreadModel>,
        public IDispatchImpl<IEnumerableImpl<Base, EnumType, RangeType>, &__uuidof(Base), plibid, wMajor, wMinor, tihclass>
    {
    public:
        typedef CComEnumerable<Base, EnumType, RangeType, plibid, wMajor, wMinor, tihclass, ThreadModel> _CComEnumerable;
        typedef IEnumerableImpl<Base, EnumType, RangeType> _CComEnumerableBase;
        BEGIN_COM_MAP(_CComEnumerable)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), _CComEnumerableBase)
            COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComEnumerable

    template<
        class Base,
        class ItemType,
        class EnumType, 
        class CollectionType,
        class ItemCopy = _Copy<ItemType>
    >
    class ATL_NO_VTABLE ICollectionImpl : 
        public IEnumerableImpl<Base, EnumType, CollectionType>
    {
        BOOST_CONCEPT_ASSERT((ComCollection<Base, ItemType>));
        BOOST_CONCEPT_ASSERT((boost::Mutable_RandomAccessContainer<CollectionType>));
        BOOST_CONCEPT_ASSERT((boost::Sequence<CollectionType>));
        BOOST_CONCEPT_ASSERT((ATLCopy<ItemCopy, typename WithoutAdapt<typename CollectionType::value_type>::type, ItemType>));

    public:
        typedef typename WithoutAdapt<typename CollectionType::value_type>::type range_value_type;
        typedef typename CollectionType::iterator range_iterator;

        STDMETHOD(Add)(ItemType item)
        {
            HRESULT hr = E_FAIL;
            range_value_type value;
            hr = ItemCopy::copy(&value, &item);
            if (FAILED(hr))
            {
                return hr;
            }
            m_coll.insert(m_coll.end(), value);
            return S_OK;
        }

        STDMETHOD(Clear)(void)
        {
            m_coll.erase(m_coll.begin(), m_coll.end());
            return S_OK;
        }

        STDMETHOD(Contains)(ItemType item, VARIANT_BOOL* exists)
        {
            range_iterator i = m_coll.begin(), i_end = m_coll.end();
            range_iterator result = find(i, i_end, item);
            if (result != i_end)
            {
                *exists = VARIANT_TRUE;
                return S_OK;
            }
            else
            {
                *exists = VARIANT_FALSE;
                return S_FALSE;
            }
        }

        STDMETHOD(CopyTo)(SAFEARRAY* pArray, LONG index)
        {
            HRESULT hr;

            CComSafeArray<ItemType> arr;
            hr = arr.Attach(pArray);
            if (FAILED(hr))
            {
                return hr;
            }

            for (range_iterator i = m_coll.begin(), i_end = m_coll.end(); i != i_end; ++i, ++index)
            {
                range_value_type& _i = *i;
                hr = arr.SetAt(index, _i);
                if (FAILED(hr))
                {
                    return hr;
                }
            }

            arr.Detach();
            return S_OK;
        }

        STDMETHOD(Remove)(ItemType item)
        {
            range_iterator i = m_coll.begin(), i_end = m_coll.end();
            range_iterator result = find(i, i_end, item);
            if (result != i_end)
            {
                m_coll.erase(result);
            }

            return S_OK;
        }

        STDMETHOD(get_Count)(LONG* pVal)
        {
            *pVal = m_coll.size();
            return S_OK;
        }

        STDMETHOD(get_IsReadOnly)(VARIANT_BOOL* pVal)
        {
            *pVal = VARIANT_FALSE;
            return S_OK;
        }

        STDMETHOD(get_Item)(LONG index, ItemType* pVal)
        {
            if (index < 0 || m_coll.size() <= static_cast<ULONG>(index))
            {
                return E_INVALIDARG;
            }

            range_value_type& item = m_coll[index];
            return ItemCopy::copy(pVal, &item);
        }

        STDMETHOD(put_Item)(LONG index, ItemType newVal)
        {
            if (index < 0 || m_coll.size() <= static_cast<ULONG>(index))
            {
                return E_INVALIDARG;
            }

            HRESULT hr = E_FAIL;
            range_value_type value;
            hr = ItemCopy::copy(&value, &newVal);
            if (FAILED(hr))
            {
                return hr;
            }
            m_coll[index] = value;
            return S_OK;
        }

    };  // class ATL_NO_VTABLE ICollectionImpl

    template<
        class Base, 
        class ItemType,
        class EnumType, 
        class RangeType,
        class ItemCopy = _Copy<ItemType>,
        const GUID* plibid = &CAtlModule::m_libid,
        WORD wMajor = 1,
        WORD wMinor = 0, 
        class tihclass = CComTypeInfoHolder,
        class ThreadModel = CComObjectThreadModel
    >
    class ATL_NO_VTABLE CComCollection :
        public CComObjectRootEx<ThreadModel>,
        public IDispatchImpl<ICollectionImpl<Base, ItemType, EnumType, RangeType, ItemCopy>, &__uuidof(Base), plibid, wMajor, wMinor, tihclass>
    {
    public:
        typedef CComCollection<Base, ItemType, EnumType, RangeType, ItemCopy, plibid, wMajor, wMinor, tihclass, ThreadModel> _CComCollection;
        typedef ICollectionImpl<Base, ItemType, EnumType, RangeType, ItemCopy> _CComCollectionBase;
        BEGIN_COM_MAP(_CComCollection)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), _CComCollectionBase)
            COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComCollection

}   // namespace My