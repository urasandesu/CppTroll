#pragma once
#include <atlbase.h>
#include <atlcom.h>

namespace My
{
    template<class DestinationType, class SourceType = DestinationType>
    struct GenericCopy
    {
        typedef DestinationType destination_type;
        typedef SourceType source_type;

        static void init(destination_type* p)
        {
            _Copy<destination_type>::init(p);
        }
        static void destroy(destination_type* p)
        {
            _Copy<destination_type>::destroy(p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            return _Copy<destination_type>::copy(pTo, const_cast<source_type*>(pFrom));
        }
    }; // struct GenericCopy

    template<class SourceType>
    struct GenericCopy<VARIANT, SourceType>
    {
        typedef VARIANT destination_type;
        typedef SourceType source_type;

        static void init(destination_type* p)
        {
            _Copy<destination_type>::init(p);
        }
        static void destroy(destination_type* p)
        {
            _Copy<destination_type>::destroy(p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            return _Copy<destination_type>::copy(pTo, &CComVariant(*pFrom));
        }
    }; // struct GenericCopy<VARIANT, SourceType>

    template<>
    struct GenericCopy<VARIANT, CComBSTR>
    {
        typedef VARIANT destination_type;
        typedef BSTR source_type;
        typedef CComBSTR actual_source_type;

        static void init(destination_type* p)
        {
            _Copy<destination_type>::init(p);
        }
        static void destroy(destination_type* p)
        {
            _Copy<destination_type>::destroy(p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            return _Copy<destination_type>::copy(pTo, &CComVariant(*pFrom));
        }
        static HRESULT copy(destination_type* pTo, const actual_source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            return _Copy<destination_type>::copy(pTo, &CComVariant(*pFrom));
        }
    }; // struct GenericCopy<VARIANT, CComBSTR>

    template<class SourceType>
    struct GenericCopy<VARIANT, CComPtr<SourceType>>
    {
        typedef VARIANT destination_type;
        typedef SourceType source_type;
        typedef CComPtr<SourceType> actual_source_type;

        static void init(destination_type* p)
        {
            _Copy<destination_type>::init(p);
        }
        static void destroy(destination_type* p)
        {
            _Copy<destination_type>::destroy(p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            return _Copy<destination_type>::copy(pTo, &CComVariant(const_cast<source_type*>(pFrom)));
        }
        static HRESULT copy(destination_type* pTo, const actual_source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            return _Copy<destination_type>::copy(pTo, &CComVariant((*pFrom).p));
        }
    }; // GenericCopy<VARIANT, CComPtr<SourceType>>

    template<class SourceType>
    struct GenericCopy<BSTR, SourceType>
    {
        typedef BSTR destination_type;
        typedef SourceType source_type;

        static void init(destination_type* p)
        {
            if (p != NULL)
                *p = NULL;
        }
        static void destroy(destination_type* p)
        {
            if (p != NULL)
                CComBSTR().Attach(*p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            return CComBSTR(*pFrom).CopyTo(pTo);
        }

    }; // struct GenericCopy<BSTR, SourceType>

    template<>
    struct GenericCopy<BSTR, CComBSTR>
    {
        typedef BSTR destination_type;
        typedef BSTR source_type;
        typedef CComBSTR actual_source_type;

        static void init(destination_type* p)
        {
            if (p != NULL)
                *p = NULL;
        }
        static void destroy(destination_type* p)
        {
            if (p != NULL)
                CComBSTR().Attach(*p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            return CComBSTR(*pFrom).CopyTo(pTo);
        }
        static HRESULT copy(destination_type* pTo, const actual_source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            return CComBSTR(*pFrom).CopyTo(pTo);
        }

    }; // struct GenericCopy<BSTR, CComBSTR>

    template<class SourceType>
    struct GenericCopy<CComBSTR, SourceType>
    {
        typedef BSTR destination_type;
        typedef CComBSTR actual_destination_type;
        typedef SourceType source_type;

        static void init(destination_type* p)
        {
            if (p != NULL)
                *p = NULL;
        }
        static void init(actual_destination_type* p)
        {
            if (p != NULL)
                p->Empty();
        }
        static void destroy(destination_type* p)
        {
            if (p != NULL)
                CComBSTR().Attach(*p);
        }
        static void destroy(actual_destination_type* p)
        {
            if (p != NULL)
            {
                delete p;
                p = NULL;
            }
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            return CComBSTR(*pFrom).CopyTo(pTo);
        }
        static HRESULT copy(actual_destination_type* pTo, const source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            pTo = new CComBSTR(*pFrom);
            return S_OK;
        }

    }; // struct GenericCopy<CComBSTR, SourceType>

    template<class SourceType>
    struct GenericCopy<SourceType*, CComPtr<SourceType>>
    {
        typedef SourceType* destination_type;
        typedef SourceType* source_type;
        typedef CComPtr<SourceType> actual_source_type;

        static void init(destination_type* p)
        {
            _CopyInterface<SourceType>::init(p);
        }
        static void destroy(destination_type* p)
        {
            _CopyInterface<SourceType>::destroy(p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            return _CopyInterface<SourceType>::copy(pTo, pFrom);
        }
        static HRESULT copy(destination_type* pTo, const actual_source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            return _CopyInterface<SourceType>::copy(pTo, &*const_cast<actual_source_type*>(pFrom));
        }

    }; // struct GenericCopy<SourceType*, CComPtr<SourceType>>


    template<class DestinationType>
    struct GenericCopy<CComPtr<DestinationType>, DestinationType*>
    {
        typedef DestinationType* destination_type;
        typedef CComPtr<DestinationType> actual_destination_type;
        typedef DestinationType* source_type;

        static void init(destination_type* p)
        {
            _CopyInterface<DestinationType>::init(p);
        }
        static void init(actual_destination_type* p)
        {
            if (p != NULL)
                *p = NULL;
        }
        static void destroy(destination_type* p)
        {
            _CopyInterface<DestinationType>::destroy(p);
        }
        static void destroy(actual_destination_type* p)
        {
            if (p != NULL)
            {
                delete p;
                p = NULL;
            }
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            return _CopyInterface<DestinationType>::copy(pTo, pFrom);
        }
        static HRESULT copy(actual_destination_type* pTo, const source_type* pFrom)
        {
            pTo = new CComPtr<DestinationType>();
            return _CopyInterface<DestinationType>::copy(&*pTo, pFrom);
        }

    }; // struct GenericCopy<CComPtr<DestinationType>, DestinationType*>

    template<
        class MapType, 
        class PairType,
        class FirstCopy = GenericCopy<typename PairType::first_type, typename MapType::key_type>, 
        class SecondCopy = GenericCopy<typename PairType::second_type, typename MapType::mapped_type>
    >
    struct MapCopy
    {
        typedef MapType map_type;
        typedef typename map_type::key_type map_first_type;
        typedef typename map_type::mapped_type map_second_type;

        typedef PairType pair_type;
        typedef typename pair_type::first_type pair_first_type;
        typedef typename pair_type::second_type pair_second_type;

        typedef FirstCopy first_copy;
        typedef SecondCopy second_copy;

        typedef VARIANT destination_type;
        typedef typename map_type::value_type source_type;

        BOOST_CONCEPT_ASSERT((ComPair<pair_type, pair_first_type, pair_second_type>));
        BOOST_CONCEPT_ASSERT((ATLCopy<first_copy, pair_first_type, map_first_type>));
        BOOST_CONCEPT_ASSERT((ATLCopy<second_copy, pair_second_type, map_second_type>));

        static void init(destination_type* p)
        {
            GenericCopy<destination_type, source_type>::init(p);
        }
        static void destroy(destination_type* p)
        {
            GenericCopy<destination_type, source_type>::destroy(p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            HRESULT hr;
            CComObject<pair_type>* pPair = NULL;
            hr = CComObject<pair_type>::CreateInstance(&pPair);
            if (FAILED(hr)) return hr;

            CComPtr<IUnknown> pUnkForRelease;
            pUnkForRelease.Attach(pPair);

            pair_first_type first;
            first_copy::init(&first);
            hr = first_copy::copy(&first, &pFrom->first);
            if (FAILED(hr)) goto RETURN_WITH_RELEASE;

            hr = pPair->put_First(first);
            if (FAILED(hr)) goto RETURN_WITH_RELEASE;

            pair_second_type second;
            second_copy::init(&second);
            hr = second_copy::copy(&second, &pFrom->second);
            if (FAILED(hr)) goto RETURN_WITH_RELEASE;

            hr = pPair->put_Second(second);
            if (FAILED(hr)) goto RETURN_WITH_RELEASE;

            hr = CComVariant(pPair).Detach(pTo);    // Shallow copy. Relegating the memory management(the ref count, too).
            if (FAILED(hr)) goto RETURN_WITH_RELEASE;

            pUnkForRelease.Detach();
            return S_OK;

RETURN_WITH_RELEASE:
            return hr;
        }

    }; // struct MapCopy

    template<class MapType, class DestinationType = MapType::mapped_type>
    struct MapCopy2nd
    {
        typedef MapType map_type;
        typedef typename map_type::mapped_type map_second_type;

        typedef DestinationType destination_type;
        typedef typename map_type::value_type source_type;
        
        static void init(destination_type* p)
        {
            GenericCopy<destination_type, map_second_type>::init(p);
        }
        static void destroy(destination_type* p)
        {
            GenericCopy<destination_type, map_second_type>::destroy(p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            return GenericCopy<destination_type, map_second_type>::copy(pTo, &(pFrom->second));
        }

    }; // struct MapCopy2nd
}   // namespace My
