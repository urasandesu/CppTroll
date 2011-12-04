#pragma once
#ifndef URASANDESU_CPPANONYM_IAPIOPERABLE_H
#define URASANDESU_CPPANONYM_IAPIOPERABLE_H

namespace Urasandesu { namespace CppAnonym {

    template<
        class HeapManagerType,
        class ApiType
    >        
    class ATL_NO_VTABLE IApiOperable
    {
    public:
        typedef HeapManagerType heap_manager_type;
        typedef ApiType api_type;
         
        IApiOperable() :
            m_pHeapManager(NULL),
            m_pApi(NULL)
        { }
        
        void Init(HeapManagerType *pHeapManager, ApiType *pApi)
        {
            m_pHeapManager = pHeapManager;
            m_pApi = pApi;
        }

        template<class T>
        T *CreatePseudo()
        {
            T *pObj = m_pHeapManager->NewPseudo<T>();
            pObj->Init(m_pHeapManager, m_pApi);
            return pObj;
        }

        HeapManagerType *GetHeapManager()
        {
            return m_pHeapManager;
        }

        ApiType *GetApi()
        {
            return m_pApi;
        }
    private:
        HeapManagerType *m_pHeapManager;
        ApiType *m_pApi;
    };
    
}}  // namespace Urasandesu { namespace CppAnonym {

#endif  // URASANDESU_CPPANONYM_IAPIOPERABLE_H