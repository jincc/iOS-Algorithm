//
//  iterator_test.h
//  tiny_stl
//
//  Created by junl on 2020/11/12.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef iterator_test_h
#define iterator_test_h
#include <stdio.h>
#include <iterator>
#include "vector.h"
#include "iterator.h"
namespace tiny{
    namespace test{
    //构造，拷贝构造, 前置++， 后置++ , ==, != , 解引用
    struct my_iterator : public tiny::iterator<tiny::input_iterator_tag, int>{
    public:
        friend bool operator==(const my_iterator &l, const my_iterator &r);
        friend bool operator!=(const my_iterator &l, const my_iterator &r);
        my_iterator(int *p):p(p){}
        my_iterator(const my_iterator &ite):p(ite.p){}
        my_iterator& operator++(){
            p++;
            return *this;
        }
        my_iterator operator++(int){
            my_iterator ite(*this);
            operator++();
            return ite;
        }
        int& operator*(){
            return *p;
        }
    private:
        int *p;
    };
    bool operator==(const my_iterator &l, const my_iterator &r){
        return l.p == r.p;
    }
    bool operator!=(const my_iterator &l, const my_iterator &r){
        return l.p != r.p;
    }
    TEST(iterator){
        //test has_iterator_cat
        tiny::vector<int> vec{1};
        EXPECT_EQ(has_iterator_cat<my_iterator>::value, 1);
        //萃取迭代器里的成员
        auto x = std::is_same<iterator_traits<my_iterator>::iterator_category, tiny::input_iterator_tag>::value;
        EXPECT_EQ(1, x);
        x = std::is_same<iterator_traits<my_iterator>::value_type, int>::value;
        EXPECT_EQ(1, x);
        x = std::is_same<iterator_traits<my_iterator>::pointer, int*>::value;
        EXPECT_EQ(1, x);
        
        //萃取指针里的成员
        typedef iterator_traits<int *> pointer_iterator;
        x = std::is_same<pointer_iterator::pointer, int*>::value;
        EXPECT_EQ(1, x);
        
        EXPECT_EQ(1, is_iterator<my_iterator>::value);
        EXPECT_EQ(1, is_input_iterator<my_iterator>::value);
        EXPECT_EQ(0, is_output_iterator<my_iterator>::value);
        
        int arr[] = {1, 2, 3, 4};
        EXPECT_EQ(4, distance(arr, arr + 4));
        
        
        my_iterator mit_start(arr);
        my_iterator mit_end(arr+3);
        EXPECT_EQ(3, distance(mit_start, mit_end));
        
        advance(mit_start, 3);
        EXPECT_EQ(4, *mit_start);
        
        //反向迭代器
        tiny::vector<int> myvector{0, 1, 2, 3, 4, 5, 6, 7};
#if 1
        typedef tiny::reverse_iterator<tiny::vector<int>::iterator> riterator;
#else
        typedef std::reverse_iterator<tiny::vector<int>::iterator> riterator;
#endif
        riterator rev_until(myvector.begin());
        riterator rev_from(myvector.end());
        riterator it = rev_from;
        std::cout << "myvector:";
        while (it != rev_until) {
            std::cout << ' ' << *it++;
        }
        std::cout << std::endl;
        
        auto it2 = rev_until.base();
        std::cout << "myvector:";
        while (it2 != rev_from.base()) {
            std::cout << ' ' << *it2++;
        }
        std::cout << std::endl;
        
        EXPECT_EQ(7, *rev_from);
        EXPECT_EQ(0, *rev_until.base());
        
        it = rev_from + 3;
        EXPECT_EQ(4, *it);
        it++;
        EXPECT_EQ(3, *it);
        it+=1;
        EXPECT_EQ(2, *it);
        it--;
        EXPECT_EQ(3, *it);
        it-=1;
        EXPECT_EQ(4, *it);
        
        EXPECT_EQ(4, rev_from[3]);
        //判断相等运算符
//        EXPECT_PTR_EQ(rev_from, (myvector.end()-1));
        
        auto compare_a = rev_from;
        auto compare_b = rev_until - myvector.size();
        EXPECT_EQ(1, (compare_a == compare_b));
        EXPECT_EQ(1, (compare_a < (compare_a + 1)));
        EXPECT_EQ(1, (compare_a <= (compare_a + 1)));
        EXPECT_EQ(1, ((compare_a+1) > compare_a));
        EXPECT_EQ(1, ((compare_a+1) >= compare_a));
        EXPECT_EQ(1, ((compare_a+1) != compare_a));
        
        EXPECT_EQ(myvector.size(), rev_until - rev_from);
    }
}
}

#endif /* iterator_test_h */
