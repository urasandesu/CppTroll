#pragma once
#ifndef URASANDESU_NANONYM_UTILITIES_GENERICCOPY_H
#define URASANDESU_NANONYM_UTILITIES_GENERICCOPY_H

namespace Urasandesu { namespace NAnonym { namespace Utilities {

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
    };
    
    template<>
    struct GenericCopy<CComBSTR, BSTR>
    {
        typedef CComBSTR destination_type;
        typedef BSTR source_type;

        static void init(destination_type* p)
        {
            if (p != NULL) p->Empty();
        }
        static void destroy(destination_type* p)
        {
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            if (pTo == NULL || pFrom == NULL) return E_POINTER;
            *pTo = CComBSTR(*pFrom);
            return S_OK;
        }
    };
    
    template<>
    struct GenericCopy<BSTR, CComBSTR>
    {
        typedef BSTR destination_type;
        typedef CComBSTR source_type;

        static void init(destination_type* p)
        {
            if (p != NULL) *p = NULL;
        }
        static void destroy(destination_type* p)
        {
            if (p != NULL) CComBSTR().Attach(*p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            return CComBSTR(*pFrom).CopyTo(pTo);
        }
    };
    
    template<>
    struct GenericCopy<CComBSTR, CComBSTR>
    {
        typedef CComBSTR destination_type;
        typedef CComBSTR source_type;

        static void init(destination_type* p)
        {
            if (p != NULL) p->Empty();
        }
        static void destroy(destination_type* p)
        {
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            if (pTo == NULL || pFrom == NULL) return E_POINTER;
            *pTo = *pFrom;
            return S_OK;
        }
    };
  
    // Though _Copy<LPOLESTR> that is specialized to use BSTR has already existed, 
    // an access violation error was occurred when I used it in the managed code... :-<
    template<>
    struct GenericCopy<BSTR, BSTR>
    {
        typedef BSTR destination_type;
        typedef BSTR source_type;

        static void init(destination_type* p)
        {
            if (p != NULL) *p = NULL;
        }
        static void destroy(destination_type* p)
        {
            if (p != NULL) CComBSTR().Attach(*p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            return CComBSTR(*pFrom).CopyTo(pTo);
        }
    };
    
    template<class Interface>
    class GenericCopy<CComPtr<Interface>, Interface*>
    {
    private:
        BOOST_MPL_ASSERT((is_base_of<IUnknown, Interface>));
        
    public:
        typedef CComPtr<Interface> destination_type;
        typedef Interface* source_type;

        static void init(destination_type* p)
        {
            if (p != NULL) _CopyInterface<Interface>::init(&p->p);
        }
        static void destroy(destination_type* p)
        {
            if (p != NULL) _CopyInterface<Interface>::destroy(&p->p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            if (pTo == NULL) return E_POINTER;
            return _CopyInterface<Interface>::copy(&pTo->p, pFrom);
        }
    };
    
    template<class Interface>
    class GenericCopy<Interface*, CComPtr<Interface>>
    {
    private:
        BOOST_MPL_ASSERT((is_base_of<IUnknown, Interface>));
        
    public:
        typedef Interface* destination_type;
        typedef CComPtr<Interface> source_type;

        static void init(destination_type* p)
        {
            _CopyInterface<Interface>::init(p);
        }
        static void destroy(destination_type* p)
        {
            _CopyInterface<Interface>::destroy(p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            if (pFrom == NULL) return E_POINTER;
            return _CopyInterface<Interface>::copy(pTo, &pFrom->p);
        }
    };
    
    template<class Interface>
    class GenericCopy<CComPtr<Interface>, CComPtr<Interface>>
    {
    private:
        BOOST_MPL_ASSERT((is_base_of<IUnknown, Interface>));
        
    public:
        typedef CComPtr<Interface> destination_type;
        typedef CComPtr<Interface> source_type;

        static void init(destination_type* p)
        {
            if (p != NULL) _CopyInterface<Interface>::init(&p->p);
        }
        static void destroy(destination_type* p)
        {
            if (p != NULL) _CopyInterface<Interface>::destroy(&p->p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            if (pTo == NULL || pFrom == NULL) return E_POINTER;
            *pTo = *pFrom;
            return S_OK;
        }
    };
    
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
    };

    template<class DestinationType>
    struct GenericCopy<DestinationType, VARIANT>
    {
        typedef DestinationType destination_type;
        typedef VARIANT source_type;

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
            using Urasandesu::NAnonym::Traits::VariantTraits;
            
            if (pFrom == NULL) return E_POINTER;
            typedef VariantTraits<destination_type> destination_traits;
            destination_traits::return_type from = destination_traits::Val(*pFrom);
            return _Copy<destination_type>::copy(pTo, &from);
        }
    };
    
    template<>
    struct GenericCopy<VARIANT, VARIANT>
    {
        typedef VARIANT destination_type;
        typedef VARIANT source_type;

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
            return _Copy<destination_type>::copy(pTo, pFrom);
        }
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace Utilities {

#endif  // #ifndef URASANDESU_NANONYM_UTILITIES_GENERICCOPY_H