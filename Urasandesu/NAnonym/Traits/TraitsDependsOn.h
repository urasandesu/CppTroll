#pragma once
#ifndef URASANDESU_NANONYM_TRAITS_TRAITSDEPENDSON_H
#define URASANDESU_NANONYM_TRAITS_TRAITSDEPENDSON_H

#ifndef URASANDESU_NANONYM_NANONYMDEPENDSON_H
#include "Urasandesu/NAnonym/NAnonymDependsOn.h"
#endif

#include <boost/call_traits.hpp>
#include <boost/preprocessor.hpp>

namespace Urasandesu { namespace NAnonym { namespace Traits {

    using boost::add_lvalue_reference;
    using boost::call_traits;
    using boost::is_class;
    using boost::is_lvalue_reference;
    using boost::is_object;
    using boost::is_pointer;
    using boost::is_same;
    using boost::is_union;
    using boost::mpl::eval_if;
    using boost::mpl::false_;
    using boost::mpl::identity;
    using boost::mpl::int_;
    using boost::mpl::not_;
    using boost::mpl::or_;
    using boost::mpl::true_;
    using boost::mpl::void_;
    using boost::range_value;

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_TRAITS_TRAITSDEPENDSON_H