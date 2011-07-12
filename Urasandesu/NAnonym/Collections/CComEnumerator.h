#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMENUMERATOR_H
#define URASANDESU_NANONYM_COLLECTIONS_CCOMENUMERATOR_H

#ifndef URASANDESU_NANONYM_UTILITIES_GENERICCOPY_H
#include "Urasandesu/NAnonym/Utilities/GenericCopy.h"
#endif

#ifndef URASANDESU_NANONYM_TRAITS_WITHOUTADAPT_H
#include "Urasandesu/NAnonym/Traits/WithoutAdapt.h"
#endif

#ifndef URASANDESU_NANONYM_COLLECTIONS_IENUMERATORIMPL_H
#include "Urasandesu/NAnonym/Collections/IEnumeratorImpl.h"
#endif

#ifndef URASANDESU_NANONYM_TRAITS_REPLACE_H
#include "Urasandesu/NAnonym/Traits/Replace.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Collections {

    template <
        class Base, 
        class ItemType, 
        class RangeType, 
        class CopyItemFromRange = use_default,
        class ThreadModel = use_default,
        template<class> class CComObject_ = use_default1
    >
    class ATL_NO_VTABLE CComEnumerator :
        public IEnumeratorImpl<Base, ItemType, RangeType, CopyItemFromRange>,
        public CComObjectRootEx<typename Replace<ThreadModel, use_default, CComObjectThreadModel>::type>
    {
    public:
        typedef IEnumeratorImpl<Base, ItemType, RangeType, CopyItemFromRange> base_type;
        typedef CComEnumerator<Base, ItemType, RangeType, CopyItemFromRange, ThreadModel, CComObject_> type;
        typedef typename Replace<CComObject_<type>, use_default1<type>, CComObject<type>>::type com_object_type;
        typedef typename base_type::interface_type interface_type;

        BEGIN_COM_MAP(type)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), base_type)
        END_COM_MAP()
        
        STDMETHOD(Clone)(Base** ppVal)
        {
            return base_type::Clone<com_object_type>(ppVal);
        }
    };  // class ATL_NO_VTABLE CComEnumerator

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_CCOMENUMERATOR_H