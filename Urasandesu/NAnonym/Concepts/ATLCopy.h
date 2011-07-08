#pragma once
#ifndef URASANDESU_NANONYM_CONCEPTS_ATLCOPY_H
#define URASANDESU_NANONYM_CONCEPTS_ATLCOPY_H

namespace Urasandesu { namespace NAnonym { namespace Concepts {

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

}}}   // namespace Urasandesu { namespace NAnonym { namespace Concepts {

#endif  // #ifndef URASANDESU_NANONYM_CONCEPTS_ATLCOPY_H
