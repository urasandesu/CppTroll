#pragma once
#ifndef GLOBAL_SAFE_DICTIONARY_H
#define GLOBAL_SAFE_DICTIONARY_H

template<
    typename Key, 
    typename Value, 
    typename Hash = boost::hash<Key>, 
    typename Pred = std::equal_to<Key>, 
    typename Alloc = std::allocator<std::pair<Key const, Value>> 
> 
class GlobalSafeDictionary : boost::noncopyable
{
public:
    typedef typename boost::call_traits<Key>::param_type in_key_type;
    typedef typename boost::call_traits<Value>::param_type in_value_type;
    typedef typename boost::call_traits<Value>::reference out_value_type;

    static GlobalSafeDictionary &GetInstance()
    {
        static GlobalSafeDictionary im;
        return im;
    }

    BOOL TryAdd(in_key_type key, in_value_type value)
    {
        m_lock.Lock();
        BOOST_SCOPE_EXIT((&m_lock))
        {
            m_lock.Unlock();
        }
        BOOST_SCOPE_EXIT_END


        if (m_map.find(key) == m_map.end())
        {
            m_map[key] = value;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

    BOOL TryGet(in_key_type key, out_value_type rValue)
    {
        m_lock.Lock();
        BOOST_SCOPE_EXIT((&m_lock))
        {
            m_lock.Unlock();
        }
        BOOST_SCOPE_EXIT_END


        if (m_map.find(key) == m_map.end())
        {
            return FALSE;
        }
        else
        {
            rValue = m_map[key];
            return TRUE;
        }
    }

    BOOL TryRemove(in_key_type key, out_value_type rValue)
    {
        m_lock.Lock();
        BOOST_SCOPE_EXIT((&m_lock))
        {
            m_lock.Unlock();
        }
        BOOST_SCOPE_EXIT_END


        if (m_map.find(key) == m_map.end())
        {
            return FALSE;
        }
        else
        {
            rValue = m_map[key];
            m_map.erase(key);
            return TRUE;
        }
    }

    void Clear()
    {
        m_lock.Lock();
        BOOST_SCOPE_EXIT((&m_lock))
        {
            m_lock.Unlock();
        }
        BOOST_SCOPE_EXIT_END

        
        m_map.clear();
    }

private:
    GlobalSafeDictionary() { }
    ATL::CComAutoCriticalSection m_lock;
    boost::unordered_map<Key, Value, Hash, Pred, Alloc> m_map;
};

#endif  // #ifndef GLOBAL_SAFE_DICTIONARY_H