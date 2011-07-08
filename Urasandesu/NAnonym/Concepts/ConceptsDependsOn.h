#pragma once
#ifndef URASANDESU_NANONYM_CONCEPTS_CONCEPTSDEPENDSON_H
#define URASANDESU_NANONYM_CONCEPTS_CONCEPTSDEPENDSON_H

#ifndef URASANDESU_NANONYM_NANONYMDEPENDSON_H
#include "Urasandesu/NAnonym/NAnonymDependsOn.h"
#endif

#include <boost/concept/assert.hpp>
#include <boost/concept/usage.hpp>
#include <boost/concept_check.hpp>

namespace Urasandesu { namespace NAnonym { namespace Concepts {

    using boost::is_base_of;

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_CONCEPTS_CONCEPTSDEPENDSON_H