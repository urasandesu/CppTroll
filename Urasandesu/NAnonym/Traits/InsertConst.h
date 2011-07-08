#pragma once
#ifndef URASANDESU_NANONYM_TRAITS_INSERTCONST_H
#define URASANDESU_NANONYM_TRAITS_INSERTCONST_H

namespace Urasandesu { namespace NAnonym { namespace Traits {

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

}}}   // namespace Urasandesu { namespace NAnonym { namespace Traits {

#endif // #ifndef URASANDESU_NANONYM_TRAITS_INSERTCONST_H
