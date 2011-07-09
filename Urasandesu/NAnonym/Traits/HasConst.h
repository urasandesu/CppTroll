#pragma once
#ifndef URASANDESU_NANONYM_TRAITS_HASCONST_H
#define URASANDESU_NANONYM_TRAITS_HASCONST_H

namespace Urasandesu { namespace NAnonym { namespace Traits {

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

}}}   // namespace Urasandesu { namespace NAnonym { namespace Traits {

#endif  // #ifndef URASANDESU_NANONYM_TRAITS_HASCONST_H