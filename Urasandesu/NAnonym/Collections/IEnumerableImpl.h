#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_IENUMERABLEIMPL_H
#define URASANDESU_NANONYM_COLLECTIONS_IENUMERABLEIMPL_H

#ifndef URASANDESU_NANONYM_CONCEPTS_COMENUMERABLE_H
#include "Urasandesu/NAnonym/Concepts/ComEnumerable.h"
#endif

#ifndef URASANDESU_NANONYM_TRAITS_ADDIMPLICITCONVERSION_H
#include "Urasandesu/NAnonym/Traits/AddImplicitConversion.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Collections {

    using namespace Urasandesu::NAnonym::Concepts;
    using namespace Urasandesu::NAnonym::Traits;
    
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
    
}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_IENUMERABLEIMPL_H