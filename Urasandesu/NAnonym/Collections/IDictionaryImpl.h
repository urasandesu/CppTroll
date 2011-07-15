#pragma once
#ifndef URASANDESU_NANONYM_COLLECTIONS_IDICTIONARYIMPL_H
#define URASANDESU_NANONYM_COLLECTIONS_IDICTIONARYIMPL_H

#ifndef URASANDESU_NANONYM_COLLECTIONS_ICOLLECTIONIMPL_H
#include "Urasandesu/NAnonym/Collections/ICollectionImpl.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Collections {

    using boost::add_pointer;
    
    template<
        class Base,
        class ComPairObject,
        class FirstCollection,
        class SecondCollection,
        class DictionaryType,
        class ComEnumeratorObject,
        class CopyItemFromDictionary = use_default,
        class CopyDictionaryFromItem = use_default
    >
    class ATL_NO_VTABLE IDictionaryImpl : 
        public ICollectionImpl<
                    Base, 
                    typename add_pointer<typename ComPairObject::interface_type>::type, 
                    DictionaryType, 
                    ComEnumeratorObject, 
                    CopyItemFromDictionary, 
                    CopyDictionaryFromItem
               >
    {
    };

}}}   // namespace Urasandesu { namespace NAnonym { namespace Collections {

#endif  // #ifndef URASANDESU_NANONYM_COLLECTIONS_IDICTIONARYIMPL_H