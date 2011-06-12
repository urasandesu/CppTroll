#pragma once
#ifndef INCLUDED_GENERICCOPY_H
#define INCLUDED_GENERICCOPY_H

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
        typedef SourceType* source_type;
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
            return _Copy<destination_type>::copy(pTo, &CComVariant(*pFrom));
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
}   // namespace My

#endif  // #ifndef INCLUDED_GENERICCOPY_H