#pragma once
#ifndef URASANDESU_CPPANONYM_HEAPPROVIDER_H
#define URASANDESU_CPPANONYM_HEAPPROVIDER_H

#ifndef URASANDESU_CPPANONYM_SIMPLEHEAP_H
#include <Urasandesu/CppAnonym/SimpleHeap.h>
#endif

#ifndef URASANDESU_CPPANONYM_TRAITS_UNIQUE_H
#include <Urasandesu/CppAnonym/Traits/Unique.h>
#endif

namespace Urasandesu { namespace CppAnonym {
    
    namespace Detail {

        template<class Key, class Sequence, class I, class IEnd>
        class HeapProviderImpl : 
            public HeapProviderImpl<Key, Sequence, typename boost::mpl::next<I>::type, IEnd>
        {
        private:
            typedef typename boost::mpl::deref<I>::type obj_type;
            BOOST_MPL_ASSERT((boost::is_base_of<IHeapContent<Key>, obj_type>));

            boost::shared_ptr<SimpleHeap<obj_type>> mutable m_objFactory;
            boost::unordered_map<Key, SIZE_T> mutable m_objIndexes;
            
            SimpleHeap<obj_type> *GetHeap() const
            {
                if (!m_objFactory.get())
                {
                    m_objFactory = boost::make_shared<SimpleHeap<obj_type>>();
                }
                return m_objFactory.get();
            }

        public:
            SIZE_T Size() const
            {
                return GetHeap()->Size();
            }
            
            bool Exists(Key key) const
            {
                return m_objIndexes.find(key) != m_objIndexes.end();
            }
            
            obj_type *Get(Key key)
            {
                return (*GetHeap())[m_objIndexes[key]];
            }
            
            obj_type const *Get(Key key) const
            {
                return (*GetHeap())[m_objIndexes[key]];
            }
            
            void Set(Key key, SIZE_T index)
            {
                m_objIndexes[key] = index;
                Get(key)->SetKey(key);
            }
            
            void SetToLast(Key key)
            {
                Set(key, Size() - 1);
            }
            
            obj_type *NewPseudo()
            {
                obj_type *pObj = GetHeap()->New();
                return pObj;
            }

            obj_type *New(Key key)
            {
                if (Exists(key))
                {
                    Get(key)->SetKey(Key());
                }
                obj_type *pObj = GetHeap()->New();
                SetToLast(key);
                return pObj;
            }
            
            obj_type *Peek() const
            {
                if (GetHeap()->Size() == 0)
                {
                    return NULL;
                }
                else
                {
                    return (*GetHeap())[GetHeap()->Size() - 1];
                }
            }
        };

        template<class Key, class Sequence>
        class HeapProviderImpl<Key, 
                               Sequence, 
                               typename Traits::UniqueEnd<Sequence>::type, 
                               typename Traits::UniqueEnd<Sequence>::type>
        {
        };

    }   // namespace Detail


#ifdef PROVIDER_TYPE_DECIDED_BY_TYPE
#error This .h temporarily reserves the word "PROVIDER_TYPE_DECIDED_BY_TYPE".
#else
#define PROVIDER_TYPE_DECIDED_BY_TYPE(t, key, sequence) \
    Detail::HeapProviderImpl< \
        key, \
        sequence, \
        typename boost::mpl::find< \
            typename Traits::Unique<sequence>::type, \
            t \
        >::type, \
        typename Traits::UniqueEnd<sequence>::type \
    >

    template<class Key, class Sequence>
    class HeapProvider : 
        Detail::HeapProviderImpl<Key, 
                                 Sequence, 
                                 typename Traits::UniqueBegin<Sequence>::type, 
                                 typename Traits::UniqueEnd<Sequence>::type>
    {
    public:
        template<class T>
        PROVIDER_TYPE_DECIDED_BY_TYPE(T, Key, Sequence) &Of()
        {
            return static_cast<PROVIDER_TYPE_DECIDED_BY_TYPE(T, Key, Sequence) &>(*this);
        }

        template<class T>
        PROVIDER_TYPE_DECIDED_BY_TYPE(T, Key, Sequence) const &Of() const
        {
            return static_cast<PROVIDER_TYPE_DECIDED_BY_TYPE(T, Key, Sequence) const &>(*this);
        }
    };

#undef PROVIDER_TYPE_DECIDED_BY_TYPE
#endif




#define CPPANONYM_BEGIN_HEAP_PROVIDER_DECLARATION() \
    private: \
        template<class T> \
        Urasandesu::CppAnonym::SimpleHeap<T> *GetHeap(); \
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


#define CPPANONYM_HEAP_PROVIDER(t, key_, name) \
    private: \
        boost::shared_ptr<Urasandesu::CppAnonym::SimpleHeap<t>> name; \
        boost::unordered_map<key_, SIZE_T> name##Indexes; \
         \
        template<> \
        Urasandesu::CppAnonym::SimpleHeap<t> *GetHeap() \
        { \
            if (!name.get()) \
            { \
                name = boost::make_shared<Urasandesu::CppAnonym::SimpleHeap<t>>(); \
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

#define CPPANONYM_END_HEAP_PROVIDER_DECLARATION()

}}   // namespace Urasandesu { namespace CppAnonym {

#endif  // #ifndef URASANDESU_CPPANONYM_HEAPPROVIDER_H