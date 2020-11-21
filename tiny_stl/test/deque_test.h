//
//  deque_test.h
//  tiny_stl
//
//  Created by junl on 2020/11/18.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef deque_test_hpp
#define deque_test_hpp

#include <stdio.h>
#include "deque.h"
#include <deque>
#include "test.h"
namespace tiny{
namespace test{

namespace deque_test{
struct A{
    A(){std::cout << "A()" << std::endl;}
    A(const A &a){std::cout << "A(const A &a)" << std::endl;}
    A(A &&a) noexcept{std::cout << "A(A &&a)" << std::endl;}
    A& operator=(const A&){std::cout << "A& operator=(const A&)" << std::endl; return *this;}
    A& operator==( A&&){std::cout << "A& operator==( A&&)" << std::endl; return *this;}
};
A getA() {
    return A();
}
};
    TEST(deque){
        tiny::deque_iterator<int , int&, int *> dq1, dq2;
        EXPECT_EQ(0 , (dq1 != dq2));
#if 0
        typedef std::deque<int> myideque;
#else
        typedef tiny::deque<int> myideque;
#endif
        {
            // constructors used in the same order as described above:
            myideque first;                                // empty deque of ints
            myideque second (4,100);                       // four ints with value 100
            myideque second2 (40000,100);                       // four ints with value 100
            myideque third (second.begin(),second.end());  // iterating through second
            myideque fourth (third);                       // a copy of third
            
            // the iterator constructor can be used to copy arrays:
            int myints[] = {16,2,77,29};
            myideque fifth (myints, myints + sizeof(myints) / sizeof(int) );
            STREQ("16 2 77 29 ", fifth);
            STREQ("100 100 100 100 ", second);
            EXPECT_EQ(0, first.size());
            EXPECT_EQ(4, second.size());
            EXPECT_EQ(40000, second2.size());
            EXPECT_EQ(4, third.size());
            EXPECT_EQ(4, fourth.size());
        }
        {
            myideque first (3);    // deque with 3 zero-initialized ints
            myideque second (5);   // deque with 5 zero-initialized ints

            second = first;
            first = myideque();
            EXPECT_EQ(0, first.size());
            EXPECT_EQ(3, second.size());
        }
        {
            myideque mydeque (5);  // 5 default-constructed ints

            myideque::reverse_iterator rit = mydeque.rbegin();

            int i=0;
            for (rit = mydeque.rbegin(); rit!= mydeque.rend(); ++rit)
                *rit = ++i;

            STREQ("5 4 3 2 1 ", mydeque);
        }
        {
            myideque mydeque;
            int sum = 0;
            for (int i=0; i < 100; i++) {
                mydeque.push_back(i);
                sum += i;
            }
            int ret = 0;
            while (!mydeque.empty()) {
                ret += mydeque.back();
                mydeque.pop_back();
            }
            EXPECT_EQ(sum, ret);
        }
        {
            myideque mydeque;
            int sum = 0;
            for (int i=0; i < 100; i++) {
                mydeque.push_front(i);
                sum += i;
            }
//            for (auto it = mydeque.begin(); it != mydeque.end(); it++) {
//                std::cout << *it << std::endl;
//            }
            int ret = 0;
            while (!mydeque.empty()) {
                ret += mydeque.front();
                mydeque.pop_front();
            }
            EXPECT_EQ(sum, ret);
        }
        {
            myideque myints;
            EXPECT_EQ(0, myints.size());
            for (int i=0; i<5; i++) myints.push_back(i);//0,1,2,3,4
            EXPECT_EQ(5, myints.size());
            STREQ("0 1 2 3 4 ", myints);
            myints.insert (myints.begin(),5,100);
            STREQ("100 100 100 100 100 0 1 2 3 4 ", myints);
            EXPECT_EQ(10, myints.size());
            myints.pop_back();
            EXPECT_EQ(9, myints.size());
            
            myints.insert(myints.end(), 5, 100);
            EXPECT_EQ(14, myints.size());
            STREQ("100 100 100 100 100 0 1 2 3 100 100 100 100 100 ", myints);
            
            myints.insert(myints.begin() + 3, 7);
            STREQ("100 100 100 7 100 100 0 1 2 3 100 100 100 100 100 ", myints);
            
            myints.insert(myints.begin() + 6, 9, 6);
            STREQ("100 100 100 7 100 100 6 6 6 6 6 6 6 6 6 0 1 2 3 100 100 100 100 100 ", myints);
            
            myints.insert(myints.begin() + 14, 14);
            STREQ("100 100 100 7 100 100 6 6 6 6 6 6 6 6 14 6 0 1 2 3 100 100 100 100 100 ", myints);

        }
        {
            myideque mydeque;
            tiny::vector<int> vec{1, 2, 3, 4};
            mydeque.insert(mydeque.begin(), {1, 2, 3});
            STREQ("1 2 3 ", mydeque);
            mydeque.insert(mydeque.end(), {7,8,9});
            STREQ("1 2 3 7 8 9 ", mydeque);
            mydeque.insert(mydeque.begin() + 1, {10, 11, 12, 13});
            STREQ("1 10 11 12 13 2 3 7 8 9 ", mydeque);
            
            mydeque.insert(mydeque.end() - 3, vec.begin(), vec.end());
            STREQ("1 10 11 12 13 2 3 1 2 3 4 7 8 9 ", mydeque);
            
        }
        //test copy construct
        {
            using A = deque_test::A;
            tiny::deque<A> dq;
//            dq.insert(dq.begin(), deque_test::getA());
            dq.push_back(deque_test::getA());
            dq.insert(dq.begin(), deque_test::getA());
            dq.insert(dq.end(), deque_test::getA());
            dq.insert(dq.begin() + 1, deque_test::getA());
//            A a = deque_test::getA();
        }
        {
            myideque mydeque;
            myideque::iterator it;

            // set some initial content:
            for (int i=1; i<10; ++i) mydeque.push_back(i);

            mydeque.resize(5);
            mydeque.resize(8,100);
            mydeque.resize(12);

            STREQ("1 2 3 4 5 100 100 100 0 0 0 0 ", mydeque);
        }
        {
            myideque mydeque;
            int sum (0);

            for (int i=1;i<=10;i++) mydeque.push_back(i);

            while (!mydeque.empty())
            {
                sum += mydeque.front();
                mydeque.pop_front();
            }
            EXPECT_EQ(55, sum);
        }
        {
            myideque mydeque (100);
            EXPECT_EQ(100, mydeque.size());

            mydeque.resize(10);
            EXPECT_EQ(10, mydeque.size());
            mydeque.shrink_to_fit();
            EXPECT_EQ(10, mydeque.size());
        }
        {
            myideque mydeque (10);   // 10 zero-initialized elements
            myideque::size_type sz = mydeque.size();

            // assign some values:
            for (unsigned i=0; i<sz; i++) mydeque[i]=i;

            // reverse order of elements using operator[]:
            for (unsigned i=0; i<sz/2; i++)
            {
                int temp;
                temp = mydeque[sz-1-i];
                mydeque[sz-1-i]=mydeque[i];
                mydeque[i]=temp;
            }

            STREQ("9 8 7 6 5 4 3 2 1 0 ", mydeque);
        }
        {
            std::deque<unsigned> mydeque (10);   // 10 zero-initialized unsigneds

            // assign some values:
            for (unsigned i=0; i<mydeque.size(); i++)
                mydeque.at(i)=i;

            STREQ("0 1 2 3 4 5 6 7 8 9 ", mydeque);
        }
        {
            myideque mydeque;

            mydeque.push_front(77);
            mydeque.push_back(20);

            mydeque.front() -= mydeque.back();
            EXPECT_EQ(57, mydeque.front());
        }
        {
            myideque mydeque;

            mydeque.push_back(10);

            while (mydeque.back() != 0)
                mydeque.push_back ( mydeque.back() -1 );

            STREQ("10 9 8 7 6 5 4 3 2 1 0 ", mydeque);
        }
        {
            myideque first;
            myideque second;
            myideque third;

            first.assign (7,100);             // 7 ints with a value of 100

            myideque::iterator it;
            it=first.begin()+1;

            second.assign (it,first.end()-1); // the 5 central values of first

            int myints[] = {1776,7,4};
            third.assign (myints,myints+3);   // assigning from array.

            EXPECT_EQ(7, first.size());
            EXPECT_EQ(5, second.size());
            EXPECT_EQ(3, third.size());
            
        }
        {
            myideque first(11, 100);
            myideque second(1, 99);
            first.assign(second.begin(), second.end());
            STREQ("99 ", first);
        }
        {
            myideque mydeque (2,100);     // two ints with a value of 100
            mydeque.push_front (200);
            mydeque.push_front (300);

            STREQ("300 200 100 100 ", mydeque);
        }
        {
            myideque mydeque;
            int sum (0);
            mydeque.push_back (10);
            mydeque.push_back (20);
            mydeque.push_back (30);

            while (!mydeque.empty())
            {
                sum+=mydeque.back();
                mydeque.pop_back();
            }

            EXPECT_EQ(60, sum);
        }
        {
            myideque mydeque;

            mydeque.push_back (100);
            mydeque.push_back (200);
            mydeque.push_back (300);

            std::stringstream cout;
            cout << "Popping out the elements in mydeque:";
            while (!mydeque.empty())
            {
                cout << ' ' << mydeque.front();
                mydeque.pop_front();
            }

            cout << "\nThe final size of mydeque is " << int(mydeque.size()) << '\n';
            EXPECT_STREQ("Popping out the elements in mydeque: 100 200 300\nThe final size of mydeque is 0\n", cout.str().c_str());
        }
        {
            myideque mydeque;

            // set some initial values:
            for (int i=1; i<6; i++) mydeque.push_back(i); // 1 2 3 4 5

            myideque::iterator it = mydeque.begin();
            ++it;

            it = mydeque.insert (it,10);                  // 1 10 2 3 4 5
            // "it" now points to the newly inserted 10
            STREQ("1 10 2 3 4 5 ", mydeque);
            mydeque.insert (it,2,20);                     // 1 20 20 10 2 3 4 5
            // "it" no longer valid!
            STREQ("1 20 20 10 2 3 4 5 ", mydeque);
            it = mydeque.begin()+2;

            tiny::vector<int> myvector (2,30);
            mydeque.insert (it,myvector.begin(),myvector.end());
            // 1 20 30 30 20 10 2 3 4 5

            STREQ("1 20 30 30 20 10 2 3 4 5 ", mydeque);
        }
        {
            myideque mydeque;

            // set some values (from 1 to 10)
            for (int i=1; i<=10; i++) mydeque.push_back(i);

            // erase the 6th element
            mydeque.erase (mydeque.begin()+5);

            // erase the first 3 elements:
            mydeque.erase (mydeque.begin(),mydeque.begin()+3);


            STREQ("4 5 7 8 9 10 ", mydeque);
            
            
            myideque dq;
            for (int i=1; i<=22; i++) dq.push_back(i);
            dq.erase(dq.begin() + 3, dq.end() - 1);
            STREQ("1 2 3 22 ", dq);
        }
        {
            unsigned int i;
            myideque foo (3,100);   // three ints with a value of 100
            myideque bar (5,200);   // five ints with a value of 200

            foo.swap(bar);


            STREQ("200 200 200 200 200 ", foo);
            STREQ("100 100 100 ", bar);

        }
        {
            myideque mydeque;
            mydeque.push_back (100);
            mydeque.push_back (200);
            mydeque.push_back (300);


            STREQ("100 200 300 ", mydeque);
            mydeque.clear();
            mydeque.push_back (1101);
            mydeque.push_back (2202);
            STREQ("1101 2202 ", mydeque);
        }
        {
            myideque mydeque = {10,20,30};

            auto it = mydeque.emplace ( mydeque.begin()+1, 100 );
            mydeque.emplace ( it, 200 );
            mydeque.emplace ( mydeque.end(), 300 );

            STREQ("10 200 100 20 30 300 ", mydeque);
        }
        {
            myideque mydeque = {10,20,30};

            mydeque.emplace_front (111);
            mydeque.emplace_front (222);

            STREQ("222 111 10 20 30 ", mydeque);
        }
        {
            myideque mydeque = {10,20,30};

            mydeque.emplace_back (100);
            mydeque.emplace_back (200);

            STREQ("10 20 30 100 200 ", mydeque);
        }
        {
            myideque a = {10, 20, 30};
            myideque b = {10, 20, 30};
            myideque c = {30, 20, 10};
            std::stringstream cout;
            if (a==b) cout << "a and b are equal\n";
            if (b!=c) cout << "b and c are not equal\n";
            if (b<c) cout << "b is less than c\n";
            if (c>b) cout << "c is greater than b\n";
            if (a<=b) cout << "a is less than or equal to b\n";
            if (a>=b) cout << "a is greater than or equal to b\n";
            EXPECT_STREQ("a and b are equal\nb and c are not equal\nb is less than c\nc is greater than b\na is less than or equal to b\na is greater than or equal to b\n", cout.str().c_str());
        }
    }
}
}
#endif /* deque_test_hpp */
