#pragma once
#ifndef INCLUDED_MAPCOPY_H
#define INCLUDED_MAPCOPY_H

namespace My
{
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

            CComPtr<IUnknown> pUnkForRelease(pPair);

            pair_first_type first;
            first_copy::init(&first);
            hr = first_copy::copy(&first, &pFrom->first);
            if (FAILED(hr)) return hr;

            hr = pPair->put_First(first);
            if (FAILED(hr)) return hr;

            pair_second_type second;
            second_copy::init(&second);
            hr = second_copy::copy(&second, &pFrom->second);
            if (FAILED(hr)) return hr;

            hr = pPair->put_Second(second);
            if (FAILED(hr)) return hr;

            hr = CComVariant(pPair).Detach(pTo);    // Shallow copy. Relegating the memory management(the ref count, too).
            if (FAILED(hr)) return hr;

            return S_OK;
        }

    }; // struct MapCopy
}   // namespace My

#endif  // #ifndef INCLUDED_MAPCOPY_H