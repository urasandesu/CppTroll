#pragma once
#ifndef INCLUDED_IENUMERABLEIMPL_H
#define INCLUDED_IENUMERABLEIMPL_H

#ifndef INCLUDED_COMENUMERABLE_H
#include "ComEnumerable.h"
#endif

#ifndef INCLUDED_ADDIMPLICITCONVERSION_H
#include "AddImplicitConversion.h"
#endif

namespace My
{
    template<
        class Base,
        class RangeType,
        class ComEnumeratorObject
    >
    class ATL_NO_VTABLE IEnumerableImpl : 
        public Base
    {
        BOOST_CONCEPT_ASSERT((ComEnumerable<Base>));
        BOOST_CONCEPT_ASSERT((SinglePassRangeConcept<RangeType>));
        BOOST_CONCEPT_ASSERT((ComObjectWithInstantiation<ComEnumeratorObject>));
        BOOST_MPL_ASSERT((is_convertible<ComEnumeratorObject, AddImplicitConversion<IgnoreParam5<IEnumeratorImpl>>>));

    public:
        typedef IEnumerableImpl<Base, RangeType, ComEnumeratorObject> type;
        typedef Base base_type;
        typedef Base interface_type;

        STDMETHOD(get__NewEnum)(IUnknown** ppVal)
        {
            return ComEnumeratorObject::New<ComEnumeratorObject>(this, m_container, ppVal);
        }

        RangeType m_container;
    };  // class ATL_NO_VTABLE IEnumerableImpl
}   // namespace My

#endif  // #ifndef INCLUDED_IENUMERABLEIMPL_H