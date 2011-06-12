#pragma once
#ifndef INCLUDED_SINGLEPASSANYRANGEGENERATOR_H
#define INCLUDED_SINGLEPASSANYRANGEGENERATOR_H

namespace My
{
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
}   // namespace My

#endif  // #ifndef INCLUDED_SINGLEPASSANYRANGEGENERATOR_H