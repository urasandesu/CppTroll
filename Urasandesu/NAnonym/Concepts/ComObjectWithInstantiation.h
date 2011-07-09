#pragma once
#ifndef URASANDESU_NANONYM_CONCEPTS_COMOBJECTWITHINSTANTIATION_H
#define URASANDESU_NANONYM_CONCEPTS_COMOBJECTWITHINSTANTIATION_H

namespace Urasandesu { namespace NAnonym { namespace Concepts {

    template<class X>
    struct ComObjectWithInstantiation
    {
        BOOST_MPL_ASSERT((is_base_of<IUnknown, X>));
            
        BOOST_CONCEPT_USAGE(ComObjectWithInstantiation)
        {
            HRESULT hr;
            X* pObj = NULL;
            hr = X::CreateInstance(&pObj);
        }
    };  // struct ComObjectWithInstantiation

}}}   // namespace Urasandesu { namespace NAnonym { namespace Concepts {

#endif  // #ifndef URASANDESU_NANONYM_CONCEPTS_COMOBJECTWITHINSTANTIATION_H
