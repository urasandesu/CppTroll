#pragma once
#ifndef URASANDESU_NANONYM_TRAITS_VARIANTTRAITS_H
#define URASANDESU_NANONYM_TRAITS_VARIANTTRAITS_H

#ifndef URASANDESU_NANONYM_TRAITS_INSERTCONST_H
#include "Urasandesu/NAnonym/Traits/InsertConst.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Traits {

    enum
    {
        VT_VALUE = VT_VERSIONED_STREAM + 1
    };

    typedef int_<VT_EMPTY> I_VT_EMPTY;
    typedef int_<VT_NULL> I_VT_NULL;
    typedef int_<VT_I2> I_VT_I2;
    typedef int_<VT_I4> I_VT_I4;
    typedef int_<VT_R4> I_VT_R4;
    typedef int_<VT_R8> I_VT_R8;
    typedef int_<VT_CY> I_VT_CY;
    typedef int_<VT_DATE> I_VT_DATE;
    typedef int_<VT_BSTR> I_VT_BSTR;
    typedef int_<VT_DISPATCH> I_VT_DISPATCH;
    typedef int_<VT_ERROR> I_VT_ERROR;
    typedef int_<VT_BOOL> I_VT_BOOL;
    typedef int_<VT_VARIANT> I_VT_VARIANT;
    typedef int_<VT_UNKNOWN> I_VT_UNKNOWN;
    typedef int_<VT_DECIMAL> I_VT_DECIMAL;
    typedef int_<VT_I1> I_VT_I1;
    typedef int_<VT_UI1> I_VT_UI1;
    typedef int_<VT_UI2> I_VT_UI2;
    typedef int_<VT_UI4> I_VT_UI4;
    typedef int_<VT_I8> I_VT_I8;
    typedef int_<VT_UI8> I_VT_UI8;
    typedef int_<VT_INT> I_VT_INT;
    typedef int_<VT_UINT> I_VT_UINT;
    typedef int_<VT_VOID> I_VT_VOID;
    typedef int_<VT_HRESULT> I_VT_HRESULT;
    typedef int_<VT_PTR> I_VT_PTR;
    typedef int_<VT_SAFEARRAY> I_VT_SAFEARRAY;
    typedef int_<VT_CARRAY> I_VT_CARRAY;
    typedef int_<VT_USERDEFINED> I_VT_USERDEFINED;
    typedef int_<VT_LPSTR> I_VT_LPSTR;
    typedef int_<VT_LPWSTR> I_VT_LPWSTR;
    typedef int_<VT_RECORD> I_VT_RECORD;
    typedef int_<VT_INT_PTR> I_VT_INT_PTR;
    typedef int_<VT_UINT_PTR> I_VT_UINT_PTR;
    typedef int_<VT_FILETIME> I_VT_FILETIME;
    typedef int_<VT_BLOB> I_VT_BLOB;
    typedef int_<VT_STREAM> I_VT_STREAM;
    typedef int_<VT_STORAGE> I_VT_STORAGE;
    typedef int_<VT_STREAMED_OBJECT> I_VT_STREAMED_OBJECT;
    typedef int_<VT_STORED_OBJECT> I_VT_STORED_OBJECT;
    typedef int_<VT_BLOB_OBJECT> I_VT_BLOB_OBJECT;
    typedef int_<VT_CF> I_VT_CF;
    typedef int_<VT_CLSID> I_VT_CLSID;
    typedef int_<VT_VERSIONED_STREAM> I_VT_VERSIONED_STREAM;
    typedef int_<VT_VARIANT | VT_BYREF> I_VT_VARIANT_REF;
    typedef int_<VT_UNKNOWN | VT_BYREF> I_VT_UNKNOWN_REF;
    typedef int_<VT_UINT | VT_BYREF> I_VT_UINT_REF;
    typedef int_<VT_UI8 | VT_BYREF> I_VT_UI8_REF;
    typedef int_<VT_UI4 | VT_BYREF> I_VT_UI4_REF;
    typedef int_<VT_UI2 | VT_BYREF> I_VT_UI2_REF;
    typedef int_<VT_UI1 | VT_BYREF> I_VT_UI1_REF;
    typedef int_<VT_R8 | VT_BYREF> I_VT_R8_REF;
    typedef int_<VT_R4 | VT_BYREF> I_VT_R4_REF;
    typedef int_<VT_INT | VT_BYREF> I_VT_INT_REF;
    typedef int_<VT_I8 | VT_BYREF> I_VT_I8_REF;
    typedef int_<VT_I4 | VT_BYREF> I_VT_I4_REF;
    typedef int_<VT_I2 | VT_BYREF> I_VT_I2_REF;
    typedef int_<VT_I1 | VT_BYREF> I_VT_I1_REF;
    typedef int_<VT_ERROR | VT_BYREF> I_VT_ERROR_REF;
    typedef int_<VT_EMPTY | VT_BYREF> I_VT_EMPTY_REF;
    typedef int_<VT_DISPATCH | VT_BYREF> I_VT_DISPATCH_REF;
    typedef int_<VT_DECIMAL | VT_BYREF> I_VT_DECIMAL_REF;
    typedef int_<VT_DATE | VT_BYREF> I_VT_DATE_REF;
    typedef int_<VT_CY | VT_BYREF> I_VT_CY_REF;
    typedef int_<VT_BSTR | VT_BYREF> I_VT_BSTR_REF;
    typedef int_<VT_BOOL | VT_BYREF> I_VT_BOOL_REF;
    typedef int_<VT_BYREF> I_VT_BYREF;
    typedef int_<VT_VALUE> I_VT_VALUE;


    template<class T>
    struct VariantTraits
    {
        typedef typename call_traits<T>::param_type param_type;
        typedef typename eval_if<
                            or_<
                                is_pointer<param_type>,
                                is_lvalue_reference<param_type>
                            >,
                            InsertConst<param_type>,
                            identity<param_type>
                         >::type const_param_type;
        typedef typename eval_if<
                            is_pointer<param_type>, 
                            I_VT_PTR, 
                            eval_if<
                                is_lvalue_reference<param_type>, 
                                int_<VT_BYREF>, 
                                int_<VT_VALUE> 
                            > 
                         >::type var_type;
        typedef typename eval_if<
                            or_<
                                is_pointer<T>, 
                                not_<
                                    or_<
                                        is_class<T>, 
                                        is_union<T>
                                    > 
                                >
                            >,
                            identity<T>, 
                            add_lvalue_reference<T>
                         >::type return_type;
        typedef typename eval_if<
                            or_<
                                is_pointer<return_type>,
                                is_lvalue_reference<return_type>
                            >,
                            InsertConst<return_type>,
                            identity<return_type>
                         >::type const_return_type;
    };  // struct VariantTraits

#define DECLARE_VAR_TYPE_VARIANT_TRAITS(var_type_, type_, member) \
    template<> \
    struct VariantTraits<var_type_> \
    { \
        typedef type_ param_type; \
        typedef eval_if< \
                    or_< \
                        is_pointer<param_type>, \
                        is_lvalue_reference<param_type> \
                    >, \
                    InsertConst<param_type>, \
                    identity<param_type> \
                >::type const_param_type; \
        typedef var_type_ var_type; \
        typedef type_ return_type; \
        typedef eval_if< \
                    or_< \
                        is_pointer<return_type>, \
                        is_lvalue_reference<return_type> \
                    >, \
                    InsertConst<return_type>, \
                    identity<return_type> \
                >::type const_return_type; \
        inline static return_type Val(VARIANT& source) \
        { \
            return source.##member; \
        } \
        \
        inline static const_return_type Val(const VARIANT& source) \
        { \
            return source.##member; \
        } \
    }; \
    typedef VariantTraits<var_type_> var_type_##_TRAITS; 

    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_I8, LONGLONG, llVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_I4, LONG, lVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_UI1, BYTE, bVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_I2, SHORT, iVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_R4, FLOAT, fltVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_R8, DOUBLE, dblVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_BOOL, VARIANT_BOOL, boolVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_ERROR, SCODE, scode);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_CY, CY&, cyVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_DATE, DATE, date);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_BSTR, BSTR, bstrVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_UNKNOWN, IUnknown*, punkVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_DISPATCH, IDispatch*, pdispVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_I1, CHAR, cVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_UI2, USHORT, uiVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_UI4, ULONG, ulVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_UI8, ULONGLONG, ullVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_INT, INT, intVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_UINT, UINT, uintVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_DECIMAL, DECIMAL&, decVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_VARIANT_REF, VARIANT*, pvarVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_UNKNOWN_REF, IUnknown**, ppunkVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_UINT_REF, UINT*, puintVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_UI8_REF, ULONGLONG*, pullVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_UI4_REF, ULONG*, pulVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_UI2_REF, USHORT*, puiVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_UI1_REF, BYTE*, pbVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_R8_REF, DOUBLE*, pdblVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_R4_REF, FLOAT*, pfltVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_INT_REF, INT*, pintVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_I8_REF, LONGLONG*, pllVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_I4_REF, LONG*, plVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_I2_REF, SHORT*, piVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_I1_REF, CHAR*, pcVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_ERROR_REF, SCODE*, pscode);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_DISPATCH_REF, IDispatch**, ppdispVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_DECIMAL_REF, DECIMAL*, pdecVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_DATE_REF, DATE*, pdate);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_CY_REF, CY*, pcyVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_BSTR_REF, BSTR*, pbstrVal);
    DECLARE_VAR_TYPE_VARIANT_TRAITS(I_VT_BOOL_REF, VARIANT_BOOL*, pboolVal);
    
#undef DECLARE_VAR_TYPE_VARIANT_TRAITS

    template<>
    struct VariantTraits<I_VT_VARIANT>
    {
        typedef VARIANT& param_type; 
        typedef const VARIANT& const_param_type; 
        typedef I_VT_VARIANT var_type; 
        typedef VARIANT& return_type; 
        typedef const VARIANT& const_return_type; 
        inline static return_type Val(VARIANT& source) 
        { 
            return source; 
        } 
        
        inline static const_return_type Val(const VARIANT& source) 
        { 
            return source; 
        } 
    };  // struct VariantTraits<I_VT_VARIANT>
    typedef VariantTraits<I_VT_VARIANT> I_VT_VARIANT_TRAITS; 

#define DECLARE_TYPE_VARIANT_TRAITS(name, var_type_, type_, member) \
    template<> \
    struct VariantTraits<type_> \
    { \
        typedef type_ param_type; \
        typedef eval_if< \
                    or_< \
                        is_pointer<param_type>, \
                        is_lvalue_reference<param_type> \
                    >, \
                    InsertConst<param_type>, \
                    identity<param_type> \
                >::type const_param_type; \
        typedef var_type_ var_type; \
        typedef type_ return_type; \
        typedef eval_if< \
                    or_< \
                        is_pointer<return_type>, \
                        is_lvalue_reference<return_type> \
                    >, \
                    InsertConst<return_type>, \
                    identity<return_type> \
                >::type const_return_type; \
        inline static return_type Val(VARIANT& source) \
        { \
            return source.##member; \
        } \
        \
        inline static const_return_type Val(const VARIANT& source) \
        { \
            return source.##member; \
        } \
    }; \
    typedef VariantTraits<type_> name##_TRAITS; 
    
    DECLARE_TYPE_VARIANT_TRAITS(I_T_I8, I_VT_I8, LONGLONG, llVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_I4, I_VT_I4, LONG, lVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_UI1, I_VT_UI1, BYTE, bVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_I2, I_VT_I2, SHORT, iVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_R4, I_VT_R4, FLOAT, fltVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_R8, I_VT_R8, DOUBLE, dblVal);
    //DECLARE_TYPE_VARIANT_TRAITS(I_T_BOOL, I_VT_BOOL, VARIANT_BOOL, boolVal);
    //DECLARE_TYPE_VARIANT_TRAITS(I_T_ERROR, I_VT_ERROR, SCODE, scode);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_CY, I_VT_CY, CY&, cyVal);
    //DECLARE_TYPE_VARIANT_TRAITS(I_T_DATE, I_VT_DATE, DATE, date);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_BSTR, I_VT_BSTR, BSTR, bstrVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_UNKNOWN, I_VT_UNKNOWN, IUnknown*, punkVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_DISPATCH, I_VT_DISPATCH, IDispatch*, pdispVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_I1, I_VT_I1, CHAR, cVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_UI2, I_VT_UI2, USHORT, uiVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_UI4, I_VT_UI4, ULONG, ulVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_UI8, I_VT_UI8, ULONGLONG, ullVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_INT, I_VT_INT, INT, intVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_UINT, I_VT_UINT, UINT, uintVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_DECIMAL, I_VT_DECIMAL, DECIMAL&, decVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_VARIANT_REF, I_VT_VARIANT_REF, VARIANT*, pvarVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_UNKNOWN_REF, I_VT_UNKNOWN_REF, IUnknown**, ppunkVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_UINT_REF, I_VT_UINT_REF, UINT*, puintVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_UI8_REF, I_VT_UI8_REF, ULONGLONG*, pullVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_UI4_REF, I_VT_UI4_REF, ULONG*, pulVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_UI2_REF, I_VT_UI2_REF, USHORT*, puiVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_UI1_REF, I_VT_UI1_REF, BYTE*, pbVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_R8_REF, I_VT_R8_REF, DOUBLE*, pdblVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_R4_REF, I_VT_R4_REF, FLOAT*, pfltVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_INT_REF, I_VT_INT_REF, INT*, pintVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_I8_REF, I_VT_I8_REF, LONGLONG*, pllVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_I4_REF, I_VT_I4_REF, LONG*, plVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_I2_REF, I_VT_I2_REF, SHORT*, piVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_I1_REF, I_VT_I1_REF, CHAR*, pcVal);
    //DECLARE_TYPE_VARIANT_TRAITS(I_T_ERROR_REF, I_VT_ERROR_REF, SCODE*, pscode);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_DISPATCH_REF, I_VT_DISPATCH_REF, IDispatch**, ppdispVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_DECIMAL_REF, I_VT_DECIMAL_REF, DECIMAL*, pdecVal);
    //DECLARE_TYPE_VARIANT_TRAITS(I_T_DATE_REF, I_VT_DATE_REF, DATE*, pdate);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_CY_REF, I_VT_CY_REF, CY*, pcyVal);
    DECLARE_TYPE_VARIANT_TRAITS(I_T_BSTR_REF, I_VT_BSTR_REF, BSTR*, pbstrVal);
    //DECLARE_TYPE_VARIANT_TRAITS(I_T_BOOL_REF, I_VT_BOOL_REF, VARIANT_BOOL*, pboolVal);

#undef DECLARE_TYPE_VARIANT_TRAITS

}}}   // namespace Urasandesu { namespace NAnonym { namespace Traits {

#endif  // #ifndef URASANDESU_NANONYM_TRAITS_VARIANTTRAITS_H