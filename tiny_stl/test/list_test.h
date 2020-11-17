//
//  list_test.h
//  tiny_stl
//
//  Created by junl on 2020/11/15.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef list_test_hpp
#define list_test_hpp

#include "test.h"
#include "list.h"
#include <list>
#include <sstream>
#include <cmath>

namespace tiny{
    namespace test{
        // a binary predicate implemented as a function:
        bool same_integral_part (double first, double second)
        { return ( int(first)==int(second) ); }
        
        // a binary predicate implemented as a class:
        struct is_near {
            bool operator() (double first, double second)
            { return (fabs(first-second)<5.0); }
        };
        bool mycomparison (double first, double second)
        { return ( int(first)<int(second) ); }
        // comparison, not case sensitive.
        bool compare_nocase (const std::string& first, const std::string& second)
        {
            unsigned int i=0;
            while ( (i<first.length()) && (i<second.length()) )
            {
                if (tolower(first[i])<tolower(second[i])) return true;
                else if (tolower(first[i])>tolower(second[i])) return false;
                ++i;
            }
            return ( first.length() < second.length() );
        }
        
       std::string printlist(tiny::list<int> &ilist){
            std::stringstream cout;
            auto beg = ilist.begin();
            while (beg != ilist.end()) {
                cout << *beg++ << " ";
            }
            return cout.str();
        }
    
#define STREQ(_expect, _list) EXPECT_STREQ(_expect, printlist(_list).c_str());
    
        TEST(list){
        #if 0
            typedef std::list<int> ilist;
        #else
            typedef tiny::list<int> ilist;
        #endif
            
            {
                ilist first;                                // empty list of ints
                ilist second (4,100);                       // four ints with value 100
                ilist third (second.begin(),second.end());  // iterating through second
                ilist fourth (third);                       // a copy of third
                
                EXPECT_TRUE(first.empty());
                EXPECT_FALSE(second.empty());
                EXPECT_EQ(4, second.size());
                EXPECT_EQ(0, first.size());
                // the iterator constructor can also be used to construct from arrays:
                int myints[] = {16,2,77,29};
                ilist fifth (myints, myints + sizeof(myints) / sizeof(int) );
                
                STREQ("16 2 77 29 ", fifth);
                STREQ("100 100 100 100 ", second);
            }

            //operator=
            {
                ilist first (3);      // list of 3 zero-initialized ints
                ilist second (5);     // list of 5 zero-initialized ints

                second = first;
                first = ilist();
                EXPECT_EQ(0, first.size());
                EXPECT_EQ(3, second.size());
                
                ilist thrid = {1, 2, 3, 4, 5};
                ilist four(3, 100);
                thrid = four;
                EXPECT_EQ(3, thrid.size());
                STREQ("100 100 100 ", four);
                STREQ("100 100 100 ", thrid);
            }
            
            {
                ilist ilist;
                for (int i=1; i<=5; ++i) ilist.push_back(i);
                
                std::stringstream cout;
                cout << "ilist backwards:";
                for (ilist::reverse_iterator rit=ilist.rbegin(); rit!=ilist.rend(); ++rit)
                    cout << ' ' << *rit;
                
                cout << '\n';
                EXPECT_STREQ("ilist backwards: 5 4 3 2 1\n", cout.str().c_str());

            }
            {
                ilist ilist;
                int sum (0);
                
                for (int i=1;i<=10;++i) ilist.push_back(i);
                
                while (!ilist.empty())
                {
                    sum += ilist.front();
                    ilist.pop_front();
                }
                EXPECT_EQ(55, sum);
            }
            {
                ilist ilist;
                
                ilist.push_back(77);
                ilist.push_back(22);
                
                // now front equals 77, and back 22
                
                ilist.front() -= ilist.back();
                EXPECT_EQ(55, ilist.front());
            }
            {
                ilist first;
                ilist second;
                
                first.assign (7,100);                      // 7 ints with value 100
                STREQ("100 100 100 100 100 100 100 ", first);
                second.assign (first.begin(),first.end()); // a copy of first
                STREQ("100 100 100 100 100 100 100 ", second);
                int myints[]={1776,7,4};
                first.assign (myints,myints+3);            // assigning from array
                STREQ("1776 7 4 ", first);
                EXPECT_EQ(3, first.size());
                EXPECT_EQ(7, second.size());
            }
            {
                tiny::list< std::pair<int,char> > ilist;
                
                ilist.emplace_front(10,'a');
                ilist.emplace_front(20,'b');
                ilist.emplace_front(30,'c');
                
                std::stringstream cout;
                for (auto& x: ilist)
                    cout << " (" << x.first << "," << x.second << ")";
                EXPECT_STREQ(" (30,c) (20,b) (10,a)", cout.str().c_str());
            }
            {
                ilist ilist (2,100);         // two ints with a value of 100
                ilist.push_front (200);
                ilist.push_front (300);
                
                std::stringstream cout;
                for (ilist::iterator it=ilist.begin(); it!=ilist.end(); ++it)
                    cout << ' ' << *it;
                
                EXPECT_STREQ(" 300 200 100 100", cout.str().c_str());
            }
            {
                ilist ilist;
                ilist.push_back (100);
                ilist.push_back (200);
                ilist.push_back (300);
                
                std::stringstream cout;
                cout << "Popping out the elements in ilist:";
                while (!ilist.empty())
                {
                    cout << ' ' << ilist.front();
                    ilist.pop_front();
                }
                
                cout << "\nFinal size of ilist is " << ilist.size() << '\n';
                EXPECT_STREQ("Popping out the elements in ilist: 100 200 300\nFinal size of ilist is 0\n", cout.str().c_str());
            }
            {
                tiny::list< std::pair<int,char> > ilist;
                
                ilist.emplace_back(10,'a');
                ilist.emplace_back(20,'b');
                ilist.emplace_back(30,'c');
                std::stringstream cout;
                cout << "ilist contains:";
                for (auto& x: ilist)
                    cout << " (" << x.first << "," << x.second << ")";
                
                cout << std::endl;
                EXPECT_STREQ("ilist contains: (10,a) (20,b) (30,c)\n", cout.str().c_str());

            }
            {
                ilist ilist;
                int sum (0);
                ilist.push_back (100);
                ilist.push_back (200);
                ilist.push_back (300);
                
                while (!ilist.empty())
                {
                    sum+=ilist.back();
                    ilist.pop_back();
                }
                EXPECT_EQ(600, sum);
            }
            {
                tiny::list< std::pair<int,char> > ilist;
                
                ilist.emplace ( ilist.cbegin(), 100, 'x' );
                ilist.emplace ( ilist.cbegin(), 200, 'y' );
                std::stringstream cout;
                cout << "ilist contains:";
                for (auto& x: ilist)
                    cout << " (" << x.first << "," << x.second << ")";
                
                cout << '\n';
                EXPECT_STREQ("ilist contains: (200,y) (100,x)\n", cout.str().c_str());

            }
            {
                ilist ilist;
                
                // set some initial values:
                for (int i=1; i<=5; ++i) ilist.push_back(i); // 1 2 3 4 5
                
                ilist::const_iterator it = ilist.cbegin();
                ++it;       // it points now to number 2           ^
                
                ilist.insert (it,10);                        // 1 10 2 3 4 5
                STREQ("1 10 2 3 4 5 ", ilist);
                
                // "it" still points to number 2                      ^
                ilist.insert (it,2,20);                      // 1 10 20 20 2 3 4 5
                STREQ("1 10 20 20 2 3 4 5 ", ilist);
                --it;       // it points now to the second 20            ^
                
                tiny::vector<int> myvector (2,30);
                ilist.insert (it,myvector.cbegin(),myvector.cend());
                // 1 10 20 30 30 20 2 3 4 5
                //               ^
                std::stringstream cout;
                cout << "ilist contains:";
                for (it=ilist.cbegin(); it!=ilist.cend(); ++it)
                    cout << ' ' << *it;
                cout << '\n';
                STREQ("1 10 20 30 30 20 2 3 4 5 ", ilist)
            }
            {
                ilist ilist;
                
                // set some values:
                for (int i=1; i<10; ++i) ilist.push_back(i*10);
                ilist::iterator it1 = ilist.begin(),it2 = ilist.begin();
                // 10 20 30 40 50 60 70 80 90
//                it2 += 6;
                tiny::advance (it2,6);            // ^                 ^
                ++it1;                      //    ^              ^
                
                it1 = ilist.erase (it1.getPtr());   // 10 30 40 50 60 70 80 90
                //    ^           ^
                
                it2 = ilist.erase (it2.getPtr());   // 10 30 40 50 60 80 90
                //    ^           ^
                
                ++it1;                      //       ^        ^
                --it2;                      //       ^     ^
                
                ilist.erase (it1.getPtr(),it2.getPtr());     // 10 30 60 80 90
                //        ^
                STREQ("10 30 60 80 90 ", ilist);

            }
            {
                tiny::list<int> first (3,100);   // three ints with a value of 100
                tiny::list<int> second (5,200);  // five ints with a value of 200
                
                first.swap(second);
                STREQ("200 200 200 200 200 ", first);
                STREQ("100 100 100 ", second);
            }
//
            {
                tiny::list<int> ilist;
                
                // set some initial content:
                for (int i=1; i<10; ++i) ilist.push_back(i);
                
                ilist.resize(5);
                ilist.resize(8,100);
                ilist.resize(12);
                STREQ("1 2 3 4 5 100 100 100 0 0 0 0 ", ilist);


            }

            {
                tiny::list<int> ilist;
                ilist.push_back (100);
                ilist.push_back (200);
                ilist.push_back (300);
                
                STREQ("100 200 300 ", ilist);

                ilist.clear();
                ilist.push_back (1101);
                ilist.push_back (2202);
                STREQ("1101 2202 ", ilist);
            }
            {
                tiny::list<int> ilist1, ilist2;
                
                // set some initial values:
                for (int i=1; i<=4; ++i)
                    ilist1.push_back(i);      // ilist1: 1 2 3 4
                
                for (int i=1; i<=3; ++i)
                    ilist2.push_back(i*10);   // ilist2: 10 20 30
                
                tiny::list<int>::const_iterator it = ilist1.cbegin();
                ++it;                         // points to 2
                
                ilist1.splice (it, ilist2); // ilist1: 1 10 20 30 2 3 4
                STREQ("1 10 20 30 2 3 4 ", ilist1);
                STREQ("", ilist2);
                // ilist2 (empty)
                // "it" still points to 2 (the 5th element)
                
                ilist2.splice (ilist2.cbegin(),ilist1, it);
                STREQ("1 10 20 30 3 4 ", ilist1);
                STREQ("2 ", ilist2);
                // ilist1: 1 10 20 30 3 4
                // ilist2: 2
                // "it" is now invalid.
                it = ilist1.cbegin();
                tiny::advance(it,3);           // "it" points now to 30
                
                ilist1.splice ( ilist1.cbegin(), ilist1, it, ilist1.cend());
                // ilist1: 30 3 4 1 10 20
                
                STREQ("30 3 4 1 10 20 ", ilist1);
                STREQ("2 ", ilist2);
            }
            {
                int myints[]= {17,89,7,14};
                tiny::list<int> ilist (myints,myints+4);
                
                ilist.remove(89);
                
                STREQ("17 7 14 ", ilist);
            }

            {
                int myints[]= {15,36,7,17,20,39,4,1};
                tiny::list<int> ilist (myints,myints+8);   // 15 36 7 17 20 39 4 1
                
                auto single_digit = [](const int& value){
                    return value < 10;
                };
                auto is_odd = [](const int &value){
                    return value % 2 == 1;
                };
                ilist.remove_if (single_digit);           // 15 36 17 20 39
                
                ilist.remove_if (is_odd);               // 36 20
                STREQ("36 20 ", ilist);
            }
            {
                tiny::list<int> ilist{1,1,2,3,4,4,4, 5};
                ilist.unique();
                STREQ("1 2 3 4 5 ", ilist);
            }
            {
                ilist alist{2,4,6,8,10};
                ilist blist{1,3,4,5,7};
                alist.merge(blist);
                STREQ("1 2 3 4 4 5 6 7 8 10 ", alist);
                STREQ("",blist);
            }
            
            {
                ilist alist{2,4,6,8,10};
                ilist blist{1,3,4,5,7};
                blist.merge(alist);
                STREQ("1 2 3 4 4 5 6 7 8 10 ", blist);
                STREQ("",alist);
            }
            {
                double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
                    12.77, 73.35, 72.25, 15.3,  72.25 };
                tiny::list<double> ilist (mydoubles,mydoubles+10);
                
                ilist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
                // 15.3,  72.25, 72.25, 73.0,  73.35
                std::cout << ilist << std::endl;
                ilist.unique();           //  2.72,  3.14, 12.15, 12.77
                // 15.3,  72.25, 73.0,  73.35
                 std::cout << ilist << std::endl;
                ilist.unique (same_integral_part);  //  2.72,  3.14, 12.15
                // 15.3,  72.25, 73.0
                 std::cout << ilist << std::endl;
                ilist.unique (is_near());           //  2.72, 12.15, 72.25
                 std::cout << ilist << std::endl;
                std::stringstream cout;
                cout << "ilist contains:";
                for (tiny::list<double>::iterator it=ilist.begin(); it!=ilist.end(); ++it)
                    cout << ' ' << *it;
                cout << '\n';
                EXPECT_STREQ("ilist contains: 2.72 12.15 72.25\n", cout.str().c_str());

            }
//            {
//                tiny::list<double> first, second;
//                
//                first.push_back (3.1);
//                first.push_back (2.2);
//                first.push_back (2.9);
//                
//                second.push_back (3.7);
//                second.push_back (7.1);
//                second.push_back (1.4);
//                
//                first.sort();
//                second.sort();
//                
//                first.merge(second);
//                
//                // (second is now empty)
//                
//                second.push_back (2.1);
//                
//                first.merge(second,mycomparison);
//                
//                std::stringstream cout;
//                cout << "first contains:";
//                for (tiny::list<double>::iterator it=first.begin(); it!=first.end(); ++it)
//                    cout << ' ' << *it;
//                cout << '\n';
//                EXPECT_STREQ("first contains: 1.4 2.2 2.9 2.1 3.1 3.7 7.1\n", cout.str().c_str());
//            }
//            {
//                tiny::list<std::string> ilist;
//                tiny::list<std::string>::iterator it;
//                ilist.push_back ("one");
//                ilist.push_back ("two");
//                ilist.push_back ("Three");
//                
//                ilist.sort();
//                std::stringstream cout;
//                cout << "ilist contains:";
//                for (it=ilist.begin(); it!=ilist.end(); ++it)
//                    cout << ' ' << *it;
//                cout << '\n';
//                EXPECT_STREQ("ilist contains: Three one two\n", cout.str().c_str());
//
//                ilist.sort(compare_nocase);
//                std::stringstream cout2;
//                cout2 << "ilist contains:";
//                for (it=ilist.begin(); it!=ilist.end(); ++it)
//                    cout2 << ' ' << *it;
//                cout2 << '\n';
//                EXPECT_STREQ("ilist contains: one Three two\n", cout2.str().c_str());
//
//            }
            {
                tiny::list<int> ilist;
                
                for (int i=1; i<10; ++i) ilist.push_back(i);
                
                ilist.reverse();
                STREQ("9 8 7 6 5 4 3 2 1 ", ilist);
            }
            {
                tiny::list<int> a = {10, 20, 30};
                tiny::list<int> b = {10, 20, 30};
                tiny::list<int> c = {30, 20, 10};
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
#endif /* list_test_hpp */
