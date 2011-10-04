#pragma once
#ifndef URASANDESU_NANONYM_METADATA_ITOKENIZABLE_H
#define URASANDESU_NANONYM_METADATA_ITOKENIZABLE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    class ATL_NO_VTABLE ITokenizable
    {
    private:
        mdToken m_tokenRef;
        mdToken m_token;

    public:
        ITokenizable() : m_tokenRef(mdTokenNil), m_token(mdTokenNil) { }
                
        mdToken GetToken()
        {
            return IsNilToken(m_tokenRef) ? m_token : m_tokenRef;
        }
        
        void SetToken(mdToken token)
        {
            mdToken type = TypeFromToken(token);
            if (type == mdtTypeRef || 
                type == mdtMemberRef || 
                type == mdtModuleRef || 
                type == mdtAssemblyRef)
            {
                m_tokenRef = token;
            }
            else
            {
                m_token = token;
            }
        }
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_ITOKENIZABLE_H