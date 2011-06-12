#pragma once
#ifndef INCLUDED_IEQUALITYCOMPARERIMPL_H
#define INCLUDED_IEQUALITYCOMPARERIMPL_H

namespace My
{
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
}   // namespace My

#endif  // #ifndef INCLUDED_IEQUALITYCOMPARERIMPL_H