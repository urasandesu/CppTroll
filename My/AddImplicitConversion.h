#pragma once
#include <boost/preprocessor.hpp>

namespace My
{
    template<class T>
    struct AddImplicitConversion
    {
        AddImplicitConversion(T& other) { }
        AddImplicitConversion& operator=(T& other) { return *this; }
    };

    #define SIZE 11

    #define IGNORE_PARAM(z, n, _) \
        template<template<BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, BOOST_PP_INC(n), class T)> class Container> \
        struct IgnoreParam ## n \
        { \
        };

    BOOST_PP_REPEAT_FROM_TO(1, SIZE, IGNORE_PARAM, nil)

    #undef IGNORE_PARAM

    #define ADD_IMPLICIT_CONVERSION(z, n, _) \
        template<template<BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, BOOST_PP_INC(n), class T)> class Container> \
        struct AddImplicitConversion<IgnoreParam ## n<Container>> \
        { \
            template<BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, BOOST_PP_INC(n), class T)> \
            AddImplicitConversion(Container<BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, BOOST_PP_INC(n), T)>& other) { } \
            template<BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, BOOST_PP_INC(n), class T)> \
            AddImplicitConversion& operator=(Container<BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, BOOST_PP_INC(n), T)>& other) { return *this; } \
        };

    BOOST_PP_REPEAT_FROM_TO(1, SIZE, ADD_IMPLICIT_CONVERSION, nil)

    #undef ADD_IMPLICIT_CONVERSION
    
    #undef SIZE
}   // namespace My