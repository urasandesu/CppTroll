#pragma once
#ifndef INCLUDED_MYDEPENDSON_H
#define INCLUDED_MYDEPENDSON_H

#include <atlsafe.h>
#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept/usage.hpp>
#include <boost/concept_check.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/any_range.hpp>
#include <boost/preprocessor.hpp>
#include <boost/functional/hash/hash.hpp>
#include <boost/unordered_map.hpp>
#include <comip.h>

namespace My
{

    using boost::add_lvalue_reference;
    using boost::any_range_type_generator;
    using boost::call_traits;
    using boost::is_base_of;
    using boost::is_class;
    using boost::is_convertible;
    using boost::is_lvalue_reference;
    using boost::is_object;
    using boost::is_pointer;
    using boost::is_union;
    using boost::mpl::eval_if;
    using boost::mpl::false_;
    using boost::mpl::identity;
    using boost::mpl::int_;
    using boost::mpl::not_;
    using boost::mpl::or_;
    using boost::mpl::true_;
    using boost::Mutable_RandomAccessContainer;
    using boost::range_iterator;
    using boost::range_value;
    using boost::Sequence;
    using boost::single_pass_traversal_tag;
    using boost::SinglePassRangeConcept;
    using boost::use_default;
}   // namespace My

#endif  // #ifndef INCLUDED_MYDEPENDSON_H