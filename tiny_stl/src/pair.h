//
//  pair.h
//  tiny_stl
//
//  Created by junl on 2020/11/12.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef pair_hpp
#define pair_hpp

#include <stdio.h>
#include <utility>
#include "util.h"
namespace tiny {
    struct __nat
    {
        __nat() = delete;
        __nat(const __nat&) = delete;
        __nat& operator=(const __nat&) = delete;
        ~__nat() = delete;
    };
    /*
     This class couples together a pair of values, which may be of different types (T1 and T2). The individual values can be accessed through its public members first and second.
     */
    template<class T1, class T2>
    class pair{
    public:
        typedef T1 first_type;
        typedef T2 second_type;
        struct _CheckArgs{
            constexpr static bool enabel_assign(){
                return std::is_copy_assignable<first_type>::value &&
                std::is_copy_assignable<second_type>::value;
            }
            constexpr static bool enabel_move_assign(){
                return std::is_move_assignable<first_type>::value &&
                std::is_move_assignable<second_type>::value;
            }
            constexpr static bool enabel_copy_constructible(){
                return std::is_copy_constructible<first_type>::value &&
                std::is_copy_constructible<second_type>::value;
            }
            constexpr static bool enabel_move_constructible(){
                return std::is_move_constructible<first_type>::value &&
                std::is_move_constructible<second_type>::value;
            }
        };
        
        //default constructor
        template <class Ty1 = T1, class Ty2 = T2,
                  typename = typename std::enable_if<
                   std::is_default_constructible<Ty1>::value &&
                   std::is_default_constructible<Ty2>::value, void>::type>
        constexpr pair(): first(), second(){
            
        };
        //initialization
          // implicit constructiable for this type
        template <class U1 = T1, class U2 = T2,
          typename std::enable_if<
          std::is_copy_constructible<U1>::value &&
          std::is_copy_constructible<U2>::value &&
          std::is_convertible<const U1&, T1>::value &&
          std::is_convertible<const U2&, T2>::value, int>::type = 0>
          constexpr pair(const T1& a, const T2& b)
          : first(a), second(b)
        {
        }

        // explicit constructible for this type
        template <class U1 = T1, class U2 = T2,
          typename std::enable_if<
          std::is_copy_constructible<U1>::value &&
          std::is_copy_constructible<U2>::value &&
          (!std::is_convertible<const U1&, T1>::value ||
           !std::is_convertible<const U2&, T2>::value), int>::type = 0>
          explicit constexpr pair(const T1& a, const T2& b)
          : first(a), second(b)
        {
        }
                
        // explicit constructiable for other type
        template <class Other1, class Other2,
          typename std::enable_if<
          std::is_constructible<T1, Other1>::value &&
          std::is_constructible<T2, Other2>::value &&
          (!std::is_convertible<Other1, T1>::value ||
           !std::is_convertible<Other2, T2>::value), int>::type = 0>
          explicit constexpr pair(Other1&& a, Other2&& b)
          : first(tiny::forward<Other1>(a)),
          second(tiny::forward<Other2>(b))
        {
        }
        
        // implicit constructiable for other pair
        template <class Other1, class Other2,
          typename std::enable_if<
          std::is_constructible<T1, const Other1&>::value &&
          std::is_constructible<T2, const Other2&>::value &&
          std::is_convertible<const Other1&, T1>::value &&
          std::is_convertible<const Other2&, T2>::value, int>::type = 0>
          constexpr pair(const pair<Other1, Other2>& other)
          : first(other.first),
          second(other.second)
        {
        }

        // explicit constructiable for other pair
        template <class Other1, class Other2,
          typename std::enable_if<
          std::is_constructible<T1, const Other1&>::value &&
          std::is_constructible<T2, const Other2&>::value &&
          (!std::is_convertible<const Other1&, T1>::value ||
           !std::is_convertible<const Other2&, T2>::value), int>::type = 0>
          explicit constexpr pair(const pair<Other1, Other2>& other)
          : first(other.first),
          second(other.second)
        {
        }
        
        // implicit constructiable for other pair
        template <class Other1, class Other2,
          typename std::enable_if<
          std::is_constructible<T1, Other1>::value &&
          std::is_constructible<T2, Other2>::value &&
          std::is_convertible<Other1, T1>::value &&
          std::is_convertible<Other2, T2>::value, int>::type = 0>
          constexpr pair(pair<Other1, Other2>&& other)
          : first(tiny::forward<Other1>(other.first)),
          second(tiny::forward<Other2>(other.second))
        {
        }

        // explicit constructiable for other pair
        template <class Other1, class Other2,
          typename std::enable_if<
          std::is_constructible<T1, Other1>::value &&
          std::is_constructible<T2, Other2>::value &&
          (!std::is_convertible<Other1, T1>::value ||
           !std::is_convertible<Other2, T2>::value), int>::type = 0>
          explicit constexpr pair(pair<Other1, Other2>&& other)
          : first(tiny::forward<Other1>(other.first)),
          second(tiny::forward<Other2>(other.second))
        {
        }

        
        
        //copy
        pair(typename std::conditional<
             _CheckArgs::enabel_copy_constructible(), pair, __nat>::type const &_p):first(_p.first),second(_p.second) {}
        //move
        pair(typename std::conditional<
             _CheckArgs::enabel_move_constructible(), pair, __nat>::type &&_p):first(tiny::move(_p.first)), second(tiny::move(_p.second)){
            
        }
        pair& operator=(typename std::conditional<
                        _CheckArgs::enabel_assign(), pair, __nat>::type const&_p){
            first = _p.first;
            second = _p.second;
            return *this;
        };
        
        pair& operator=(typename std::conditional<
                        _CheckArgs::enabel_move_assign(), pair, __nat>::type && _p){
            first = tiny::forward<first_type>(_p.first);
            second = tiny::forward<second_type>(_p.second);
            return *this;
        };
        void swap(pair &p){
            if (this != &p){
                tiny::swap(first, p.first);
                tiny::swap(second, p.second);
            }
        }
        //ivar
        first_type first;
        second_type second;
    };
    template<typename T1, typename T2>
    void swap(tiny::pair<T1, T2> &lhs, tiny::pair<T1, T2> &rhs){
        lhs.swap(rhs);
    }
    template<typename T1, typename T2>
    bool operator==(const tiny::pair<T1, T2> &lhs, const tiny::pair<T1, T2> &rhs){
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
    template<typename T1, typename T2>
    bool operator!=(const tiny::pair<T1, T2> &lhs, const tiny::pair<T1, T2> &rhs){
        return !(lhs == rhs);
    }
    //Where the types V1 and V2 are the decay equivalents of T1 and T2, respectively (except for reference_wrapper types, for which the corresponding reference type is used instead).
    template<class T1, class T2>
    inline tiny::pair<typename std::decay<T1>::type, typename std::decay<T2>::type>
    make_pair(T1 &&x, T2 &&y){
        return pair<typename std::decay<T1>::type,
                    typename std::decay<T2>::type>(tiny::forward<T1>(x), tiny::forward<T2>(y));
    }
}

#endif /* pair_hpp */
