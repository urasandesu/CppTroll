#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_SINGLEPASSANYRANGEGENERATOR_H
#define URASANDESU_NANONYM_COLLECTIONS_SINGLEPASSANYRANGEGENERATOR_H

namespace Urasandesu { namespace NAnonym { namespace Collections {

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

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_SINGLEPASSANYRANGEGENERATOR_H