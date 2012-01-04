#pragma once
#ifndef URASANDESU_NANONYM_TRAITS_HASCONST_H
#define URASANDESU_NANONYM_TRAITS_HASCONST_H

namespace Urasandesu { namespace NAnonym { namespace Traits {

    template<class T>
    struct HasConst 
    { 
        typedef boost::mpl::false_ type;
        static const bool value = false;
    };  // struct HasConst 

    template<class T>
    struct HasConst<const T*>
    {
        typedef boost::mpl::true_ type;
        static const bool value = true;
    };  // struct HasConst<const T*>

    template<class T>
    struct HasConst<T* const>
    {
        typedef boost::mpl::true_ type;
        static const bool value = true;
    };  // struct HasConst<T* const>

    template<class T>
    struct HasConst<const T&>
    {
        typedef boost::mpl::true_ type;
        static const bool value = true;
    };  // struct HasConst<const T&>

}}}   // namespace Urasandesu { namespace NAnonym { namespace Traits {

#endif  // #ifndef URASANDESU_NANONYM_TRAITS_HASCONST_H