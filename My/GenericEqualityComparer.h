#pragma once
#ifndef INCLUDED_GENERICEQUALITYCOMPARER_H
#define INCLUDED_GENERICEQUALITYCOMPARER_H

#ifndef INCLUDED_UTILITIES_H
#include "Utilities.h"
#endif

#ifndef INCLUDED_VARIANTEQUALITYCOMPARISON_H
#include "VariantEqualityComparison.h"
#endif

#ifndef INCLUDED_VARIANTHASHCODE_H
#include "VariantHashCode.h"
#endif

namespace My
{
    template<class T>
    struct GenericEqualityComparer : 
        private VariantTraits<T>
    {
        inline static HRESULT Equals(const_param_type value1, const_param_type value2, VARIANT_BOOL* equals)
        {
            if (equals == NULL) return E_POINTER;
            *equals = VariantEquals<const_param_type>(value1, value2, var_type()) ? VARIANT_TRUE : VARIANT_FALSE;
            return S_OK;
        }
       
        inline static HRESULT GetHashCode(const_param_type value, LONG* hashCode)
        {
            if (hashCode == NULL) return E_POINTER;
            *hashCode = VariantGetHashCode<const_param_type>(value, var_type());
            return S_OK;
        }
    };

#define DECLARE_GENERIC_EQUALITY_COMPARER(specialized, var_type_) \
    template<> \
    struct GenericEqualityComparer<specialized> :  \
        private VariantTraits<var_type_> \
    { \
        inline static HRESULT Equals(const_param_type value1, const_param_type value2, VARIANT_BOOL* equals) \
        { \
            if (equals == NULL) return E_POINTER; \
            *equals = VariantEquals<const_param_type>(value1, value2, var_type()) ? VARIANT_TRUE : VARIANT_FALSE; \
            return S_OK; \
        } \
        \
        inline static HRESULT GetHashCode(const_param_type value, LONG* hashCode) \
        { \
            if (hashCode == NULL) return E_POINTER; \
            *hashCode = VariantGetHashCode<const_param_type>(value, var_type()); \
            return S_OK; \
        } \
    };

    DECLARE_GENERIC_EQUALITY_COMPARER(BSTR, I_VT_BSTR);
    DECLARE_GENERIC_EQUALITY_COMPARER(UINT, I_VT_UINT);
    DECLARE_GENERIC_EQUALITY_COMPARER(ULONG, I_VT_UI4);
    DECLARE_GENERIC_EQUALITY_COMPARER(USHORT, I_VT_UI2);
    DECLARE_GENERIC_EQUALITY_COMPARER(BYTE, I_VT_UI1);
    DECLARE_GENERIC_EQUALITY_COMPARER(INT, I_VT_INT);
    DECLARE_GENERIC_EQUALITY_COMPARER(LONG, I_VT_I4);
    DECLARE_GENERIC_EQUALITY_COMPARER(SHORT, I_VT_I2);
    DECLARE_GENERIC_EQUALITY_COMPARER(CHAR, I_VT_I1);
    //DECLARE_GENERIC_EQUALITY_COMPARER(SCODE, I_VT_ERROR);
    //DECLARE_GENERIC_EQUALITY_COMPARER(VARIANT_BOOL, I_VT_BOOL);
    
#undef DECLARE_GENERIC_EQUALITY_COMPARER

    template<>
    struct GenericEqualityComparer<VARIANT>
    {
        static HRESULT Equals(const VARIANT& value1, const VARIANT& value2, VARIANT_BOOL* equals)
        {
            if (equals == NULL) return E_POINTER;
            *equals = VariantEqualityComparison<I_VT_VARIANT>::Equals(value1, value2) ? VARIANT_TRUE : VARIANT_FALSE;
            return S_OK;
        }

        static HRESULT GetHashCode(const VARIANT& value, LONG* hashCode)
        {
            if (hashCode == NULL) return E_POINTER;

            switch (value.vt)
            {
            case VT_VARIANT:
            case VT_BYREF | VT_NULL:
            case VT_NULL: 
            case VT_BYREF | VT_EMPTY:
            case VT_EMPTY:
                *hashCode = 0;
                break;
            case VT_BYREF | VT_VARIANT: *hashCode = VariantHashCode<I_VT_VARIANT_REF>::Get(value); break;
            case VT_BYREF | VT_UNKNOWN: *hashCode = VariantHashCode<I_VT_UNKNOWN_REF>::Get(value); break;
            case VT_BYREF | VT_UINT: *hashCode = VariantHashCode<I_VT_UINT_REF>::Get(value); break;
            case VT_BYREF | VT_UI8: *hashCode = VariantHashCode<I_VT_UI8_REF>::Get(value); break;
            case VT_BYREF | VT_UI4: *hashCode = VariantHashCode<I_VT_UI4_REF>::Get(value); break;
            case VT_BYREF | VT_UI2: *hashCode = VariantHashCode<I_VT_UI2_REF>::Get(value); break;
            case VT_BYREF | VT_UI1: *hashCode = VariantHashCode<I_VT_UI1_REF>::Get(value); break;
            case VT_BYREF | VT_R8: *hashCode = VariantHashCode<I_VT_R8_REF>::Get(value); break;
            case VT_BYREF | VT_R4: *hashCode = VariantHashCode<I_VT_R4_REF>::Get(value); break;
            case VT_BYREF | VT_INT: *hashCode = VariantHashCode<I_VT_INT_REF>::Get(value); break;
            case VT_BYREF | VT_I8: *hashCode = VariantHashCode<I_VT_I8_REF>::Get(value); break;
            case VT_BYREF | VT_I4: *hashCode = VariantHashCode<I_VT_I4_REF>::Get(value); break;
            case VT_BYREF | VT_I2: *hashCode = VariantHashCode<I_VT_I2_REF>::Get(value); break;
            case VT_BYREF | VT_I1: *hashCode = VariantHashCode<I_VT_I1_REF>::Get(value); break;
            case VT_BYREF | VT_ERROR: *hashCode = VariantHashCode<I_VT_ERROR_REF>::Get(value); break;
            case VT_BYREF | VT_DISPATCH: *hashCode = VariantHashCode<I_VT_DISPATCH_REF>::Get(value); break;
            case VT_BYREF | VT_DECIMAL: *hashCode = VariantHashCode<I_VT_DECIMAL_REF>::Get(value); break;
            case VT_BYREF | VT_DATE: *hashCode = VariantHashCode<I_VT_DATE_REF>::Get(value); break;
            case VT_BYREF | VT_CY: *hashCode = VariantHashCode<I_VT_CY_REF>::Get(value); break;
            case VT_BYREF | VT_BSTR: *hashCode = VariantHashCode<I_VT_BSTR_REF>::Get(value); break;
            case VT_BYREF | VT_BOOL: *hashCode = VariantHashCode<I_VT_BOOL_REF>::Get(value); break;
            case VT_UNKNOWN: *hashCode = VariantHashCode<I_VT_UNKNOWN>::Get(value); break;
            case VT_DISPATCH: *hashCode = VariantHashCode<I_VT_DISPATCH>::Get(value); break;
            case VT_UINT: *hashCode = VariantHashCode<I_VT_UINT>::Get(value); break;
            case VT_UI4: *hashCode = VariantHashCode<I_VT_UI4>::Get(value); break;
            case VT_UI2: *hashCode = VariantHashCode<I_VT_UI2>::Get(value); break;
            case VT_UI1: *hashCode = VariantHashCode<I_VT_UI1>::Get(value); break;
            case VT_INT: *hashCode = VariantHashCode<I_VT_INT>::Get(value); break;
            case VT_I4: *hashCode = VariantHashCode<I_VT_I4>::Get(value); break;
            case VT_I2: *hashCode = VariantHashCode<I_VT_I2>::Get(value); break;
            case VT_I1: *hashCode = VariantHashCode<I_VT_I1>::Get(value); break;
            case VT_ERROR: *hashCode = VariantHashCode<I_VT_ERROR>::Get(value); break;
            case VT_BOOL: *hashCode = VariantHashCode<I_VT_BOOL>::Get(value); break;
            case VT_UI8: *hashCode = VariantHashCode<I_VT_UI8>::Get(value); break;
            case VT_I8: *hashCode = VariantHashCode<I_VT_I8>::Get(value); break;
            case VT_R8: *hashCode = VariantHashCode<I_VT_R8>::Get(value); break;
            case VT_DATE: *hashCode = VariantHashCode<I_VT_DATE>::Get(value); break;
            case VT_R4: *hashCode = VariantHashCode<I_VT_R4>::Get(value); break;
            case VT_DECIMAL: *hashCode = VariantHashCode<I_VT_DECIMAL>::Get(value); break;
            case VT_CY: *hashCode = VariantHashCode<I_VT_CY>::Get(value); break;
            case VT_BSTR: *hashCode = VariantHashCode<I_VT_BSTR>::Get(value); break;
            default:
                *hashCode = 0;
                return E_INVALIDARG;
            }
            return S_OK;
        }
    };  // struct GenericEqualityComparer<VARIANT>

}   // namespace My

#endif  // #ifndef INCLUDED_GENERICEQUALITYCOMPARER_H