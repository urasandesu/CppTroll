#pragma once
#include <boost/range/algorithm.hpp>
#include <boost/range/any_range.hpp>

namespace My
{
    template<class Container>
    struct SinglePassAnyRangeGenerator : 
        public boost::any_range_type_generator<
            Container, 
            boost::use_default, 
            boost::single_pass_traversal_tag, 
            boost::use_default, 
            boost::use_default, 
            boost::use_default
        >
    {
    };

    template<class Container>
    struct SinglePassCopyAnyRangeGenerator : 
        public boost::any_range_type_generator<
            Container, 
            boost::use_default, 
            boost::single_pass_traversal_tag, 
            typename boost::range_value<Container>::type, 
            boost::use_default, 
            boost::use_default
        >
    {
    };
}   // namespace My