#pragma once
#ifndef URASANDESU_CPPANONYM_HEAPPROVIDER_H
#define URASANDESU_CPPANONYM_HEAPPROVIDER_H

#ifndef URASANDESU_CPPANONYM_SIMPLEHEAP_H
#include <Urasandesu/CppAnonym/SimpleHeap.h>
#endif

#ifndef URASANDESU_CPPANONYM_TRAITS_DISTINCT_H
#include <Urasandesu/CppAnonym/Traits/Distinct.h>
#endif

namespace Urasandesu { namespace CppAnonym {
    
    namespace Detail {

        template<class Key, class Sequence, class I, class IEnd>
        class ATL_NO_VTABLE HeapProviderImpl : 
            public HeapProviderImpl<Key, Sequence, typename boost::mpl::next<I>::type, IEnd>
        {
        private:
            typedef typename boost::mpl::deref<I>::type obj_type;
            BOOST_MPL_ASSERT((boost::is_base_of<IHeapContent<Key>, obj_type>));
            typedef typename boost::call_traits<Key>::param_type key_param_type;

            boost::shared_ptr<SimpleHeap<obj_type>> mutable m_objFactory;
            boost::unordered_map<Key, SIZE_T> mutable m_objIndexes;
            
            inline SimpleHeap<obj_type> *GetHeap() const
            {
                if (!m_objFactory.get())
                    m_objFactory = boost::make_shared<SimpleHeap<obj_type>>();
                return m_objFactory.get();
            }

        public:
            inline SIZE_T Size() const
            {
                return GetHeap()->Size();
            }
            
            inline bool Exists(key_param_type key) const
            {
                return m_objIndexes.find(key) != m_objIndexes.end();
            }
            
            inline obj_type *Get(key_param_type key)
            {
                return (*GetHeap())[m_objIndexes[key]];
            }
            
            inline obj_type const *Get(key_param_type key) const
            {
                return (*GetHeap())[m_objIndexes[key]];
            }
            
            inline void Set(key_param_type key, SIZE_T index)
            {
                m_objIndexes[key] = index;
                Get(key)->SetKey(key);
            }
            
            inline void SetToLast(key_param_type key)
            {
                Set(key, Size() - 1);
            }
            
            inline obj_type *NewPseudo()
            {
                obj_type *pObj = GetHeap()->New();
                return pObj;
            }

            inline obj_type *New(key_param_type key)
            {
                if (Exists(key))
                    Get(key)->SetKey(Key());
                obj_type *pObj = GetHeap()->New();
                SetToLast(key);
                return pObj;
            }
            
            inline obj_type *Peek() const
            {
                return GetHeap()->Size() == 0 ? NULL : (*GetHeap())[GetHeap()->Size() - 1];
            }
        };

        template<class Key, class Sequence>
        class ATL_NO_VTABLE HeapProviderImpl<Key, 
                                             Sequence, 
                                             typename Traits::DistinctEnd<Sequence>::type, 
                                             typename Traits::DistinctEnd<Sequence>::type> : 
            boost::noncopyable
        {
        };

    }   // namespace Detail


    template<class Key, class Sequence>
    class ATL_NO_VTABLE HeapProvider : 
        Detail::HeapProviderImpl<Key, 
                                 Sequence, 
                                 typename Traits::DistinctBegin<Sequence>::type, 
                                 typename Traits::DistinctEnd<Sequence>::type>
    {
    public:
        template<class T>
        struct type_decided_by
        {
            typedef Detail::HeapProviderImpl<
                Key,
                Sequence,
                typename boost::mpl::find<
                    typename Traits::Distinct<Sequence>::type,
                    T
                >::type,
                typename Traits::DistinctEnd<Sequence>::type
            > type;
        };

        template<class T>
        inline typename type_decided_by<T>::type &Of()
        {
            return static_cast<typename type_decided_by<T>::type &>(*this);
        }

        template<class T>
        inline typename type_decided_by<T>::type const &Of() const
        {
            return const_cast<HeapProvider<Key, Sequence> *>(this)->Of<T>();
        }
    };




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