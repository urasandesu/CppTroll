#pragma once
#ifndef URASANDESU_CPPANONYM_SIMPLEHEAP_H
#define URASANDESU_CPPANONYM_SIMPLEHEAP_H

namespace Urasandesu { namespace CppAnonym {
    
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
            typedef CQuickArray<T> TArray;        
            
            SimpleHeapImpl() : m_pCurrent(m_array.Ptr()), m_lastMaxSize(m_array.MaxSize()) { }

            T *New()
            {
                HRESULT hr = E_FAIL;
                T *pObj = NULL;
                hr = m_array.ReSizeNoThrow(m_array.Size() + 1);
                if (m_lastMaxSize < m_array.MaxSize())
                {
                    m_lastMaxSize = m_array.MaxSize();
                    m_pCurrent = m_array.Ptr() + m_array.Size() - 1;
                }
                if (FAILED(hr))
                    BOOST_THROW_EXCEPTION(CppAnonymCOMException(hr));
                pObj = m_pCurrent;
                ++m_pCurrent;
                new(pObj)T();
                return pObj;
            }

            SIZE_T Size()
            {
                return m_array.Size();
            }
            
            T *operator[] (SIZE_T ix)
            {
                return &m_array[ix];
            }
            
            ~SimpleHeapImpl()
            {
                for (T const *i = m_array.Ptr(), *i_end = i + m_array.Size(); i != i_end; ++i)
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
            
            SIZE_T Size()
            {
                return m_array.size();
            }
            
            T *operator[] (SIZE_T ix)
            {
                return &m_array[ix];
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
        
        SIZE_T Size()
        {
            return m_impl.Size();
        }

        T *operator[] (SIZE_T ix)
        {
            return m_impl[ix];
        }
    };
    
}}  // namespace Urasandesu { namespace CppAnonym {

#endif  // URASANDESU_CPPANONYM_SIMPLEHEAP_H