#pragma once
#ifndef URASANDESU_NANONYM_TRAITS_ADDRESSEXTRACTOR_H
#define URASANDESU_NANONYM_TRAITS_ADDRESSEXTRACTOR_H

namespace Urasandesu { namespace NAnonym { namespace Traits {

    template<class T>
    struct AddressExtractor
    {
        typedef T source_type;
        typedef T* result_type;
        inline static result_type Apply(source_type& val)
        {
            return &val;
        }
    };  // struct AddressExtractor

    template<>
    struct AddressExtractor<CComBSTR>
    {
        typedef CComBSTR source_type;
        typedef BSTR* result_type;
        inline static result_type Apply(source_type& val)
        {
            return &val;
        }
    };  // struct AddressExtractor<CComBSTR>

    template<class T>
    struct AddressExtractor<_com_ptr_t<_com_IIID<T, &__uuidof(T)>>>
    {
        typedef _com_ptr_t<_com_IIID<T, &__uuidof(T)>> source_type;
        typedef T** result_type;
        inline static result_type Apply(source_type& val)
        {
            return &val;
        }
    };  // struct AddressExtractor<_com_ptr_t<_com_IIID<T, &__uuidof(T)>>>

    template<class T>
    struct AddressExtractor<CComPtr<T>>
    {
        typedef CComPtr<T> source_type;
        typedef T** result_type;
        inline static result_type Apply(source_type& val)
        {
            return &val.p;
        }
    };  // struct AddressExtractor<CComPtr<T>>
    
}}}   // namespace Urasandesu { namespace NAnonym { namespace Traits {

#endif  // #ifndef URASANDESU_NANONYM_TRAITS_ADDRESSEXTRACTOR_H