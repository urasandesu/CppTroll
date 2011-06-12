#pragma once
#ifndef INCLUDED_EXTRACTOR_H
#define INCLUDED_EXTRACTOR_H

namespace My
{
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
}   // namespace My

#endif  // #ifndef INCLUDED_EXTRACTOR_H