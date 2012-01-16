#pragma once
#ifndef URASANDESU_CPPANONYM_TRAITS_DISTINCT_H
#define URASANDESU_CPPANONYM_TRAITS_DISTINCT_H

namespace Urasandesu { namespace CppAnonym { namespace Traits {

    template<class Sequence>
    struct Distinct : 
        boost::mpl::fold<Sequence, boost::mpl::set0<>, 
            boost::mpl::insert<boost::mpl::arg<1>, boost::mpl::arg<2> > >
    {
    };

    template<class Sequence>
    struct DistinctBegin : 
        boost::mpl::begin<typename Distinct<Sequence>::type>
    {
    };

    template<class Sequence>
    struct DistinctEnd : 
        boost::mpl::end<typename Distinct<Sequence>::type>
    {
    };

}}}   // namespace Urasandesu { namespace CppAnonym { namespace Traits {

#endif  // #ifndef URASANDESU_CPPANONYM_TRAITS_DISTINCT_H