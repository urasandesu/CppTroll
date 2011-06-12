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

namespace My
{
    template <
        class Base, 
        class ItemType, 
        class RangeType, 
        class CopyItemFromRange = GenericCopy<
                                    ItemType, 
                                    typename WithoutAdapt<
                                        typename range_value<RangeType>::type
                                    >::type
                                  >,
        class RangeAddresser = AddressExtractor<
                                    typename WithoutAdapt<
                                        typename range_value<RangeType>::type
                                    >::type
                               >,
        class ThreadModel = CComObjectThreadModel
    >
    class ATL_NO_VTABLE CComEnumerator :
        public IEnumeratorImpl<Base, ItemType, RangeType, CopyItemFromRange, RangeAddresser, ThreadModel>,
        public CComObjectRootEx<ThreadModel>
    {
    public:
        typedef CComEnumerator<Base, ItemType, RangeType, CopyItemFromRange, RangeAddresser, ThreadModel> type;
        typedef IEnumeratorImpl<Base, ItemType, RangeType, CopyItemFromRange, RangeAddresser, ThreadModel> base_type;
        typedef typename base_type::interface_type interface_type;

        BEGIN_COM_MAP(type)
            COM_INTERFACE_ENTRY_IID(__uuidof(Base), base_type)
        END_COM_MAP()
    };  // class ATL_NO_VTABLE CComEnumerator

}   // namespace My

#endif  // #ifndef INCLUDED_CCOMENUMERATOR_H