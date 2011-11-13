#pragma once
#ifndef URASANDESU_CPPANONYM_SIMPLEBLOB_H
#define URASANDESU_CPPANONYM_SIMPLEBLOB_H

namespace Urasandesu { namespace CppAnonym {
    
    class SimpleBlob
    {
        typedef CQuickArray<BYTE> ByteArray;        

        ByteArray m_buffer;
        BYTE *m_pCurrent;

    public:
        SimpleBlob() : m_pCurrent(m_buffer.Ptr()) { }

        template<class T>
        HRESULT Put(T val)
        {
            using namespace boost;            
            using namespace boost::mpl;
            
            BOOST_MPL_ASSERT((or_<is_arithmetic<T>, is_pod<T>>));

            return Put(&val, sizeof(T));
        }
        
        HRESULT Put(void const *p, SIZE_T size)
        {
            _ASSERT(0 <= size);
            HRESULT hr = m_buffer.ReSizeNoThrow(m_buffer.Size() + size);
            if (FAILED(hr))
                return hr;
            ::memcpy_s(m_pCurrent, size, p, size);
            m_pCurrent += size;
            return S_OK;
        }
        
        BYTE *Ptr()
        {
            return m_buffer.Ptr();
        }
        
        BYTE const *Ptr() const
        {
            return m_buffer.Ptr();
        }
        
        SIZE_T Size() const
        { 
            return m_buffer.Size();
        }

        SIZE_T MaxSize() const
        { 
            return m_buffer.MaxSize();
        }

        BYTE& operator[] (SIZE_T ix)
        { 
            return m_buffer[ix];
        }

        const BYTE& operator[] (SIZE_T ix) const
        { 
            return m_buffer[ix];
        }
    };
    
}}  // namespace Urasandesu { namespace CppAnonym {

#endif  // URASANDESU_CPPANONYM_SIMPLEBLOB_H