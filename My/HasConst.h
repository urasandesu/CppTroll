#pragma once
#ifndef INCLUDED_HASCONST_H
#define INCLUDED_HASCONST_H

namespace My
{
    template<class T>
    struct HasConst 
    { 
        typedef false_ type;
    };  // struct HasConst 

    template<class T>
    struct HasConst<const T*>
    {
        typedef true_ type;
    };  // struct HasConst<const T*>

    template<class T>
    struct HasConst<T* const>
    {
        typedef true_ type;
    };  // struct HasConst<T* const>

    template<class T>
    struct HasConst<const T&>
    {
        typedef true_ type;
    };  // struct HasConst<const T&>
}   // namespace My

#endif  // #ifndef INCLUDED_HASCONST_H