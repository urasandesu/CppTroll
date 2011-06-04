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
            return CComVariant(*&*pFrom).Detach(pTo);
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
            return CComVariant(*pFrom).Detach(pTo);
        }
        static HRESULT copy(destination_type* pTo, const actual_source_type* pFrom)
        {
            return CComVariant(*pFrom).Detach(pTo);
        }
    }; // struct GenericCopy<VARIANT, CComBSTR>

    template<class SourceType>
    struct GenericCopy<BSTR, SourceType>
    {
        typedef BSTR destination_type;
        typedef SourceType source_type;

        static void init(destination_type* p)
        {
            *p = NULL;
        }
        static void destroy(destination_type* p)
        {
            CComBSTR().Attach(*p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            return CComBSTR(*&*pFrom).CopyTo(pTo);
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
            *p = NULL;
        }
        static void destroy(destination_type* p)
        {
            CComBSTR().Attach(*p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            return CComBSTR(*pFrom).CopyTo(pTo);
        }
        static HRESULT copy(destination_type* pTo, const actual_source_type* pFrom)
        {
            return CComBSTR(*pFrom).CopyTo(pTo);
        }

    }; // struct GenericCopy<BSTR, CComBSTR>

    template<class SourceType>
    struct GenericCopy<CComBSTR, SourceType>
    {
        typedef BSTR destination_type;
        typedef SourceType source_type;

        static void init(destination_type* p)
        {
            *p = NULL;
        }
        static void destroy(destination_type* p)
        {
            CComBSTR().Attach(*p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            return CComBSTR(*&*pFrom).CopyTo(pTo);
        }

    }; // struct GenericCopy<CComBSTR, SourceType>

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
            CComObject<pair_type>* pPair;   // pPair is not released here because it will be released by the caller.
            hr = CComObject<pair_type>::CreateInstance(&pPair);
            if (FAILED(hr))
            {
                return hr;
            }

            pair_first_type first;
            first_copy::init(&first);
            hr = first_copy::copy(&first, &pFrom->first);
            if (FAILED(hr))
            {
                goto RETURN_WITH_RELEASE;
            }

            hr = pPair->put_First(first);
            if (FAILED(hr))
            {
                goto RETURN_WITH_RELEASE;
            }

            pair_second_type second;
            second_copy::init(&second);
            hr = second_copy::copy(&second, &pFrom->second);
            if (FAILED(hr))
            {
                goto RETURN_WITH_RELEASE;
            }

            hr = pPair->put_Second(second);
            if (FAILED(hr))
            {
                goto RETURN_WITH_RELEASE;
            }

            hr = CComVariant(pPair).Detach(pTo);
            if (FAILED(hr))
            {
                goto RETURN_WITH_RELEASE;
            }

            return S_OK;

RETURN_WITH_RELEASE:
            pPair->Release();
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
