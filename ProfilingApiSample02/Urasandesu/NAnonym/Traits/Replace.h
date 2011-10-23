#pragma once
#ifndef URASANDESU_NANONYM_TRAITS_REPLACE_H
#define URASANDESU_NANONYM_TRAITS_REPLACE_H

namespace Urasandesu { namespace NAnonym { namespace Traits {

    // Gets New if T is Old; otherwise T.    
    template <class T, class Old, class New>
    struct Replace : 
        public boost::mpl::eval_if<
                boost::is_same<T, Old>, 
                boost::mpl::identity<New>, 
                boost::mpl::identity<T>>
    {
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace Traits {

#endif  // #ifndef URASANDESU_NANONYM_TRAITS_REPLACE_H