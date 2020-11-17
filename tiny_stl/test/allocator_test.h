//
//  allocator_test.h
//  tiny_stl
//
//  Created by junl on 2020/11/10.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef allocator_test_h
#define allocator_test_h

#include <stdio.h>
#include <memory>
#include <iostream>
#include <string>
#include "test.h"
#include "allocator.h"
#include "util.h"
namespace tiny{
namespace test{
    class Object{
    public:
        Object(const int tag):tag(tag) {std::cout << "Object()" << std::endl;}
        ~Object(){std::cout << "~Object()" << std::endl;}
    private:
        int tag;
    };
    int get(){
        return 1;
    }
    void overloaded (const int& x) {std::cout << "[lvalue]";}
    void overloaded (int&& x) {std::cout << "[rvalue]";}

    // function template taking rvalue reference to deduced type:
    template <class T> void fn (T&& x) {
      overloaded (x);                   // always an lvalue
      overloaded (std::forward<T>(x));  // rvalue if argument is rvalue
    }
#define USE_CUSTOM_VERSION
    TEST(allocator){
        typedef Object class_name;
#ifdef USE_CUSTOM_VERSION
        allocator<class_name> allocator;
#else
        std::allocator<class_name> allocator;
#endif
        size_t n = 3;
        class_name *basePtr, *obj;
        basePtr = obj = allocator.allocate(n);
        for (size_t i =0; i < n; i++) {
            std::cout << allocator.address(*obj) << std::endl;
            allocator.construct(obj++, get());
        }
        obj = basePtr;
        for (size_t i = 0; i < n; i++) {
            allocator.destroy(obj++);
        }
        allocator.deallocate(basePtr, n);
        
        
    }

}
}
#endif /* allocator_test_h */
