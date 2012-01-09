﻿#pragma once
#ifndef URASANDESU_CPPANONYM_PROFILING_IPROFILINGAPIOPERABLE_H
#define URASANDESU_CPPANONYM_PROFILING_IPROFILINGAPIOPERABLE_H

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

namespace Urasandesu { namespace CppAnonym { namespace Profiling {

    template<
        class HeapManagerType,
        class ApiType
    >        
    class ATL_NO_VTABLE IProfilingApiOperable : 
        public IApiOperable<HeapManagerType, ApiType>, 
        public IHeapContent<UINT_PTR>
    {
    public:
        IProfilingApiOperable() { }

        template<class T>
        T *CreateIfNecessary(UINT_PTR id)
        {
            if (GetHeapManager()->Exists<T>(id))
            {
                return GetHeapManager()->Get<T>(id);
            }
            else
            {
                T *pObj = IApiOperable<HeapManagerType, ApiType>::CreatePseudo<T>();
                GetHeapManager()->SetToLast<T>(id);
                return pObj;
            }
        }
        
        UINT_PTR GetID()
        {
            return GetKey();
        }
        
        void SetID(UINT_PTR id)
        {
            SetKey(id);
        }
    };
        
}}}  // namespace Urasandesu { namespace CppAnonym { namespace Profiling {

#endif  // URASANDESU_CPPANONYM_PROFILING_IPROFILINGAPIOPERABLE_H