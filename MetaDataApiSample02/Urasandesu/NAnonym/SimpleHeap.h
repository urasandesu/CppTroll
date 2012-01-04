#pragma once
#ifndef URASANDESU_NANONYM_SIMPLEHEAP_H
#define URASANDESU_NANONYM_SIMPLEHEAP_H

#ifndef URASANDESU_NANONYM_RAPIDVECTOR_H
#include <Urasandesu/NAnonym/RapidVector.h>
#endif

namespace Urasandesu { namespace NAnonym {
    
    struct DefaultHeap;
    struct ALotOfAllocAndFreeHeap;  // The type size is less than 32 - 40 and 
                                    // they are a lot of allocated and freed.
    
    namespace Detail {
    
        template<class T, class Tag>
        struct SimpleHeapImpl;
        
        template<class T>
        class SimpleHeapImpl<T, ALotOfAllocAndFreeHeap>
        {
        public:
            typedef RapidVector<T> TArray;
            
            SimpleHeapImpl() : m_pCurrent(&m_array[0]), m_lastMaxSize(m_array.max_size()) { }

            T *New()
            {
                T *pObj = NULL;
                m_array.resize(m_array.size() + 1);
                if (m_lastMaxSize < m_array.max_size())
                {
                    m_lastMaxSize = m_array.max_size();
                    m_pCurrent = &m_array[0] + m_array.size() - 1;
                }
                pObj = m_pCurrent;
                ++m_pCurrent;
                new(pObj)T();
                return pObj;
            }

            SIZE_T Size()
            {
                return m_array.size();
            }
            
            T *operator[] (SIZE_T ix)
            {
                return &m_array[ix];
            }
            
            ~SimpleHeapImpl()
            {
                for (T const *i = &m_array[0], *i_end = i + m_array.size(); i != i_end; ++i)
                    (*i).~T();
            }
        
        private:    
            TArray m_array;
            T *m_pCurrent;
            SIZE_T m_lastMaxSize;
        };
    
        template<class T>
        class SimpleHeapImpl<T, DefaultHeap>
        {
        public:
            T *New()
            {
                T *pObj = new T();
                m_array.push_back(pObj);
                return pObj;
            }
        
        private:
            boost::ptr_vector<T> m_array;
        };
    }
    
    template<
        class T, 
        class Tag = DefaultHeap
    >
    class SimpleHeap
    {
        Detail::SimpleHeapImpl<T, Tag> m_impl;
        
    public:
        T *New()
        {
            return m_impl.New();
        }
    };
    
}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_SIMPLEHEAP_H