#pragma once
#ifndef URASANDESU_NANONYM_DEFAULTSTDMETHODWRAPPER_H
#define URASANDESU_NANONYM_DEFAULTSTDMETHODWRAPPER_H

#ifndef URASANDESU_NANONYM_NANONYMEXCEPTION_H
#include <Urasandesu/NAnonym/NAnonymException.h>
#endif

namespace Urasandesu { namespace NAnonym {

#define NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER_ARG(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) BOOST_PP_TUPLE_ELEM(2, 0, elem) BOOST_PP_TUPLE_ELEM(2, 1, elem)

#define NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER_LOAD_ARG(r, data, i, elem) \
    BOOST_PP_COMMA_IF(i) BOOST_PP_TUPLE_ELEM(2, 1, elem)

#define NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER(method, args_tuple_seq) \
    public: \
        STDMETHOD(method)(BOOST_PP_SEQ_FOR_EACH_I(NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER_ARG, _, args_tuple_seq)) \
        { \
            using namespace std; \
            using namespace boost; \
            using namespace Urasandesu::NAnonym; \
             \
            try \
            { \
                return method##Core(BOOST_PP_SEQ_FOR_EACH_I(NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER_LOAD_ARG, _, args_tuple_seq)); \
            } \
            catch (NAnonymException &e) \
            { \
                cout << diagnostic_information(e) << endl; \
            } \
            catch (...) \
            { \
                cout << diagnostic_information(boost::current_exception()) << endl; \
            } \
             \
            return S_OK; \
        } \
         \
    protected: \
        STDMETHOD(method##Core)(BOOST_PP_SEQ_FOR_EACH_I(NANONYM_DECLARE_DEFAULT_STDMETHOD_WRAPPER_ARG, _, args_tuple_seq)) \
        { \
            return S_OK; \
        }

}}   // namespace Urasandesu { namespace NAnonym {

#endif  // #ifndef URASANDESU_NANONYM_DEFAULTSTDMETHODWRAPPER_H