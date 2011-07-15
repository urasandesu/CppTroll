#pragma once
#ifndef URASANDESU_NANONYM_CONCEPTS_COMDICTIONARY_H
#define URASANDESU_NANONYM_CONCEPTS_COMDICTIONARY_H

#ifndef URASANDESU_NANONYM_CONCEPTS_COMCOLLECTION_H
#include "Urasandesu/NAnonym/Concepts/ComCollection.h"
#endif

#ifndef URASANDESU_NANONYM_CONCEPTS_COMPAIR_H
#include "Urasandesu/NAnonym/Concepts/ComPair.h"
#endif

namespace Urasandesu { namespace NAnonym { namespace Concepts {

    using boost::add_pointer;
    
    template<class X, class PairType, class FirstType, class SecondType, class FirstCollection, class SecondCollection>
    struct ComDictionary
    {
        BOOST_CONCEPT_ASSERT((ComCollection<X, typename add_pointer<PairType>::type>));
        BOOST_CONCEPT_ASSERT((ComPair<PairType, FirstType, SecondType>));
        BOOST_CONCEPT_ASSERT((ComCollection<FirstCollection, FirstType>));
        BOOST_CONCEPT_ASSERT((ComCollection<SecondCollection, SecondType>));
        
        BOOST_CONCEPT_USAGE(ComDictionary)
        {
            HRESULT hr;
            X* pX;

            // Add
            {
                PairType* pPair;
                hr = pX->Add(pPair);
                
                FirstType* pFirst;
                SecondType* pSecond;
                hr = pX->Add(*pFirst, *pSecond);
            }
            
            // ContainsKey
            {
                FirstType* pFirst;
                VARIANT_BOOL exists;
                hr = pX->ContainsKey(*pFirst, &exists);
            }
            
            // TryGetValue
            {
                FirstType* pFirst;
                SecondType* pSecond;
                VARIANT_BOOL exists;
                hr = pX->TryGetValue(*pFirst, pSecond, &exists);
            }

            // Item
            {
                FirstType* pFirst;
                SecondType* pSecond;
                hr = pX->get_Item(*pFirst, pSecond);
                hr = pX->put_Item(*pFirst, *pSecond);
            }
            
            // Keys
            {
                FirstCollection* pFirstCollection;
                hr = pX->get_Keys(&pFirstCollection);
            }
            
            // Values
            {
                SecondCollection* pSecondCollection;
                hr = pX->get_Values(&pSecondCollection);
            }
        }
    };  // struct ComDictionary

}}}   // namespace Urasandesu { namespace NAnonym { namespace Concepts {

#endif // #ifndef URASANDESU_NANONYM_CONCEPTS_COMDICTIONARY_H