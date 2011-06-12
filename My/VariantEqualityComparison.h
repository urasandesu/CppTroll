#pragma once
#ifndef INCLUDED_VARIANTEQUALITYCOMPARISON_H
#define INCLUDED_VARIANTEQUALITYCOMPARISON_H

#ifndef INCLUDED_VARIANTTRAITS_H
#include "VariantTraits.h"
#endif

namespace My
{
    template<class VarType>
    struct VariantEqualityComparison : 
        private VariantTraits<VarType>
    {
        inline static bool Equals(const VARIANT& var1, const VARIANT& var2);
    };

#define DECLARE_VARIANT_EQUALITY_COMPARISON(var_type_) \
    template<> \
    struct VariantEqualityComparison<var_type_> :  \
        private VariantTraits<var_type_> \
    { \
        inline static bool Equals(const VARIANT& var1, const VARIANT& var2) \
        { \
            return VariantEquals<const_param_type>(Val(var1), Val(var2), var_type()); \
        } \
    }; \

    DECLARE_VARIANT_EQUALITY_COMPARISON(I_VT_VARIANT);
    
#undef DECLARE_VARIANT_EQUALITY_COMPARISON

}   // namespace My

#endif  // #ifndef INCLUDED_VARIANTEQUALITYCOMPARISON_H