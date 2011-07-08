#pragma once
#ifndef URASANDESU_NANONYM_UTILITIES_VARIANTEQUALITYCOMPARISON_H
#define URASANDESU_NANONYM_UTILITIES_VARIANTEQUALITYCOMPARISON_H

#ifndef URASANDESU_NANONYM_TRAITS_VARIANTTRAITS_H
#include "Urasandesu/NAnonym/Traits/VariantTraits.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Utilities {

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

}}}   // namespace Urasandesu { namespace NAnonym { namespace Utilities {

#endif  // #ifndef URASANDESU_NANONYM_UTILITIES_VARIANTEQUALITYCOMPARISON_H