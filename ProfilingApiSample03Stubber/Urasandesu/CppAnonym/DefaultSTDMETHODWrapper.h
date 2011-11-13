#pragma once
#ifndef URASANDESU_CPPANONYM_DEFAULTSTDMETHODWRAPPER_H
#define URASANDESU_CPPANONYM_DEFAULTSTDMETHODWRAPPER_H

#ifndef URASANDESU_CPPANONYM_CPPANONYMEXCEPTION_H
#include <Urasandesu/CppAnonym/CppAnonymException.h>
#endif

namespace Urasandesu { namespace CppAnonym {

#define CPPANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER_ARG(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) BOOST_PP_TUPLE_ELEM(2, 0, elem) BOOST_PP_TUPLE_ELEM(2, 1, elem)

#define CPPANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER_LOAD_ARG(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) BOOST_PP_TUPLE_ELEM(2, 1, elem)

#define CPPANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(method, args_tuple_seq) \
    public: \
        STDMETHOD(method)(BOOST_PP_SEQ_FOR_EACH_I(CPPANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER_ARG, _, args_tuple_seq)) \
        { \
            using namespace std; \
            using namespace boost; \
            using namespace Urasandesu::CppAnonym; \
             \
            try \
            { \
                return method##Core(BOOST_PP_SEQ_FOR_EACH_I(CPPANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER_LOAD_ARG, _, args_tuple_seq)); \
            } \
            catch (CppAnonymException &e) \
            { \
                cout << diagnostic_information(e) << endl; \
            } \
            catch (...) \
            { \
                cout << diagnostic_information(current_exception()) << endl; \
            } \
             \
            return S_OK; \
        } \
         \
    protected: \
        STDMETHOD(method##Core)(BOOST_PP_SEQ_FOR_EACH_I(CPPANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER_ARG, _, args_tuple_seq)) \
        { \
            return S_OK; \
        }

}}   // namespace Urasandesu { namespace CppAnonym {

#endif  // #ifndef URASANDESU_CPPANONYM_DEFAULTSTDMETHODWRAPPER_H