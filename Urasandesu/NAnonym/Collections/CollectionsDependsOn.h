#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_COLLECTIONSDEPENDSON_H
#define URASANDESU_NANONYM_COLLECTIONS_COLLECTIONSDEPENDSON_H

#ifndef URASANDESU_NANONYM_NANONYMDEPENDSON_H
#include "Urasandesu/NAnonym/NAnonymDependsOn.h"
#endif

#include <atlsafe.h>
#include <boost/range/algorithm.hpp>
#include <boost/range/any_range.hpp>

namespace Urasandesu { namespace NAnonym { namespace Collections {

    using boost::any_range_type_generator;
    using boost::is_convertible;
    using boost::Mutable_RandomAccessContainer;
    using boost::range_iterator;
    using boost::Sequence;
    using boost::SinglePassRangeConcept;
    using boost::single_pass_traversal_tag;
    template<class> struct use_default1;

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_COLLECTIONSDEPENDSON_H