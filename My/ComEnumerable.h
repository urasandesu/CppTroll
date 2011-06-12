#pragma once
#ifndef INCLUDED_COMENUMERABLE_H
#define INCLUDED_COMENUMERABLE_H

namespace My
{
    template<class X>
    struct ComEnumerable
    {
        BOOST_MPL_ASSERT((is_base_of<IUnknown, X>));
            
        BOOST_CONCEPT_USAGE(ComEnumerable)
        {
            HRESULT hr;
            X* pX;
            IUnknown* pUnk;

            hr = pX->get__NewEnum(&pUnk);
        }
    };  // struct ComEnumerable
}   // namespace My

#endif  // #ifndef INCLUDED_COMENUMERABLE_H
