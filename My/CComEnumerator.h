#pragma once
#ifndef INCLUDED_CCOMENUMERATOR_H
#define INCLUDED_CCOMENUMERATOR_H

#ifndef INCLUDED_GENERICCOPY_H
#include "GenericCopy.h"
#endif

#ifndef INCLUDED_WITHOUTADAPT_H
#include "WithoutAdapt.h"
#endif

#ifndef INCLUDED_ADDRESSEXTRACTOR_H
#include "AddressExtractor.h"
#endif

#ifndef INCLUDED_IENUMERATORIMPL_H
#include "IEnumeratorImpl.h"
#endif

#ifndef INCLUDED_REPLACE_H
#include "Replace.h"
#endif

namespace My
{
    template <
        class Base, 
        class ItemType, 
        class RangeType, 
        class CopyItemFromRange = use_default,
        class RangeAddresser = use_default,
        class ThreadModel = use_default,
        template<class> class CComObject_ = use_default1
    >
    class ATL_NO_VTABLE CComEnumerator :
        public IEnumeratorImpl<Base, ItemType, RangeType, CopyItemFromRange, RangeAddresser>,
        public CComObjectRootEx<typename Replace<ThreadModel, use_default, CComObjectThreadModel>::type>
    {
    public:
        typedef IEnumeratorImpl<Base, ItemType, RangeType, CopyItemFromRange, RangeAddresser> base_type;
        typedef CComEnumerator<Base, ItemType, RangeType, CopyItemFromRange, RangeAddresser, ThreadModel, CComObject_> type;
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

}   // namespace My

#endif  // #ifndef INCLUDED_CCOMENUMERATOR_H