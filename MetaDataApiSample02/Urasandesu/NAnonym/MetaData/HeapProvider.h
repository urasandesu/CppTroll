#pragma once
#ifndef URASANDESU_NANONYM_METADATA_HEAPPROVIDER_H
#define URASANDESU_NANONYM_METADATA_HEAPPROVIDER_H

#ifndef URASANDESU_NANONYM_SIMPLEHEAP_H
#include <Urasandesu/NAnonym/SimpleHeap.h>
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

#define BEGIN_META_DATA_HEAP_PROVIDER() \
    public: \
        template<class T> \
        Urasandesu::NAnonym::SimpleHeap<T> *GetHeap();


#define DECLARE_META_DATA_HEAP_PROVIDER(t, name) \
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

#define END_META_DATA_HEAP_PROVIDER()

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_HEAPPROVIDER_H