#pragma once
#ifndef URASANDESU_NANONYM_CONCEPTS_ATLCOPY_H
#define URASANDESU_NANONYM_CONCEPTS_ATLCOPY_H

namespace Urasandesu { namespace NAnonym { namespace Concepts {

    using boost::addressof;

    template<class X, class DestinationType, class SourceType>
    class ATLCopy
    {
    public:
        BOOST_CONCEPT_USAGE(ATLCopy)
        {
            HRESULT hr;

            X::init(addressof(to));
            hr = X::copy(addressof(to), addressof(from));
            X::destroy(addressof(to));
        }
        
    private:
        SourceType from;
        DestinationType to;
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace Concepts {

#endif  // #ifndef URASANDESU_NANONYM_CONCEPTS_ATLCOPY_H
