#pragma once
#ifndef URASANDESU_NANONYM_HEAPPROVIDER_H
#define URASANDESU_NANONYM_HEAPPROVIDER_H

#ifndef URASANDESU_NANONYM_SIMPLEHEAP_H
#include <Urasandesu/NAnonym/SimpleHeap.h>
#endif

namespace Urasandesu { namespace NAnonym {

#define NANONYM_BEGIN_HEAP_PROVIDER_DECLARATION() \
    private: \
        template<class T> \
        Urasandesu::NAnonym::SimpleHeap<T> *GetHeap(); \
    public: \
        template<class T> \
        SIZE_T Size(); \
         \
        template<class T, class Key> \
        bool Exists(Key key); \
         \
        template<class T, class Key> \
        T *Get(Key key); \
         \
        template<class T, class Key> \
        void Set(Key key, SIZE_T index); \
         \
        template<class T, class Key> \
        void SetToLast(Key key); \
         \
        template<class T> \
        T *NewPseudo(); \
         \
        template<class T, class Key> \
        T *New(Key key); \
         \
        template<class T> \
        T *Peek();


#define NANONYM_HEAP_PROVIDER(t, key_, name) \
    private: \
        boost::shared_ptr<Urasandesu::NAnonym::SimpleHeap<t>> name; \
        boost::unordered_map<key_, SIZE_T> name##Indexes; \
         \
        template<> \
        Urasandesu::NAnonym::SimpleHeap<t> *GetHeap() \
        { \
            if (!name.get()) \
            { \
                name = boost::make_shared<Urasandesu::NAnonym::SimpleHeap<t>>(); \
            } \
            return name.get(); \
        } \
    public: \
        template<> \
        SIZE_T Size<t>() \
        { \
            return GetHeap<t>()->Size(); \
        } \
         \
        template<> \
        bool Exists<t>(key_ key) \
        { \
            return name##Indexes.find(key) != name##Indexes.end(); \
        } \
         \
        template<> \
        t *Get(key_ key) \
        { \
            return (*GetHeap<t>())[name##Indexes[key]]; \
        } \
         \
        template<> \
        void Set<t>(key_ key, SIZE_T index) \
        { \
            name##Indexes[key] = index; \
            Get<t>(key)->SetKey(key); \
        } \
         \
        template<> \
        void SetToLast<t>(key_ key) \
        { \
            Set<t>(key, Size<t>() - 1); \
        } \
         \
        template<> \
        t *NewPseudo() \
        { \
            t *pObj = GetHeap<t>()->New(); \
            return pObj; \
        } \
         \
        template<> \
        t *New(key_ key) \
        { \
            if (Exists<t>(key)) \
            { \
                Get<t>(key)->SetKey(key_()); \
            } \
            t *pObj = GetHeap<t>()->New(); \
            SetToLast<t>(key); \
            return pObj; \
        } \
         \
        template<> \
        t *Peek() \
        { \
            if (GetHeap<t>()->Size() == 0) \
            { \
                return NULL; \
            } \
            else \
            { \
                return (*GetHeap<t>())[GetHeap<t>()->Size() - 1]; \
            } \
        }

#define NANONYM_END_HEAP_PROVIDER_DECLARATION()

}}   // namespace Urasandesu { namespace NAnonym {

#endif  // #ifndef URASANDESU_NANONYM_HEAPPROVIDER_H