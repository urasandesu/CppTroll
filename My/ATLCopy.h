#pragma once
#ifndef INCLUDED_ATLCOPY_H
#define INCLUDED_ATLCOPY_H

namespace My
{
    template<class X, class DestinationType, class SourceType>
    struct ATLCopy
    {
        BOOST_CONCEPT_USAGE(ATLCopy)
        {
            HRESULT hr;
            SourceType* pFrom;
            DestinationType* pTo;

            // For normal type.
            {
                X::init(pTo);
                hr = X::copy(pTo, pFrom);
                X::destroy(pTo);
            }

            // For specialized type overloading operator&.
            {
                X::init(&*pTo);
                hr = X::copy(&*pTo, &*pFrom);
                X::destroy(&*pTo);
            }
        }
    };  // struct ATLCopy
}   // namespace My

#endif  // #ifndef INCLUDED_ATLCOPY_H
