#pragma once
#ifndef URASANDESU_NANONYM_TRAITS_WITHOUTADAPT_H
#define URASANDESU_NANONYM_TRAITS_WITHOUTADAPT_H

namespace Urasandesu { namespace NAnonym { namespace Traits {

    template<class T>
    struct WithoutAdapt
    {
        typedef T type;
    };  // struct WithoutAdapt

    template<class T>
    struct WithoutAdapt<CAdapt<T>>
    {
        typedef T type;
    };  // struct WithoutAdapt<CAdapt<T>>
    
    template<class T>
    struct RangeValueWithoutAdapt : 
        public WithoutAdapt<typename range_value<T>::type>
    {
    };
    
}}}   // namespace Urasandesu { namespace NAnonym { namespace Traits {

#endif  // #ifndef URASANDESU_NANONYM_TRAITS_WITHOUTADAPT_H