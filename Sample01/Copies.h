#pragma once
#include <atlbase.h>
#include <atlcom.h>

namespace My
{
    template <class DestinationType, class SourceType = DestinationType>
    class GenericCopy
    {
    public :
	    typedef DestinationType	destination_type;
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

    }; // class GenericCopy

    template <class DestinationType, class SourceType>
    class GenericCopy<DestinationType, CAdapt<SourceType>>
    {
    public :
	    typedef DestinationType destination_type;
	    typedef CAdapt<SourceType> source_type;

	    static void init(destination_type* p)
	    {
		    GenericCopy<destination_type>::init(p);
	    }
	    static void destroy(destination_type* p)
	    {
		    GenericCopy<destination_type>::destroy(p);
	    }
	    static HRESULT copy(destination_type* pTo, const source_type* pFrom)
	    {
            return GenericCopy<destination_type>::copy(pTo, &(const_cast<source_type*>(pFrom)->m_T));
	    }

    }; // class GenericCopy<DestinationType, CAdapt<SourceType>>

    template <class SourceType>
    class GenericCopy<VARIANT, CComPtr<SourceType>>
    {
    public :
	    typedef VARIANT destination_type;
	    typedef CComPtr<SourceType> source_type;

	    static void init(destination_type* p)
	    {
		    GenericCopy<destination_type>::init(p);
	    }
	    static void destroy(destination_type* p)
	    {
		    GenericCopy<destination_type>::destroy(p);
	    }
	    static HRESULT copy(destination_type* pTo, const source_type* pFrom)
	    {
		    return CComVariant(*pFrom).Detach(pTo);
	    }

    }; // class GenericCopy<VARIANT, CComQIPtr<SourceType>>

    template <class SourceType>
    class GenericCopy<VARIANT, CComQIPtr<SourceType>>
    {
    public :
	    typedef VARIANT destination_type;
	    typedef CComQIPtr<SourceType> source_type;

	    static void init(destination_type* p)
	    {
		    GenericCopy<destination_type>::init(p);
	    }
	    static void destroy(destination_type* p)
	    {
		    GenericCopy<destination_type>::destroy(p);
	    }
	    static HRESULT copy(destination_type* pTo, const source_type* pFrom)
	    {
		    return CComVariant(*pFrom).Detach(pTo);
	    }

    }; // class GenericCopy<VARIANT, CComQIPtr<SourceType>>

    template <>
    class GenericCopy<BSTR, BSTR>
    {
    public :
	    typedef BSTR destination_type;
	    typedef BSTR source_type;

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

    }; // class GenericCopy<BSTR, BSTR>

    template <
        class MapType, 
        class PairType,
        class FirstCopy = GenericCopy<typename PairType::first_type, typename MapType::key_type>, 
        class SecondCopy = GenericCopy<typename PairType::second_type, typename MapType::mapped_type>
    >
    class MapCopy
    {
    public :
	    typedef VARIANT destination_type;
        typedef MapType map_type;
	    typedef typename MapType::value_type source_type;

        typedef PairType pair_type;
        typedef typename pair_type::first_type first_type;
        typedef typename pair_type::second_type second_type;

        //BOOST_CONCEPT_ASSERT((PairOf<pair_type, key_type, mapped_type>));

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
            pair_type* p;
            hr = pair_type::CreateInstance(&p);
            if (FAILED(hr))
            {
                return hr;
            }

            first_type first;
            hr = FirstCopy::copy(&first, &pFrom->first);
            if (FAILED(hr))
            {
                goto RETURN_FAILED;
            }

            hr = p->put_First(first);
            if (FAILED(hr))
            {
                goto RETURN_FAILED;
            }

            second_type second;
            hr = SecondCopy::copy(&second, &pFrom->second);
            if (FAILED(hr))
            {
                goto RETURN_FAILED;
            }

            hr = p->put_Second(second);
            if (FAILED(hr))
            {
                goto RETURN_FAILED;
            }

            hr = CComVariant(p).Detach(pTo);
            if (FAILED(hr))
            {
                goto RETURN_FAILED;
            }

            return S_OK;

RETURN_FAILED:
            p->Release();
            return hr;
	    }

    }; // class MapCopy

    template <class MapType, class DestinationType = MapType::mapped_type>
    class MapCopy2nd
    {
    public :
	    typedef DestinationType destination_type;
	    typedef typename MapType::value_type source_type;
    	
	    typedef MapType map_type;
	    typedef typename MapType::mapped_type pseudosource_type;

	    static void init(destination_type* p)
	    {
		    GenericCopy<destination_type, pseudosource_type>::init(p);
	    }
	    static void destroy(destination_type* p)
	    {
		    GenericCopy<destination_type, pseudosource_type>::destroy(p);
	    }
	    static HRESULT copy(destination_type* pTo, const source_type* pFrom)
	    {
		    return GenericCopy<destination_type, pseudosource_type>::copy(pTo, &(pFrom->second));
	    }

    }; // class MapCopy2nd
}   // namespace My
