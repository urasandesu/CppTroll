#pragma once
#ifndef INCLUDED_UTILITIES_H
#define INCLUDED_UTILITIES_H

#ifndef INCLUDED_VARIANTTRAITS_H
#include "VariantTraits.h"
#endif

namespace My
{
    template<class ParamType, int VarType>
    inline static bool VariantEquals(ParamType value1, ParamType value2, const int_<VarType>&)
    {
        BOOST_MPL_ASSERT((is_object<ParamType>));

        return value1 == value2;
    }

    template<class ParamType>
    inline static bool VariantEquals(ParamType value1, ParamType value2, const I_VT_BYREF&)
    {
        BOOST_MPL_ASSERT((is_lvalue_reference<ParamType>));

        return &value1 == &value2;
    }
    
    using boost::is_same;

    template<class ParamType>
    inline static bool VariantEquals(ParamType value1, ParamType value2, const I_VT_BSTR&)
    {
        BOOST_MPL_ASSERT((is_same<ParamType, I_VT_BSTR_TRAITS::const_param_type>));

        BSTR _value1 = const_cast<BSTR>(value1);
        BSTR _value2 = const_cast<BSTR>(value2);
        return ::VarBstrCmp(_value1, _value2, LOCALE_USER_DEFAULT, 0) == static_cast<HRESULT>(VARCMP_EQ);
    }

    template<class ParamType>
    inline static bool VariantEquals(ParamType value1, ParamType value2, const I_VT_VARIANT&)
    {
        BOOST_MPL_ASSERT((is_same<ParamType, I_VT_VARIANT_TRAITS::const_param_type>));

        if (value1.vt == VT_NULL && value2.vt == VT_NULL)
        {
            return true;
        }
        else if (value1.vt != value2.vt)
        {
            return false;
        }
        else
        {
            VARIANT* _value1 = const_cast<VARIANT*>(&value1);
            VARIANT* _value2 = const_cast<VARIANT*>(&value2);
            return ::VarCmp(_value1, _value2, LOCALE_USER_DEFAULT, 0) == static_cast<HRESULT>(VARCMP_EQ);
        }
    }



    template<class ParamType, int VarType>
    inline static LONG VariantGetHashCode(ParamType value, const int_<VarType>&);

    template<class ParamType>
    inline static LONG VariantGetHashCode(ParamType value, const I_VT_PTR&)
    {
        BOOST_MPL_ASSERT((is_pointer<ParamType>));

        return reinterpret_cast<LONG>(value);
    }

    template<class ParamType>
    inline static LONG VariantGetHashCode(ParamType value, const I_VT_BYREF&)
    {
        BOOST_MPL_ASSERT((is_lvalue_reference<ParamType>));

        return reinterpret_cast<LONG>(&value);
    }

    template<class ParamType>
    inline static LONG VariantGetHashCode(ParamType value, const I_VT_BSTR&)
    {
        BOOST_MPL_ASSERT((is_same<ParamType, I_VT_BSTR_TRAITS::const_param_type>));

        BSTR _value = const_cast<BSTR>(value);
        std::size_t seed = 0;
        for (BSTR i = _value, i_end = _value + ::SysStringLen(_value); i != i_end; ++i)
        {
            boost::hash_combine(seed, *i);
        }
        return seed;
    }

    template<class ParamType>
    inline static LONG VariantGetHashCode(ParamType value, const I_VT_R4&)
    {
        BOOST_MPL_ASSERT((is_same<ParamType, I_VT_R4_TRAITS::const_param_type>));
        return *reinterpret_cast<LONG*>(const_cast<FLOAT*>(&value));
    }

    template<class ParamType>
    inline static LONG VariantGetHashCode(ParamType value, const I_VT_DECIMAL&)
    {
        return static_cast<LONG>(value.signscale) ^ static_cast<LONG>(value.Hi32) ^ 
               static_cast<LONG>(value.Lo64) ^ static_cast<LONG>(value.Lo64 >> 32);
    }

    template<class ParamType>
    inline static LONG VariantGetHashCode(ParamType value, const I_VT_CY&)
    {
        return static_cast<LONG>(value.int64) ^ static_cast<LONG>(value.int64 >> 32);
    }

#define DECLARE_VARIANT_GET_HASH_CODE_FOR_LONG_VALUE(var_type_traits_) \
    template<class ParamType> \
    inline static LONG VariantGetHashCode(ParamType value, const var_type_traits_##::var_type&) \
    { \
        return static_cast<LONG>(value); \
    }

    DECLARE_VARIANT_GET_HASH_CODE_FOR_LONG_VALUE(I_VT_UINT_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_LONG_VALUE(I_VT_UI4_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_LONG_VALUE(I_VT_UI2_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_LONG_VALUE(I_VT_UI1_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_LONG_VALUE(I_VT_INT_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_LONG_VALUE(I_VT_I4_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_LONG_VALUE(I_VT_I2_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_LONG_VALUE(I_VT_I1_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_LONG_VALUE(I_VT_ERROR_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_LONG_VALUE(I_VT_BOOL_TRAITS);
    
#undef DECLARE_VARIANT_GET_HASH_CODE_FOR_LONG_VALUE

#define DECLARE_VARIANT_GET_HASH_CODE_FOR_LONGLONG_VALUE(var_type_traits_) \
    template<class ParamType> \
    inline static LONG VariantGetHashCode(ParamType value, const var_type_traits_##::var_type&) \
    { \
        return static_cast<LONG>(value) ^ static_cast<LONG>(value >> 32); \
    }
    
    DECLARE_VARIANT_GET_HASH_CODE_FOR_LONGLONG_VALUE(I_VT_UI8_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_LONGLONG_VALUE(I_VT_I8_TRAITS);
    
#undef DECLARE_VARIANT_GET_HASH_CODE_FOR_LONGLONG_VALUE

#define DECLARE_VARIANT_GET_HASH_CODE_FOR_DOUBLE_VALUE(var_type_traits_) \
    template<class ParamType> \
    inline static LONG VariantGetHashCode(ParamType value, const var_type_traits_##::var_type&) \
    { \
        LONGLONG ll = *reinterpret_cast<LONGLONG*>(const_cast<var_type_traits_##::param_type*>(&value)); \
        return static_cast<LONG>(ll) ^ static_cast<LONG>(ll >> 32); \
    }

    DECLARE_VARIANT_GET_HASH_CODE_FOR_DOUBLE_VALUE(I_VT_R8_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_DOUBLE_VALUE(I_VT_DATE_TRAITS);
    
#undef DECLARE_VARIANT_GET_HASH_CODE_FOR_DOUBLE_VALUE

#define DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(var_type_traits_) \
    template<class ParamType> \
    inline static LONG VariantGetHashCode(ParamType value, const var_type_traits_##::var_type&) \
    { \
        const size_t OFFSET = sizeof(VARTYPE) + sizeof(WORD) * 3; \
        const size_t LENGTH = sizeof(VARIANT) - OFFSET; \
        BYTE pb[LENGTH]; \
        ::memcpy_s(pb, LENGTH, reinterpret_cast<BYTE*>(const_cast<var_type_traits_##::param_type>(value)) + OFFSET, LENGTH);  \
        return reinterpret_cast<LONG>(*reinterpret_cast<VOID**>(&pb)); \
    }
    
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_VARIANT_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_UNKNOWN_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_UINT_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_UI8_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_UI4_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_UI2_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_UI1_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_R8_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_R4_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_INT_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_I8_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_I4_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_I2_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_I1_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_ERROR_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_DISPATCH_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_DECIMAL_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_DATE_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_CY_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_BSTR_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_BOOL_REF_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_UNKNOWN_TRAITS);
    DECLARE_VARIANT_GET_HASH_CODE_FOR_REF(I_VT_DISPATCH_TRAITS);
    
#undef DECLARE_VARIANT_GET_HASH_CODE_FOR_REF
}   // namespace My

#endif  // #ifndef INCLUDED_UTILITIES_H