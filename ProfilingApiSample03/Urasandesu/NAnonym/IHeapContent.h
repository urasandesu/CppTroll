#pragma once
#ifndef URASANDESU_NANONYM_IHEAPCONTENT_H
#define URASANDESU_NANONYM_IHEAPCONTENT_H

namespace Urasandesu { namespace NAnonym {

    template<class Key>
    class ATL_NO_VTABLE IHeapContent
    {
    public:
        IHeapContent() : 
            m_key(Key())
        { }
        
        Key GetKey()
        {
            return m_key;
        }
        
        void SetKey(Key key)
        {
            m_key = key;
        }
        
        bool IsPseudo()
        {
            return m_key == Key();
        }
        
    private:        
        Key m_key;
    }; 
    
}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_IHEAPCONTENT_H