#pragma once
#ifndef URASANDESU_NANONYM_CONCEPTS_EXTRACTOR_H
#define URASANDESU_NANONYM_CONCEPTS_EXTRACTOR_H

namespace Urasandesu { namespace NAnonym { namespace Concepts {

    template<class X>
    struct Extractor
    {
        BOOST_CONCEPT_USAGE(Extractor)
        {
            typedef X::source_type source_type;
            typedef X::result_type result_type;

            source_type source;
            result_type result = X::Apply(source);
        }
    };  // struct Extractor
    
}}}   // namespace Urasandesu { namespace NAnonym { namespace Concepts {

#endif  // #ifndef URASANDESU_NANONYM_CONCEPTS_EXTRACTOR_H