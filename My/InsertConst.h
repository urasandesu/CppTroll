#pragma once
#ifndef INCLUDED_INSERTCONST_H
#define INCLUDED_INSERTCONST_H

namespace My
{
    template<class T>
    struct InsertConst 
    { 
        typedef const T type;
    };  // struct InsertConst 

    template<class T>
    struct InsertConst<T*>
    { 
        typedef const T* type;
    };  // InsertConst<T*>

    template<class T>
    struct InsertConst<const T*>
    {
        typedef const T* type;
    };  // struct InsertConst<const T*>

    template<class T>
    struct InsertConst<T* const>
    {
        typedef const T* const type;
    };  // struct InsertConst<T* const>

    template<class T>
    struct InsertConst<const T* const>
    {
        typedef const T* const type;
    };  // struct InsertConst<const T* const>

    template<class T>
    struct InsertConst<const T&>
    {
        typedef const T& type;
    };  // struct InsertConst<const T&>

    template<class T>
    struct InsertConst<T&>
    {
        typedef const T& type;
    };  // struct InsertConst<T&>
}   // namespace My

#endif // #ifndef INCLUDED_INSERTCONST_H
