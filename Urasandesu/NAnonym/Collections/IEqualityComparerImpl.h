#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_IEQUALITYCOMPARERIMPL_H
#define URASANDESU_NANONYM_COLLECTIONS_IEQUALITYCOMPARERIMPL_H

namespace Urasandesu { namespace NAnonym { namespace Collections {

    template <
        class Base, 
        class Type, 
        class EqualityComparer = GenericEqualityComparer<Type>
    >
    class ATL_NO_VTABLE IEqualityComparerImpl : 
        public Base
    {
        BOOST_CONCEPT_ASSERT((ComEqualityComparer<Base, Type>));
        BOOST_CONCEPT_ASSERT((ATLEqualityComparer<EqualityComparer, Type>));

    public:
        STDMETHOD(Equals)(Type value1, Type value2, VARIANT_BOOL* equals)
        {
            return EqualityComparer::Equals(value1, value2, equals);
        }

        STDMETHOD(GetHashCode)(Type value, LONG* hashCode)
        {
            return EqualityComparer::GetHashCode(value, hashCode);
        }
    };  // class ATL_NO_VTABLE IEqualityComparerImpl
    
}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_IEQUALITYCOMPARERIMPL_H