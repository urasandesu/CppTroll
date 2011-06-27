#pragma once
#ifndef INCLUDED_REPLACE_H
#define INCLUDED_REPLACE_H

namespace My
{
    // Gets New if T is Old; otherwise T.    
    template <class T, class Old, class New>
    struct Replace : 
        public eval_if<is_same<T, Old>, identity<New>, identity<T>>
    {
    };

}   // namespace My

#endif  // #ifndef INCLUDED_REPLACE_H