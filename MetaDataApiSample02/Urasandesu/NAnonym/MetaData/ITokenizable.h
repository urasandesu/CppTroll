#pragma once
#ifndef URASANDESU_NANONYM_METADATA_ITOKENIZABLE_H
#define URASANDESU_NANONYM_METADATA_ITOKENIZABLE_H

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    class ATL_NO_VTABLE ITokenizable
    {
    private:
        mdToken m_token;

    public:
        ITokenizable() : m_token(mdTokenNil) { }
                
        mdToken GetToken()
        {
            return m_token;
        }
        
        void SetToken(mdToken token)
        {
            m_token = token;
        }
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_ITOKENIZABLE_H