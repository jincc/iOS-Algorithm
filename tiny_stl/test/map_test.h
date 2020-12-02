//
//  map_test.h
//  tiny_stl
//
//  Created by junl on 2020/11/21.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef map_test_hpp
#define map_test_hpp
#include "test.h"
#include <iostream>
#include <sstream>
#include <map>
namespace tiny {
namespace test{

#define m_map std::map
#define m_pair std::pair

bool fncomp(char lhs, char rhs) {return lhs < rhs;}

struct classcomp{
    bool operator() (const char &lhs, const char &rhs) const {return lhs < rhs;}
};
TEST(map){
    {
        m_map<char,int> first;

        first['a']=10;
        first['b']=30;
        first['c']=50;
        first['d']=70;

        m_map<char,int> second (first.begin(),first.end());

        m_map<char,int> third (second);

        m_map<char,int,classcomp> fourth;                 // class as Compare

        bool(*fn_pt)(char,char) = fncomp;
        m_map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
    }
    {
        m_map<char,int> first;
        m_map<char,int> second;

        first['x']=8;
        first['y']=16;
        first['z']=32;

        second=first;                // second now contains 3 ints
        first= m_map<char,int>();  // and first is now empty
        EXPECT_EQ(0 , first.size());
        EXPECT_EQ(3 , second.size());
    }
    {
        m_map<char,int> mymap;

        mymap['b'] = 100;
        mymap['a'] = 200;
        mymap['c'] = 300;
        MAP2STREQ("a => 200\n"
                  "b => 100\n"
                  "c => 300\n", mymap);
    }
    {
        m_map<char,int> mymap;

        mymap['x'] = 100;
        mymap['y'] = 200;
        mymap['z'] = 300;

        // show content:
        std::stringstream cout;
        m_map<char,int>::reverse_iterator rit;
        for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
          cout << rit->first << " => " << rit->second << '\n';
        
        EXPECT_PTR_EQ("z => 300\n"
                      "y => 200\n"
                      "x => 100\n", cout.str().c_str());
    }
    {
        m_map<char,int> mymap;

        mymap['a']=10;
        mymap['b']=20;
        mymap['c']=30;
        std::stringstream cout;
        while (!mymap.empty())
        {
          cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
          mymap.erase(mymap.begin());
        }
        EXPECT_PTR_EQ("a => 10\n"
                      "b => 20\n"
                      "c => 30\n", cout.str().c_str());
    }
    {
        m_map<char,int> mymap;
        mymap['a']=101;
        mymap['b']=202;
        mymap['c']=302;
        EXPECT_EQ(3 , mymap.size());
    }
    {
        m_map<std::string,int> mymap = {
                      { "alpha", 0 },
                      { "beta", 0 },
                      { "gamma", 0 } };

        mymap.at("alpha") = 10;
        mymap.at("beta") = 20;
        mymap.at("gamma") = 30;
        MAP2STREQ("alpha => 10\n"
                  "beta => 20\n"
                  "gamma => 30\n", mymap);
    }
    {
        m_map<char,int> mymap;

         // first insert function version (single parameter):
         mymap.insert ( m_pair<char,int>('a',100) );
         mymap.insert ( m_pair<char,int>('z',200) );

         m_pair<m_map<char,int>::iterator,bool> ret;
         ret = mymap.insert ( m_pair<char,int>('z',500) );
        
         EXPECT_EQ(false, ret.second);
         EXPECT_EQ(200, ret.first->second);

         // second insert function version (with hint position):
         m_map<char,int>::iterator it = mymap.begin();
         mymap.insert (it, m_pair<char,int>('b',300));  // max efficiency inserting
         mymap.insert (it, m_pair<char,int>('c',400));  // no max efficiency inserting

         // third insert function version (range insertion):
         m_map<char,int> anothermap;
         anothermap.insert(mymap.begin(),mymap.find('c'));

         MAP2STREQ("a => 100\n"
                   "b => 300\n"
                   "c => 400\n"
                   "z => 200\n", mymap);

         MAP2STREQ("a => 100\n"
                   "b => 300\n", anothermap);
    }
    {
        m_map<char,int> mymap;
        m_map<char,int>::iterator it;

        // insert some values:
        mymap['a']=10;
        mymap['b']=20;
        mymap['c']=30;
        mymap['d']=40;
        mymap['e']=50;
        mymap['f']=60;

        it=mymap.find('b');
        mymap.erase (it);                   // erasing by iterator

        mymap.erase ('c');                  // erasing by key

        it=mymap.find ('e');
        mymap.erase ( it, mymap.end() );    // erasing by range

        // show content:

        MAP2STREQ("a => 10\n"
                  "d => 40\n", mymap);
    }
    {
        m_map<char,int> foo,bar;

        foo['x']=100;
        foo['y']=200;

        bar['a']=11;
        bar['b']=22;
        bar['c']=33;

        foo.swap(bar);

        MAP2STREQ("a => 11\n"
                  "b => 22\n"
                  "c => 33\n", foo);
        MAP2STREQ("x => 100\n"
                  "y => 200\n", bar);
    }
    {
        m_map<char,int> mymap;

         mymap['x']=100;
         mymap['y']=200;
         mymap['z']=300;

         MAP2STREQ("x => 100\n"
                   "y => 200\n"
                   "z => 300\n", mymap);

         mymap.clear();
         mymap['a']=1101;
         mymap['b']=2202;

         MAP2STREQ("a => 1101\n"
                   "b => 2202\n", mymap);

    }
    {
        m_map<char,int> mymap;

        mymap.emplace('x',100);
        mymap.emplace('y',200);
        mymap.emplace('z',100);

        MAP2STREQ("x => 100\n"
                  "y => 200\n"
                  "z => 100\n", mymap);
    }
    {
        m_map<char,int> mymap;
        auto it = mymap.end();

        it = mymap.emplace_hint(it,'b',10);
        mymap.emplace_hint(it,'a',12);
        mymap.emplace_hint(mymap.end(),'c',14);

        MAP2STREQ("a => 12\n"
                  "b => 10\n"
                  "c => 14\n", mymap);
    }
    {
      m_map<char,int> mymap;
      m_map<char,int>::iterator it;

      mymap['a']=50;
      mymap['b']=100;
      mymap['c']=150;
      mymap['d']=200;

      it = mymap.find('b');
      if (it != mymap.end())
      mymap.erase (it);

        EXPECT_EQ(50,mymap.find('a')->second);
        EXPECT_EQ(150,mymap.find('c')->second);
        EXPECT_EQ(200,mymap.find('d')->second);
    }
    {
        m_map<char,int> mymap;
        char c;

        mymap ['a']=101;
        mymap ['c']=202;
        mymap ['f']=303;
        
        std::stringstream cout;
        for (c='a'; c<'h'; c++)
        {
          cout << c;
          if (mymap.count(c)>0)
            cout << " is an element of mymap.\n";
          else
            cout << " is not an element of mymap.\n";
        }
        
        EXPECT_PTR_EQ("a is an element of mymap.\n"
                    "b is not an element of mymap.\n"
                    "c is an element of mymap.\n"
                    "d is not an element of mymap.\n"
                    "e is not an element of mymap.\n"
                    "f is an element of mymap.\n"
                    "g is not an element of mymap.\n", cout.str().c_str());
    }
    {
        m_map<char,int> mymap;
        m_map<char,int>::iterator itlow,itup;

        mymap['a']=20;
        mymap['b']=40;
        mymap['c']=60;
        mymap['d']=80;
        mymap['e']=100;

        itlow=mymap.lower_bound ('b');  // itlow points to b
        itup=mymap.upper_bound ('d');   // itup points to e (not d!)

        mymap.erase(itlow,itup);        // erases [itlow,itup)
        
        MAP2STREQ("a => 20\n"
                  "e => 100\n", mymap);

    }
    {
        m_map<char,int> mymap;

         mymap['a']=10;
         mymap['b']=20;
         mymap['c']=30;

         m_pair<m_map<char,int>::iterator,m_map<char,int>::iterator> ret;
         ret = mymap.equal_range('b');
         std::stringstream cout;
         cout << "lower bound points to: ";
         cout << ret.first->first << " => " << ret.first->second << '\n';

         cout << "upper bound points to: ";
         cout << ret.second->first << " => " << ret.second->second << '\n';
        
        EXPECT_PTR_EQ("lower bound points to: 'b' => 20\n"
                      "upper bound points to: 'c' => 30\n", cout.str().c_str());
    }
}
}
}

#endif /* map_test_hpp */
