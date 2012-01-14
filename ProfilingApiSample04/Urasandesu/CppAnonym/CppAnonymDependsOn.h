#pragma once
#ifndef URASANDESU_CPPANONYM_CPPANONYMDEPENDSON_H
#define URASANDESU_CPPANONYM_CPPANONYMDEPENDSON_H

#include <boost/call_traits.hpp>
#include <boost/exception/all.hpp>
#include <boost/exception/errinfo_nested_exception.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/or.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/scope_exit.hpp>
#include <boost/system/windows_error.hpp>
#include <boost/type_traits.hpp>
#include <boost/unordered_map.hpp>
#include <corhlpr.h>    // This header needs the definitions. You must include the 
                        // implementation file, named corhlpr.cpp at only once. 
                        // In this time, I include it in stdafx.cpp.
#include <comdef.h>
#include <tlhelp32.h>
#include <Dbghelp.h>

namespace Urasandesu { namespace CppAnonym {

}}   // namespace Urasandesu { namespace CppAnonym {

#ifndef URASANDESU_CPPANONYM_METADATA_METADATADEPENDSON_H
#include <Urasandesu/CppAnonym/MetaData/MetaDataDependsOn.h>
#endif

#ifndef URASANDESU_CPPANONYM_PROFILING_PROFILINGDEPENDSON_H
#include <Urasandesu/CppAnonym/Profiling/ProfilingDependsOn.h>
#endif

#ifndef URASANDESU_CPPANONYM_TRAITS_TRAITSDEPENDSON_H
#include <Urasandesu/CppAnonym/Traits/TraitsDependsOn.h>
#endif

#ifndef URASANDESU_CPPANONYM_UTILITIES_UTILITIESDEPENDSON_H
#include <Urasandesu/CppAnonym/Utilities/UtilitiesDependsOn.h>
#endif

#endif  // #ifndef URASANDESU_CPPANONYM_CPPANONYMDEPENDSON_H