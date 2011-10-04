#pragma once
#ifndef URASANDESU_NANONYM_METADATA_TYPE_H
#define URASANDESU_NANONYM_METADATA_TYPE_H

#ifndef URASANDESU_NANONYM_METADATA_IMETADATAOPERABLE_H
#include "Urasandesu/NAnonym/MetaData/IMetaDataOperable.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_ITOKENIZABLE_H
#include "Urasandesu/NAnonym/MetaData/ITokenizable.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTEENUMERATOR_H
#include "Urasandesu/NAnonym/MetaData/CustomAttributeEnumerator.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_CUSTOMATTRIBUTE_H
#include "Urasandesu/NAnonym/MetaData/CustomAttribute.h"
#endif

#ifndef URASANDESU_NANONYM_METADATA_METHODENUMERATOR_H
#include "Urasandesu/NAnonym/MetaData/MethodEnumerator.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace MetaData {

    template<class MetaDataApiType = boost::use_default>
    class Type : public IMetaDataOperable<MetaDataApiType>, public ITokenizable
    {
    public:
        typedef CustomAttributeEnumerator<Type<MetaDataApiType>, MetaDataApiType> custom_attribute_enumerator_type;
        typedef CustomAttribute<Type<MetaDataApiType>, MetaDataApiType> custom_attribute_type;

        custom_attribute_enumerator_type *EnumerateCustomAttribute()
        {
            HRESULT hr = E_FAIL;
            custom_attribute_enumerator_type *pCAEnum = NULL;
            
            hr = m_pRuntime->GetHeap<custom_attribute_enumerator_type>()->New(&pCAEnum);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            pCAEnum->Init(m_pRuntime, m_pApi);
            pCAEnum->Target = this;
                        
            return pCAEnum;
        }
        
        MethodEnumerator<MetaDataApiType> *EnumerateMethod()
        {
            HRESULT hr = E_FAIL;
            MethodEnumerator<MetaDataApiType> *pMethodEnum = NULL;
            
            hr = m_pRuntime->GetHeap<MethodEnumerator<MetaDataApiType>>()->New(&pMethodEnum);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(Urasandesu::NAnonym::NAnonymCOMException(hr));

            pMethodEnum->Init(m_pRuntime, m_pApi);
            pMethodEnum->DeclaringType = this;
                        
            return pMethodEnum;
        }
        
    };


}}}   // namespace Urasandesu { namespace NAnonym { namespace MetaData {

#endif  // #ifndef URASANDESU_NANONYM_METADATA_TYPE_H