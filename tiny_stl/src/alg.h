//
//  alg.h
//  tiny_stl
//
//  Created by junl on 2020/11/19.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef alg_h
#define alg_h
#include "iterator.h"
#include "allocator.h"
namespace tiny{
    template <class _ForwardIterator, class _Size, class _Tp>
    _ForwardIterator
    uninitialized_fill_n(_ForwardIterator __f, _Size __n, const _Tp& __x)
    {
        typedef typename tiny::iterator_traits<_ForwardIterator>::value_type value_type;
#ifndef _LIBCPP_NO_EXCEPTIONS
        _ForwardIterator __s = __f;
        try
        {
#endif
            for (; __n > 0; ++__f, (void) --__n)
                ::new (static_cast<void*>(_VSTD::addressof(*__f))) value_type(__x);
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            for (; __s != __f; ++__s)
                __s->~value_type();
            throw;
        }
#endif
        return __f;
    }
    
    template <class _ForwardIterator, class _Tp>
    void
    uninitialized_fill(_ForwardIterator __f, _ForwardIterator __l, const _Tp& __x)
    {
        typedef typename tiny::iterator_traits<_ForwardIterator>::value_type value_type;
#ifndef _LIBCPP_NO_EXCEPTIONS
        _ForwardIterator __s = __f;
        try
        {
#endif
            for (; __f != __l; ++__f)
                ::new (static_cast<void*>(_VSTD::addressof(*__f))) value_type(__x);
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            for (; __s != __f; ++__s)
                __s->~value_type();
            throw;
        }
#endif
    }
    template <class _InputIterator, class _ForwardIterator>
    _ForwardIterator
    uninitialized_copy(_InputIterator __f, _InputIterator __l, _ForwardIterator __r)
    {
        typedef typename tiny::iterator_traits<_ForwardIterator>::value_type value_type;
    #ifndef _LIBCPP_NO_EXCEPTIONS
        _ForwardIterator __s = __r;
        try
        {
    #endif
            for (; __f != __l; ++__f, (void) ++__r)
                ::new (static_cast<void*>(_VSTD::addressof(*__r))) value_type(*__f);
    #ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            for (; __s != __r; ++__s)
                __s->~value_type();
            throw;
        }
    #endif
        return __r;
    }

    template<class T>
    void uninitialized_destory(const T* first, const T* last){
        for (; first != last; first++) {
            tiny::destroy(const_cast<T*>(first));
        }
    }
    template <class _Compare, class _InputIterator1, class _InputIterator2>
    bool
    lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                            _InputIterator2 __first2, _InputIterator2 __last2, _Compare __comp)
    {
        for (; __first2 != __last2; ++__first1, (void) ++__first2)
        {
            if (__first1 == __last1 || __comp(*__first1, *__first2))
                return true;
            if (__comp(*__first2, *__first1))
                return false;
        }
        return false;
    }
    
    template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
    inline
    bool
    equal(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _BinaryPredicate __pred)
    {
        for (; __first1 != __last1; ++__first1, (void) ++__first2)
            if (!__pred(*__first1, *__first2))
                return false;
        return true;
    }
}
#endif /* alg_h */
