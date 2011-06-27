#pragma once
#ifndef INCLUDED_COMOBJECTWITHINSTANTIATION_H
#define INCLUDED_COMOBJECTWITHINSTANTIATION_H

namespace My
{
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
}   // namespace My

#endif  // #ifndef INCLUDED_COMOBJECTWITHINSTANTIATION_H
