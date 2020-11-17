//
//  vector_test.h
//  tiny_stl
//
//  Created by junl on 2020/11/13.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef vector_test_h
#define vector_test_h

#include <iostream>
#include "test.h"
#include <vector>
#include "vector.h"
namespace tiny{
namespace test{
namespace vector_test{
struct A { };
struct B { B(B&&){} };
struct C { C(C&&) noexcept {} };

struct Object{
    int val;
    std::string name;
    Object(int val, const std::string &name):val(val),name(name){
        std::cout << "Object(int val, const std::string &name)" << std::endl;
    }
    Object() = default;
};
}

TEST(vector){
    using A = vector_test::A;
    using B = vector_test::B;
    using C = vector_test::C;
    std::cout << std::boolalpha;
    std::cout << "is_nothrow_move_constructible:" << std::endl;
    std::cout << "int: " << std::is_nothrow_move_constructible<int>::value << std::endl;//true
    std::cout << "A: " << std::is_nothrow_move_constructible<A>::value << std::endl;//true
    std::cout << "B: " << std::is_nothrow_move_constructible<B>::value << std::endl;//false
    std::cout << "C: " << std::is_nothrow_move_constructible<C>::value << std::endl;//true
    
    typedef  vector_test::Object Object;
#if 0
    typedef std::vector<int> vector;
    typedef std::vector<Object> ovector;
#else
    typedef tiny::vector<int> vector;
    typedef tiny::vector<Object> ovector;
#endif
     vector first;                                // empty vector of ints
     size_t n = 4;
     int val = 100;
     vector second (n,val);                       // four ints with value 100
     vector third (first.begin(),first.end());  // iterating through second
     vector fourth (third);                       // a copy of third
    
    typedef vector::iterator _InputIterator;
    
    EXPECT_TRUE(tiny::is_iterator<int*>::value);
    
     // the iterator constructor can also be used to construct from arrays:
     int myints[] = {16,2,77,29};
     vector fifth (myints, myints + sizeof(myints) / sizeof(int) );

     std::cout << "The contents of fifth are:";//16 2 77 29
     for (vector::iterator it = fifth.begin(); it != fifth.end(); ++it)
       std::cout << ' ' << *it;
     std::cout << '\n';

    vector::reverse_iterator rit = fifth.rbegin();
    for (int i = 0; rit!= fifth.rend(); ++rit)
      *rit = ++i;

    std::cout << "myvector contains:"; //4 3 2 1
    for (vector::iterator it = fifth.begin(); it != fifth.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
    //测试赋值运算符
    vector foo (3,0);
    vector bar (5,0);
    
    bar = foo;
    foo = vector();
    EXPECT_EQ(0, foo.size());
    EXPECT_EQ(3, bar.size());
    
    

    vector myvector;
    // set some initial content:
    for (int i=1;i<10;i++) myvector.push_back(i);
    myvector.resize(5);
    myvector.resize(8,100);
    myvector.resize(12);

    std::cout << "myvector contains:";//myvector contains: 1 2 3 4 5 100 100 100 0 0 0 0
    for (int i=0;i<myvector.size();i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';


    vector::size_type sz;

    foo.clear();
    sz = foo.capacity();
    std::cout << "making foo grow:\n";
    for (int i=0; i<100; ++i) {
      foo.push_back(i);
      if (sz!=foo.capacity()) {
        sz = foo.capacity();
        std::cout << "capacity changed: " << sz << '\n';
      }
    }

    bar.clear();
    sz = bar.capacity();
    bar.reserve(100);   // this is the only difference with foo above
    std::cout << "making bar grow:\n";
    for (int i=0; i<100; ++i) {
      bar.push_back(i);
      if (sz!=bar.capacity()) {
        sz = bar.capacity();
        std::cout << "capacity changed: " << sz << '\n';
      }
    }
    /*
     making foo grow:
     capacity changed: 1
     capacity changed: 2
     capacity changed: 4
     capacity changed: 8
     capacity changed: 16
     capacity changed: 32
     capacity changed: 64
     capacity changed: 128
     making bar grow:
     capacity changed: 100
     */
    {
        vector myvector (100);
        EXPECT_EQ(100, myvector.capacity());

        myvector.resize(10);
        EXPECT_EQ(100, myvector.capacity());

        myvector.shrink_to_fit();
        EXPECT_EQ(10, myvector.capacity());
    }

    {
        vector myvector (10);   // 10 zero-initialized elements

        vector::size_type sz = myvector.size();

        // assign some values:
        for (unsigned i=0; i<sz; i++) myvector[i]=i;

        // reverse vector using operator[]:
        for (unsigned i=0; i<sz/2; i++)
        {
          int temp;
          temp = myvector[sz-1-i];
          myvector[sz-1-i]=myvector[i];
          myvector[i]=temp;
        }
        vector result = {9,8,7,6,5,4,3,2,1,0};
        EXPECT_PTR_RANGE_EQ(myvector.begin(), result.begin(), 10);
    }
    {
        vector myvector (10);   // 10 zero-initialized ints

        // assign some values:
        for (unsigned i=0; i<myvector.size(); i++)
          myvector.at(i)=i;

        for (unsigned i=0; i<myvector.size(); i++)
            EXPECT_EQ(i, myvector.at(i));
    }

    {
        vector myvector;

        myvector.push_back(78);
        myvector.push_back(16);

        // now front equals 78, and back 16
        myvector.front() -= myvector.back();
        EXPECT_EQ(62, myvector.front());
        myvector.back() += 10;
        EXPECT_EQ(26, myvector.back());
    }

    {
        vector myvector (5);
        vector result{10, 20, 0, 100, 0};
        int* p = myvector.data();
        *p = 10;
        ++p;
        *p = 20;
        p[2] = 100;
        EXPECT_PTR_RANGE_EQ(myvector.begin(), result.begin(), 5);
    }
    {
        vector first;
        vector second;
        vector third;

        first.assign (7,100);             // 7 ints with a value of 100

        vector::iterator it;
        it=first.begin()+1;

        second.assign (it,first.end()-1); // the 5 central values of first

        int myints[] = {1776,7,4};
        third.assign (myints,myints+3);   // assigning from array.
        EXPECT_EQ(7, first.size());
        EXPECT_EQ(5, second.size());
        EXPECT_EQ(3, third.size());
    }
    {
        vector myvector;
        int sum (0);
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);

        while (!myvector.empty())
        {
          sum+=myvector.back();
          myvector.pop_back();
        }
        EXPECT_EQ(600, sum);
    }
    {
        vector myvector (3,100);
        vector result{501,502,503 ,300 ,300 ,400, 400, 200 ,100 ,100 ,100};
        vector::iterator it;

        it = myvector.begin();
        it = myvector.insert ( it , 200 );//200 100 100 100
        std:: cout << myvector;
        myvector.insert (it,2,300);//300 300 200 100 100 100
        std:: cout << myvector;
        // "it" no longer valid, get a new one:
        it = myvector.begin();

        vector anothervector (2,400);
        myvector.insert (it+2,anothervector.begin(),anothervector.end());//300 300 400 400 200 100 100 100
std:: cout << myvector;
        int myarray [] = { 501,502,503 };
        myvector.insert (myvector.begin(), myarray, myarray+3);//501 502 503 300 300 400 400 200 100 100 100
std:: cout << myvector;
        EXPECT_PTR_RANGE_EQ(myvector.begin(), result.begin(), 11);
    }
    {
        vector myvector;
        vector result = {4, 5 ,7, 8 ,9, 10};
        // set some values (from 1 to 10)
        for (int i=1; i<=10; i++) myvector.push_back(i);//1,2,3,4,5,6,7,8,9

        // erase the 6th element
        myvector.erase (myvector.begin()+5);//1,2,3,4,5,7,8,9

        // erase the first 3 elements:
        myvector.erase (myvector.begin(),myvector.begin()+3);//4,5,7,8,9

        EXPECT_PTR_RANGE_EQ(myvector.begin(), result.begin(), 6);
    }
    {
        vector foo (3,100);   // three ints with a value of 100
        vector foo_copy = foo;
        vector bar (5,200);   // five ints with a value of 200
        vector bar_copy = bar;
        foo.swap(bar);

        EXPECT_PTR_RANGE_EQ(foo.begin(), bar_copy.begin(), bar_copy.size());
        EXPECT_PTR_RANGE_EQ(bar.begin(), foo_copy.begin(), foo_copy.size());
    }

    {
        typedef vector_test::Object Object;
        ovector myvector;
        myvector.emplace(myvector.begin(), 100, std::string("jincc"));
        myvector.emplace_back(101, std::string("jun"));
        EXPECT_EQ(100, myvector[0].val);
        EXPECT_EQ("jincc", myvector[0].name);
        EXPECT_EQ(101, myvector[1].val);
        EXPECT_EQ("jun", myvector[1].name);
    }

    {
        vector foo (3,100);   // three ints with a value of 100
        vector bar (2,200);   // two ints with a value of 200
        EXPECT_EQ(0, (foo==bar));
        EXPECT_EQ(1, (foo!=bar));
        EXPECT_EQ(1, (foo< bar));
        EXPECT_EQ(0, (foo> bar));
        EXPECT_EQ(1, (foo<= bar));
        EXPECT_EQ(0, (foo>= bar));
    }
    
}

}
}

#endif /* vector_test_h */
