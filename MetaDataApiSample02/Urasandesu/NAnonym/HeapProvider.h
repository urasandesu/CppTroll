#pragma once
#ifndef URASANDESU_NANONYM_HEAPPROVIDER_H
#define URASANDESU_NANONYM_HEAPPROVIDER_H

#ifndef URASANDESU_NANONYM_SIMPLEHEAP_H
#include <Urasandesu/NAnonym/SimpleHeap.h>
#endif

namespace Urasandesu { namespace NAnonym {

#define BEGIN_NANONYM_HEAP_PROVIDER() \
    public: \
        template<class T> \
        Urasandesu::NAnonym::SimpleHeap<T> *GetHeap();


#define DECLARE_NANONYM_HEAP_PROVIDER(t, name) \
    private: \
        boost::shared_ptr<Urasandesu::NAnonym::SimpleHeap<t>> name; \
    public: \
        template<> \
        Urasandesu::NAnonym::SimpleHeap<t> *GetHeap() \
        { \
            if (!name.get()) \
            { \
                name = boost::make_shared<Urasandesu::NAnonym::SimpleHeap<t>>(); \
            } \
            return name.get(); \
        }

#define END_NANONYM_HEAP_PROVIDER()

}}   // namespace Urasandesu { namespace NAnonym {

#endif  // #ifndef URASANDESU_NANONYM_HEAPPROVIDER_H