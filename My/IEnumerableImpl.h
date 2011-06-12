#pragma once
#ifndef INCLUDED_IENUMERABLEIMPL_H
#define INCLUDED_IENUMERABLEIMPL_H

#ifndef INCLUDED_COMENUMERABLE_H
#include "ComEnumerable.h"
#endif

#ifndef INCLUDED_ADDIMPLICITCONVERSION_H
#include "AddImplicitConversion.h"
#endif

#ifndef INCLUDED_COLLECTIONS_H
#include "Collections.h"
#endif

namespace My
{
    template<
        class Base,
        class EnumeratorType, 
        class RangeType
    >
    class ATL_NO_VTABLE IEnumerableImpl : 
        public Base
    {
        BOOST_CONCEPT_ASSERT((ComEnumerable<Base>));
        BOOST_MPL_ASSERT((is_convertible<EnumeratorType, AddImplicitConversion<IgnoreParam6<CComEnumerator>>>));
        BOOST_CONCEPT_ASSERT((SinglePassRangeConcept<RangeType>));

    public:
        typedef IEnumerableImpl<Base, EnumeratorType, RangeType> type;
        typedef Base base_type;
        typedef Base interface_type;

        STDMETHOD(get__NewEnum)(IUnknown** ppVal)
        {
            return CreateRangeEnumerator<EnumeratorType>(this, m_container, ppVal);
        }

        RangeType m_container;
    };  // class ATL_NO_VTABLE IEnumerableImpl
}   // namespace My

#endif  // #ifndef INCLUDED_IENUMERABLEIMPL_H