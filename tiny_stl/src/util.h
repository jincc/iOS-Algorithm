//
//  util.h
//  tiny_stl
//
//  Created by junl on 2020/11/10.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef util_hpp
#define util_hpp

#include <stdio.h>
#include <type_traits>
namespace tiny{
    //forward
    template<typename T>
    T&&
    forward(typename std::remove_reference<T>::type& arg) noexcept { //左值引用版本
        return static_cast<T&&>(arg);
    }
    template<typename T>
    T&&
    forward(typename std::remove_reference<T>::type&& arg) noexcept { //右值引用版本
        static_assert(!std::is_lvalue_reference<T>::value, "can not forward an rvalue as an lvalue");
        return static_cast<T&&>(arg);
    }
    
    //https://www.cnblogs.com/5iedu/p/7739692.html
    //该函数的目的是无条件的将参数转换为右值引用，继而用于移动语义
    template<typename T>
    typename std::remove_reference<T>::type&&
    move(T&& arg){ //必须是T&&，可以保留实参的左右值和const属性
        using ReturnType = typename std::remove_reference<T>::type &&;
        return static_cast<ReturnType>(arg);
    }
    
    //利用移动构造实现高性能交换
    template<typename T>
    void
    swap(T &a, T &b){
        auto temp = move(a);
        a =  move(b);
        b = move(temp);
    }
    template<typename ForwardInteractor1, typename ForwardInteractor2>
    ForwardInteractor2
    swap(ForwardInteractor1 first1, ForwardInteractor1 end1, ForwardInteractor2 first2){
        for (; first1 != end1; first1++, first2++) {
            swap(*first1, *first2);
        }
        return first2;
    }
    
    template<typename T, size_t N>
    void
    swap(T(&lhs)[N], T(&rhs)[N]){
        swap(lhs, lhs+N, rhs);
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

#endif /* util_hpp */
