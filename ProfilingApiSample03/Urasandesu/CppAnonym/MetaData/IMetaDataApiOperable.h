#pragma once
#ifndef URASANDESU_CPPANONYM_METADATA_IMETADATAAPIOPERABLE_H
#define URASANDESU_CPPANONYM_METADATA_IMETADATAAPIOPERABLE_H

#ifndef URASANDESU_CPPANONYM_IHEAPCONTENT_H
#include <Urasandesu/CppAnonym/IHeapContent.h>
#endif

namespace Urasandesu { namespace CppAnonym {

    template<
        class HeapManagerType,
        class ApiType
    >        
    class ATL_NO_VTABLE IApiOperable;

}}  // namespace Urasandesu { namespace CppAnonym {

namespace Urasandesu { namespace CppAnonym { namespace MetaData {

    template<
        class HeapManagerType,
        class ApiType
    >        
    class ATL_NO_VTABLE IMetaDataApiOperable : 
        public IApiOperable<HeapManagerType, ApiType>, 
        public IHeapContent<mdToken>
    {
    public:
        IMetaDataApiOperable() { }

        template<class T>
        T *CreateIfNecessary(mdToken token)
        {
            if (GetHeapManager()->Exists<T>(token))
            {
                return GetHeapManager()->Get<T>(token);
            }
            else
            {
                T *pObj = IApiOperable<HeapManagerType, ApiType>::CreatePseudo<T>();
                GetHeapManager()->SetToLast<T>(token);
                return pObj;
            }
        }
        
        mdToken GetToken()
        {
            return GetKey();
        }
        
        void SetToken(mdToken token)
        {
            SetKey(token);
        }
    };

}}}   // namespace Urasandesu { namespace CppAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_CPPANONYM_METADATA_IMETADATAAPIOPERABLE_H