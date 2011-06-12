#pragma once
#ifndef INCLUDED_SINGLEPASSCOPYANYRANGEGENERATOR_H
#define INCLUDED_SINGLEPASSCOPYANYRANGEGENERATOR_H

namespace My
{
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

#endif  // #ifndef INCLUDED_SINGLEPASSCOPYANYRANGEGENERATOR_H