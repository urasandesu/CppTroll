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
	    typedef SourceType		source_type;

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

    template <class MapType, class DestinationType = MapType::referent_type>
    class MapCopy
    {
    public :
	    typedef DestinationType destination_type;
	    typedef typename MapType::value_type source_type;
    	
	    typedef MapType map_type;
	    typedef typename MapType::referent_type	pseudosource_type;

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

    }; // class MapCopy
}   // namespace My
