#pragma once
#ifndef URASANDESU_NANONYM_CONCEPTS_COMENUMERABLE_H
#define URASANDESU_NANONYM_CONCEPTS_COMENUMERABLE_H

namespace Urasandesu { namespace NAnonym { namespace Concepts {

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

}}}   // namespace Urasandesu { namespace NAnonym { namespace Concepts {

#endif  // #ifndef URASANDESU_NANONYM_CONCEPTS_COMENUMERABLE_H
