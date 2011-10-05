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
     
            HRESULT New(T **ppObj)
            {
                HRESULT hr = E_FAIL;
                hr = m_array.ReSizeNoThrow(m_array.Size() + 1);
                if (m_lastMaxSize < m_array.MaxSize())
                {
                    m_lastMaxSize = m_array.MaxSize();
                    m_pCurrent = m_array.Ptr() + m_array.Size() - 1;
                }
                if (FAILED(hr))
                    return hr;
                *ppObj = m_pCurrent;
                ++m_pCurrent;
                new(*ppObj)T();
                return S_OK;
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
            HRESULT New(T **ppObj)
            {
                *ppObj = new T();
                m_array.push_back(*ppObj);
                return S_OK;
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
        HRESULT New(T **ppObj)
        {
            return m_impl.New(ppObj);
        }
    };
    
}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_SIMPLEHEAP_H