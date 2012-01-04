#pragma once
#ifndef URASANDESU_NANONYM_NANONYMDEPENDSON_H
#define URASANDESU_NANONYM_NANONYMDEPENDSON_H

#ifndef URASANDESU_NANONYM_METADATA_METADATADEPENDSON_H
#include <Urasandesu/NAnonym/MetaData/MetaDataDependsOn.h>
#endif

#include <boost/call_traits.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/system/windows_error.hpp>
#include <boost/type_traits.hpp>
#include <corhlpr.h>    // This header needs the definitions. You must include the 
                        // implementation file, named corhlpr.cpp at only once. 
                        // In this time, I include it in stdafx.cpp.
#include <vector>

namespace Urasandesu { namespace NAnonym {

}}   // namespace Urasandesu { namespace NAnonym {

#endif  // #ifndef URASANDESU_NANONYM_NANONYMDEPENDSON_H