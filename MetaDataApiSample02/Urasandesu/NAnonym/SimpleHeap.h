#pragma once
#ifndef URASANDESU_NANONYM_SIMPLEHEAP_H
#define URASANDESU_NANONYM_SIMPLEHEAP_H

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
                    BOOST_THROW_EXCEPTION(NAnonymCOMException(hr));
                pObj = m_pCurrent;
                ++m_pCurrent;
                new(pObj)T();
                return pObj;
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