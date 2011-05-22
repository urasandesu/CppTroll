#pragma once
#include "Concepts.h"
#include "ComUtilities.h"

namespace My
{
    template<
        class Base,
        class EnumType, 
        class RangeType
    >
    class ATL_NO_VTABLE IEnumerableImpl : 
        public Base
    {
        BOOST_CONCEPT_ASSERT((ComEnumerable<Base>));

    public:
        STDMETHOD(get__NewEnum)(IUnknown** ppVal)
        {
            return My::CreateRangeEnumerator<EnumType>(ppVal, this, m_coll);
        }

        RangeType m_coll;
    };  // class ATL_NO_VTABLE IEnumerableImpl

    template<
        class Base, 
        class EnumType, 
        class RangeType,
        const GUID* plibid = &CAtlModule::m_libid,
        WORD wMajor = 1,
        WORD wMinor = 0, 
        class tihclass = CComTypeInfoHolder,
        class ThreadModel = CComObjectThreadModel
    >
    class ATL_NO_VTABLE CComEnumerable :
        public CComObjectRootEx<ThreadModel>,
        public IDispatchImpl<IEnumerableImpl<Base, EnumType, RangeType>, &__uuidof(Base), plibid, wMajor, wMinor, tihclass>
    {
    public:
        typedef CComEnumerable<Base, EnumType, RangeType, plibid, wMajor, wMinor, tihclass, ThreadModel> _CComEnumerable;
        typedef IEnumerableImpl<Base, EnumType, RangeType> _CComEnumerableBase;
        BEGIN_COM_MAP(_CComEnumerable)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), _CComEnumerableBase)
            COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComEnumerable

    //template<
    //    class Base,
    //    class CollectionType,
    //    class ItemType 
    //>
    //class ATL_NO_VTABLE ICollectionImpl : public Base
    //{
    //public:
    //    STDMETHOD(Add)(ItemType newVal)
    //    {
    //        return S_OK;
    //    }
    //};

}   // namespace My