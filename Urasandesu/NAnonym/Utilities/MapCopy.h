#pragma once
#ifndef URASANDESU_NANONYM_UTILITIES_MAPCOPY_H
#define URASANDESU_NANONYM_UTILITIES_MAPCOPY_H

namespace Urasandesu { namespace NAnonym { namespace Utilities {

    template<
        class MapType, 
        class PairType,
        class FirstCopy = use_default,
        class SecondCopy = use_default
    >
    class MapCopy
    {
    public:
        typedef MapType map_type;
        typedef typename WithoutAdapt<typename map_type::key_type>::type map_first_type;
        typedef typename WithoutAdapt<typename map_type::mapped_type>::type map_second_type;

        typedef PairType pair_type;
        typedef typename WithoutAdapt<typename pair_type::first_type>::type pair_first_type;
        typedef typename WithoutAdapt<typename pair_type::second_type>::type pair_second_type;

        typedef GenericCopy<pair_first_type, map_first_type> default_first_copy;
        typedef typename Replace<FirstCopy, use_default, default_first_copy>::type first_copy;
        typedef GenericCopy<pair_second_type, map_second_type> default_second_copy;
        typedef typename Replace<SecondCopy, use_default, default_second_copy>::type second_copy;

        typedef VARIANT destination_type;
        typedef typename map_type::value_type source_type;

    private:
        BOOST_CONCEPT_ASSERT((ComPair<pair_type, pair_first_type, pair_second_type>));
        BOOST_CONCEPT_ASSERT((ATLCopy<first_copy, pair_first_type, map_first_type>));
        BOOST_CONCEPT_ASSERT((ATLCopy<second_copy, pair_second_type, map_second_type>));

    public:
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
            if (pFrom == NULL) return E_POINTER;
            
            HRESULT hr;
            CComObject<pair_type>* pPair = NULL;
            hr = CComObject<pair_type>::CreateInstance(&pPair);
            if (FAILED(hr)) return hr;

            CComPtr<IUnknown> pUnkForRelease(pPair);

            pair_first_type pair_first;
            first_copy::init(addressof(pair_first));
            const map_first_type& map_first = const_cast<source_type*>(pFrom)->first;
            hr = first_copy::copy(addressof(pair_first), addressof(map_first));
            if (FAILED(hr)) return hr;

            hr = pPair->put_First(pair_first);
            if (FAILED(hr)) return hr;

            pair_second_type pair_second;
            second_copy::init(addressof(pair_second));
            map_second_type& map_second = const_cast<source_type*>(pFrom)->second;
            hr = second_copy::copy(addressof(pair_second), addressof(map_second));
            if (FAILED(hr)) return hr;

            hr = pPair->put_Second(pair_second);
            if (FAILED(hr)) return hr;

            hr = CComVariant(pPair).Detach(pTo);    // Shallow copy. Relegating the memory management(the ref count, too).
            if (FAILED(hr)) return hr;

            return S_OK;
        }

    }; // struct MapCopy

}}}   // namespace Urasandesu { namespace NAnonym { namespace Utilities {

#endif  // #ifndef URASANDESU_NANONYM_UTILITIES_MAPCOPY_H