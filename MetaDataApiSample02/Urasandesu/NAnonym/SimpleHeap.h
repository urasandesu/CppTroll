#pragma once
#ifndef URASANDESU_NANONYM_SIMPLEHEAP_H
#define URASANDESU_NANONYM_SIMPLEHEAP_H

namespace Urasandesu { namespace NAnonym {
    
    template<class T>
    class SimpleHeap
    {
    public:
        typedef CQuickArray<T> TArray;        
        
        SimpleHeap() : m_pCurrent(m_array.Ptr()), m_lastMaxSize(m_array.MaxSize()) { }
 
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
        
        ~SimpleHeap()
        {
            for (T const *i = m_array.Ptr(), *i_end = i + m_array.Size(); i != i_end; ++i)
                (*i).~T();
        }
    
    private:    
        TArray m_array;
        T *m_pCurrent;
        SIZE_T m_lastMaxSize;
    };
    
}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_SIMPLEHEAP_H