#pragma once
#ifndef URASANDESU_NANONYM_NANONYMDEPENDSON_H
#define URASANDESU_NANONYM_NANONYMDEPENDSON_H

#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

namespace Urasandesu { namespace NAnonym {

    using boost::is_base_of;
    using boost::use_default;

}}   // namespace Urasandesu { namespace NAnonym {

#endif  // #ifndef URASANDESU_NANONYM_NANONYMDEPENDSON_H