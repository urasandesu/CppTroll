﻿#pragma once
#ifndef URASANDESU_NANONYM_NANONYMDEPENDSON_H
#define URASANDESU_NANONYM_NANONYMDEPENDSON_H

#include <boost/exception/all.hpp>
#include <boost/exception/errinfo_nested_exception.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/scope_exit.hpp>
#include <boost/system/windows_error.hpp>
#include <boost/type_traits.hpp>
#include <corhlpr.h>    // This header needs the definitions. You must include the 
                        // implementation file, named corhlpr.cpp at only once. 
                        // In this time, I include it in stdafx.cpp.
#include <comdef.h>
#include <tlhelp32.h>
#include <Dbghelp.h>

namespace Urasandesu { namespace NAnonym {

}}   // namespace Urasandesu { namespace NAnonym {

#ifndef URASANDESU_NANONYM_METADATA_METADATADEPENDSON_H
#include <Urasandesu/NAnonym/MetaData/MetaDataDependsOn.h>
#endif

#ifndef URASANDESU_NANONYM_TRAITS_TRAITSDEPENDSON_H
#include <Urasandesu/NAnonym/Traits/TraitsDependsOn.h>
#endif

#endif  // #ifndef URASANDESU_NANONYM_NANONYMDEPENDSON_H