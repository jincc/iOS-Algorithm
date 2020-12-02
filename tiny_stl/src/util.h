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
#include "iterator.h"
#include <sstream>
#include <string>
namespace tiny{
    //log
    //用来终止可变参数模板的非递归版本，打印最后一个元素
    //此函数必须在可变参数模板之前定义，否则会无限递归
    template<typename T>
    std::ostream &print(std::ostream &os, const T &t){
        return os << t;
    }
    
    //可变参数版本, 每次调用，包中的第一个实参被移除，称为t的实参，然后用剩余实参继续递归
    template<typename T, typename... Args>
    std::ostream &print(std::ostream &os, const T &t, const Args&...rst){
        os << t << " ";//打印第一个实参
        return print(os, rst...);//递归调用, 打印其他实参
    }
    
    template<class T>
    std::string debug_rep(const T &t){
        std::ostringstream ret;
        ret << t;
        return ret.str();
    }
    template<class T>
    std::string debug_rep(T *t){
        std::ostringstream ret;
        if (t) {
            ret << "pointer: " << t << " " << debug_rep(*t);
        }else{
            ret << "pointer: " << t << " " << "null pointer";
        }
        return ret.str();
    }
    std::string debug_rep(const char *t){
        return t;
    }
    template<typename...Args>
    std::ostream& errorMsg(std::ostream &os, const Args&... args){
        return print(os, debug_rep(args)...);
    }
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
    move(T&& arg) noexcept{ //必须是T&&，可以保留实参的左右值和const属性
        using ReturnType = typename std::remove_reference<T>::type &&;
        return static_cast<ReturnType>(arg);
    }
    
    //利用移动构造实现高性能交换
    template<typename T>
    void
    swap(T &a, T &b){
        auto temp = tiny::move(a);
        a = tiny::move(b);
        b = tiny::move(temp);
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
}

#endif /* util_hpp */
