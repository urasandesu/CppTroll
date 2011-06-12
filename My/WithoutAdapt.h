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
}   // namespace My

#endif  // #ifndef INCLUDED_WITHOUTADAPT_H