//
//  forward_test.h
//  tiny_stl
//
//  Created by junl on 2020/11/11.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef forward_test_h
#define forward_test_h

#include <stdio.h>
#include "test.h"

namespace tiny{
namespace test{
namespace forward_test{
struct Test
{
public:
    int* m;
    Test(int i):m(new int(i)){std::cout << "Test()" << std::endl;}
    Test(const Test& t):m(new int(*t.m)) {std::cout << "Test(const Test&)" << std::endl;}
    Test(Test&& t):m(t.m) {
        t.m = nullptr;
        std::cout << "Test(Test&&)" << std::endl;}
    Test& operator=(Test&& t){
        if (&t != this ){
            m = t.m;
            t.m = nullptr;
        }
        std::cout << "Test(Test&&)" << std::endl;
        return *this;
    }
    ~Test(){std::cout << "~Test()" << std::endl;}
};

TEST(forward_test){
#define TEST_IS_RVALUE(val) EXPECT_TRUE(std::is_rvalue_reference<decltype((val))>::value);
    int i = 0;
    int &&ri = i++;//i++为右值
    int &li = ++i;
    int *p = &i;
    int &lp = *p;
    int *&& rp = &i;//取地址表达式是个地址值,估&rp是纯右值
    
    int &&xi1 = std::move(i);//xil是个xvalue将亡右值
    int &&xi2 = static_cast<int &&>(i);//xvalue
    auto&& fn = [](int x){return x * x;};//lambda是个右值
    
    Test t1(1), t2(2);
    swap(t1, t2);
    EXPECT_TRUE(*t1.m == 2);
    EXPECT_TRUE(*t2.m == 1);
    
    //test swap
    int arr1[] = {1,3,5,7};
    int arr2[] = {2, 4, 6,8};
    int arr3[] = {1,3,5,7};
    int arr4[] = {2, 4, 6,8};
    swap(arr1, arr2);
    EXPECT_PTR_RANGE_EQ(arr1, arr4, 4);
    EXPECT_PTR_RANGE_EQ(arr2, arr3, 4);
}
}

}
}

#endif /* forward_test_h */
