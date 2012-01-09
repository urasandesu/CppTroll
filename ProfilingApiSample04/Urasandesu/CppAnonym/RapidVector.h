#pragma once
#ifndef URASANDESU_CPPANONYM_RAPIDVECTOR_H
#define URASANDESU_CPPANONYM_RAPIDVECTOR_H

#ifndef URASANDESU_CPPANONYM_TRAITS_HASCONST_H
#include <Urasandesu/CppAnonym/Traits/HasConst.h>
#endif

namespace Urasandesu { namespace CppAnonym {

    template<class T, class Alloc, DWORD RAPID_SIZE>
    class RapidVector;

    namespace Detail {

        template<
            class Value, 
            class T, 
            class Alloc = std::allocator<T>, 
            DWORD RAPID_SIZE = 512
        >
        class RapidVectorIterator : 
            public boost::iterator_facade<
                RapidVectorIterator<Value, T, Alloc, RAPID_SIZE>, 
                Value, 
                boost::random_access_traversal_tag>
        {
        private:
            typedef typename boost::mpl::eval_if<
                Urasandesu::CppAnonym::Traits::HasConst<Value>, 
                boost::mpl::identity<typename std::vector<T, Alloc>::const_iterator>, 
                boost::mpl::identity<typename std::vector<T, Alloc>::iterator> >::type iterator_;
        public:
            RapidVectorIterator(RapidVector<T, Alloc, RAPID_SIZE> *pThis, bool isEnd = false) : 
                m_pThis(pThis), 
                m_pBuf(NULL)
            {
                if (m_pThis->RunAsRapid())
                {
                    m_pBuf = !isEnd ? 
                                reinterpret_cast<T *>(m_pThis->m_pRapidBuf) : 
                                reinterpret_cast<T *>(m_pThis->m_pRapidBuf) + m_pThis->m_size;
                }
                else
                {
                    m_i = !isEnd ? m_pThis->m_pVec->begin() : m_pThis->m_pVec->end();
                }
            }
        
        private:
            friend class boost::iterator_core_access;

            void increment() 
            { 
                if (m_pThis->RunAsRapid())
                {
                    ++m_pBuf;
                }
                else
                {
                    ++m_i;
                }
            }

            void advance(difference_type n) 
            { 
                if (m_pThis->RunAsRapid())
                {
                    m_pBuf += n;
                }
                else
                {
                    m_i += n;
                }
            }

            bool equal(RapidVectorIterator<Value, T, Alloc, RAPID_SIZE> const& other) const
            {
                if (m_pThis->RunAsRapid())
                {
                    return m_pBuf == other.m_pBuf;
                }
                else
                {
                    return m_i == other.m_i;
                }
            }

            Value &dereference() const 
            { 
                return m_pThis->m_size <= RAPID_SIZE ? *m_pBuf : *m_i; 
            }

            RapidVector<T, Alloc, RAPID_SIZE> *m_pThis;
            T *m_pBuf;
            iterator_ m_i;
        };
        
    }   // namespace Detail

    template<class T, class Alloc = std::allocator<T>, DWORD RAPID_SIZE = 512>
    class RapidVector
    {
    public:
        typedef RapidVector<T, Alloc, RAPID_SIZE> type;
	    typedef typename std::vector<T, Alloc>::allocator_type allocator_type;
	    typedef Detail::RapidVectorIterator<T const, T, Alloc, RAPID_SIZE> const_iterator;
	    typedef typename std::vector<T, Alloc>::const_pointer const_pointer;
	    typedef typename std::vector<T, Alloc>::const_reference const_reference;
	    typedef typename std::vector<T, Alloc>::const_reverse_iterator const_reverse_iterator;
	    typedef typename std::vector<T, Alloc>::difference_type difference_type;
	    typedef Detail::RapidVectorIterator<T, T, Alloc, RAPID_SIZE> iterator;
	    typedef typename std::vector<T, Alloc>::pointer pointer;
	    typedef typename std::vector<T, Alloc>::reference reference;
	    typedef typename std::vector<T, Alloc>::reverse_iterator reverse_iterator;
	    typedef typename std::vector<T, Alloc>::size_type size_type;
	    typedef typename std::vector<T, Alloc>::value_type value_type;

        RapidVector() : m_size(0), m_maxSize(RAPID_SIZE), m_pVec(NULL) { }
        ~RapidVector() { if (m_pVec == NULL) delete m_pVec; }
        
        void push_back(typename boost::call_traits<T>::param_type val)
        {
            if (m_size < RAPID_SIZE)
            {
                reinterpret_cast<T *>(m_pRapidBuf)[m_size++] = val;
                return;
            }
            
            if (m_size == RAPID_SIZE)
            {
                m_pVec = new std::vector<T, Alloc>(RAPID_SIZE);
                m_pVec->assign(reinterpret_cast<T *>(m_pRapidBuf), reinterpret_cast<T *>(m_pRapidBuf) + RAPID_SIZE);
                ++m_size;
            }
            m_pVec->push_back(val);
            m_maxSize = m_pVec->max_size();
        }

        inline const_reference operator[](size_type pos) const
        {
            return RunAsRapid() ? reinterpret_cast<T *>(const_cast<PUINT64>(m_pRapidBuf))[pos] : (*m_pVec)[pos];
        }

        inline reference operator[](size_type pos)
        {
            return RunAsRapid() ? reinterpret_cast<T *>(m_pRapidBuf)[pos] : (*m_pVec)[pos];
        }

	    inline iterator begin()
	    {
	        return iterator(this);
	    }

        inline const_iterator begin() const
        {
            return const_iterator(this);
        }

        inline iterator end()
        {
            return iterator(this, true);
        }

        inline const_iterator end() const
        {
            return const_iterator(this, true);
        }

        inline size_type size() const
        {
            return RunAsRapid() ? m_size : m_pVec->size();
        }

        inline size_type max_size() const
        {
            return RunAsRapid() ? RAPID_SIZE : m_pVec->max_size();
        }

        void resize(size_type newSize)
        {
            if (newSize <= RAPID_SIZE)
            {
                m_size = newSize;
                return;
            }
            
            if (m_size <= RAPID_SIZE && RAPID_SIZE < newSize)
            {
                m_pVec = new std::vector<T, Alloc>(newSize);
                m_pVec->assign(reinterpret_cast<T *>(m_pRapidBuf), reinterpret_cast<T *>(m_pRapidBuf) + RAPID_SIZE);
                m_size = newSize;
            }
            m_pVec->resize(newSize);
            m_maxSize = m_pVec->max_size();
        }

        inline bool RunAsRapid() const
        {
            return m_size <= RAPID_SIZE;
        }
    
    private:
        template<class Value, class T, class Alloc, DWORD RAPID_SIZE>
	    friend class Detail::RapidVectorIterator;
	    
        std::vector<T, Alloc> *m_pVec;
        SIZE_T m_size;
        SIZE_T m_maxSize;
        UINT64 m_pRapidBuf[(RAPID_SIZE * sizeof(T) + sizeof(UINT64) - 1) / sizeof(UINT64)];
    };

}}  // namespace Urasandesu { namespace CppAnonym {

#endif  // URASANDESU_CPPANONYM_RAPIDVECTOR_H