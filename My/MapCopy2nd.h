#pragma once
#ifndef INCLUDED_MAPCOPY2ND_H
#define INCLUDED_MAPCOPY2ND_H

namespace My
{
    template<class MapType, class DestinationType = MapType::mapped_type>
    struct MapCopy2nd
    {
        typedef MapType map_type;
        typedef typename map_type::mapped_type map_second_type;

        typedef DestinationType destination_type;
        typedef typename map_type::value_type source_type;
        
        static void init(destination_type* p)
        {
            GenericCopy<destination_type, map_second_type>::init(p);
        }
        static void destroy(destination_type* p)
        {
            GenericCopy<destination_type, map_second_type>::destroy(p);
        }
        static HRESULT copy(destination_type* pTo, const source_type* pFrom)
        {
            return GenericCopy<destination_type, map_second_type>::copy(pTo, &(pFrom->second));
        }

    }; // struct MapCopy2nd
}   // namespace My

#endif  // #ifndef INCLUDED_MAPCOPY2ND_H