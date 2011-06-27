#pragma once
#ifndef INCLUDED_WITHOUTADAPT_H
#define INCLUDED_WITHOUTADAPT_H

namespace My
{
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
    
}   // namespace My

#endif  // #ifndef INCLUDED_WITHOUTADAPT_H