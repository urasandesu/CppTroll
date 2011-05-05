#pragma once
#include <boost/range/algorithm.hpp>
#include <boost/range/any_range.hpp>

namespace My
{
    using namespace boost;

    template<class Container>
    struct SinglePassAnyRangeGenerator : 
        public any_range_type_generator<
            Container, 
            use_default, 
            single_pass_traversal_tag, 
            use_default, 
            use_default, 
            use_default
        >
    {
    };

    template<class Container>
    struct SinglePassCopyAnyRangeGenerator : 
        public any_range_type_generator<
            Container, 
            use_default, 
            single_pass_traversal_tag, 
            typename range_value<Container>::type, 
            use_default, 
            use_default
        >
    {
    };
}   // namespace My