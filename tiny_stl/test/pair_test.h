//
//  pair_test.h
//  tiny_stl
//
//  Created by junl on 2020/11/12.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef pair_test_hpp
#define pair_test_hpp

#include <stdio.h>
#include "test.h"
#include "pair.h"
#include <utility>
#include <string>
#include <type_traits>
namespace tiny {
    namespace test{
    
    template <class T>
    typename std::enable_if<std::is_integral<T>::value, bool>::type
    is_odd(T i){
        return bool(i % 2);
    }
    
    template<class T,
             class = typename std::enable_if<std::is_integral<T>::value>::type>
    bool is_even(T i){
        return !bool(i % 2);
    }
    
    class Deleted{
//        Deleted() = delete;
    };
    pair<std::string, double> getPair(){
        return pair<std::string, double>("123", 34.5);
    }
    TEST(pair){
        std::string s1 = "123";
        double v = 2.570;
        pair<std::string, double> product(getPair());
        pair <std::string,double> product1;                     // default constructor
        pair <std::string,double> product2 ("tomatoes",2.30);   // value init
        pair <std::string,double> product3 (product2);          // copy constructor
        pair <std::string,double> product4 = tiny::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)
        product2.first = "shoes";                  // the type of first is string
        product2.second = 39.90;                   // the type of second is double
        std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
        std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
        std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
        std::cout << "The price of " << product4.first << " is $" << product4.second << '\n';
        
        EXPECT_EQ(is_odd(1), !is_even(1));
        EXPECT_TRUE(product2 == product2);
        EXPECT_TRUE(product2 != product);
        pair<Deleted, Deleted> a;
        product = product1;
        product = tiny::move(product1);
    }
    }
}
#endif /* pair_test_hpp */
