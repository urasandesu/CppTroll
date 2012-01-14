#pragma once
#ifndef URASANDESU_CPPANONYM_TRAITS_UNIQUE_H
#define URASANDESU_CPPANONYM_TRAITS_UNIQUE_H

namespace Urasandesu { namespace CppAnonym { namespace Traits {

    template<class Sequence>
    struct Unique : 
        boost::mpl::fold<Sequence, boost::mpl::set0<>, 
            boost::mpl::insert<boost::mpl::arg<1>, boost::mpl::arg<2> > >
    {
    };

    template<class Sequence>
    struct UniqueBegin : 
        boost::mpl::begin<typename Unique<Sequence>::type>
    {
    };

    template<class Sequence>
    struct UniqueEnd : 
        boost::mpl::end<typename Unique<Sequence>::type>
    {
    };

}}}   // namespace Urasandesu { namespace CppAnonym { namespace Traits {

#endif  // #ifndef URASANDESU_CPPANONYM_TRAITS_UNIQUE_H