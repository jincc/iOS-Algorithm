//
//  unordered_map_test.h
//  tiny_stl
//
//  Created by junl on 2020/11/21.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef unordered_map_test_hpp
#define unordered_map_test_hpp

#include <iostream>
#include <string>

#if 0
#include <unordered_map>
template<class Key, class Value>
using my_unordered_map = std::unordered_map<Key, Value>;
#else
#include "unordered_map.h"
#include "pair.h"
template<class Key, class Value>
using my_unordered_map = tiny::unordered_map<Key, Value>;
#endif
typedef my_unordered_map<std::string,std::string> stringmap;

namespace tiny{
namespace test{
    stringmap merge (stringmap a,stringmap b) {
        stringmap temp(a);
        temp.insert(b.begin(),b.end());
        return temp;
    }
    TEST(unordered_map){
        {
            stringmap third ( {{"orange","orange"},{"strawberry","red"},{"orange","orange2"}} );
            MAPSTREQ("strawberry:red,orange:orange,", third);
        }
        {
            stringmap first;                              // empty
            stringmap second ( {{"apple","red"},{"lemon","yellow"}} );       // init list
            stringmap third ( {{"orange","orange"},{"strawberry","red"}} );  // init list
            stringmap fourth (second);                    // copy
            stringmap fifth (merge(third,fourth));        // move
            stringmap sixth (fifth.begin(),fifth.end());  // range

        
            MAPSTREQ("lemon:yellow,apple:red,", second);
            MAPSTREQ("strawberry:red,orange:orange,", third);
            MAPSTREQ("apple:red,lemon:yellow,", fourth);
            MAPSTREQ("apple:red,lemon:yellow,strawberry:red,orange:orange,", fifth);
            MAPSTREQ("orange:orange,strawberry:red,lemon:yellow,apple:red,", sixth);
        }
        {
            stringmap first, second, third;
            first = {{"AAPL","Apple"},{"MSFT","Microsoft"}};  // init list
            second = {{"GOOG","Google"},{"ORCL","Oracle"}};   // init list
            third = merge(first,second);                      // move
            first = third;                                    // copy

            MAPSTREQ("GOOG:Google,ORCL:Oracle,MSFT:Microsoft,AAPL:Apple,", first);
            MAPSTREQ("ORCL:Oracle,GOOG:Google,", second);
            MAPSTREQ("GOOG:Google,ORCL:Oracle,MSFT:Microsoft,AAPL:Apple,", third);
        }
        {
            stringmap first, second, third;
            first = {{"AAPL","Apple"},{"MSFT","Microsoft"}};  // init list
            EXPECT_TRUE(second.empty());
            EXPECT_TRUE(!first.empty());
        }
        {
            my_unordered_map<std::string,int> mymap = {
                {"milk",2.30},
                {"potatoes",1.90},
                {"eggs",0.40}
            };
            EXPECT_EQ(3, mymap.size());
        }
        {
            stringmap mymap;

            mymap["Bakery"]="Barbara";  // new element inserted
            mymap["Seafood"]="Lisa";    // new element inserted
            mymap["Produce"]="John";    // new element inserted

            std::string name = mymap["Bakery"];   // existing element accessed (read)
            mymap["Seafood"] = name;              // existing element accessed (written)

            mymap["Bakery"] = mymap["Produce"];   // existing elements accessed (read/written)

            name = mymap["Deli"];      // non-existing element: new element "Deli" inserted!

            mymap["Produce"] = mymap["Gifts"];    // new element "Gifts" inserted, "Produce" written

            MAPSTREQ("Deli:,Produce:,Gifts:,Seafood:Barbara,Bakery:John,", mymap);

        }
        {
            my_unordered_map<std::string,int> mymap = {
                { "Mars", 3000},
                { "Saturn", 60000},
                { "Jupiter", 70000 } };

            mymap.at("Mars") = 3396;
            mymap.at("Saturn") += 272;
            mymap.at("Jupiter") = mymap.at("Saturn") + 9638;

            for (auto& x: mymap) {
                std::cout << x.first << ": " << x.second << std::endl;
            }
            MAPSTREQ("Jupiter:69910,Saturn:60272,Mars:3396,", mymap);

        }
        {
            my_unordered_map<std::string,double> mymap = {
                {"mom",5.4},
                {"dad",6.1},
                {"bro",5.9} };


            my_unordered_map<std::string,double>::const_iterator got = mymap.find ("dad");
            EXPECT_EQ(got->second, 6.1);
            got = mymap.find ("parent");
            EXPECT_TRUE(got == mymap.end());
        }
        {
            my_unordered_map<std::string,double> mymap = {
                {"Burger",2.99},
                {"Fries",1.99},
                {"Soda",1.50} };

            std::stringstream cout;
            for (auto& x: {"Burger","Pizza","Salad","Soda"}) {
                if (mymap.count(x)>0)
                    cout << "mymap has " << x << std::endl;
                else
                    cout << "mymap has no " << x << std::endl;
            }
            EXPECT_PTR_EQ("mymap has Burger\nmymap has no Pizza\nmymap has no Salad\nmymap has Soda", cout.str().c_str());
        }
        {
            my_unordered_map<std::string,std::string> mymap;

            mymap.emplace ("NCC-1701", "J.T. Kirk");
            mymap.emplace ("NCC-1701-D", "J.L. Picard");
            mymap.emplace ("NCC-74656", "K. Janeway");
            MAPSTREQ("NCC-74656:K. Janeway,NCC-1701-D:J.L. Picard,NCC-1701:J.T. Kirk,", mymap);
        }
        {
            my_unordered_map<std::string,double>
            myrecipe,
            mypantry = {{"milk",2.0},{"flour",1.5}};

            tiny::pair<std::string,double> myshopping ("baking powder",0.3);

            myrecipe.insert (myshopping);                        // copy insertion
            myrecipe.insert ({"eggs",6.0}); // move insertion
            myrecipe.insert (mypantry.begin(), mypantry.end());  // range insertion
            myrecipe.insert ( {{"sugar",0.8},{"salt",0.1}} );    // initializer list insertion

            MAPSTREQ("salt:0.1,baking powder:0.3,flour:1.5,milk:2,eggs:6,sugar:0.8,", myrecipe);

        }
        {
            my_unordered_map<std::string,std::string> mymap;

            // populating container:
            mymap["U.S."] = "Washington";
            mymap["U.K."] = "London";
            mymap["France"] = "Paris";
            mymap["Russia"] = "Moscow";
            mymap["China"] = "Beijing";
            mymap["Germany"] = "Berlin";
            mymap["Japan"] = "Tokyo";
            EXPECT_EQ(7, mymap.size());
            // erase examples:
            mymap.erase ( mymap.begin() );      // erasing by iterator
            EXPECT_EQ(6, mymap.size());
            mymap.erase ("France");             // erasing by key
            EXPECT_EQ(5, mymap.size());
            for (auto it = mymap.begin(); it != mymap.end(); it++) {
                std::cout << it->first << ":" << it->second << std::endl;
            }
//            mymap.erase ( mymap.find("China"), mymap.end() ); // erasing by range
            
        }
        {
            my_unordered_map<std::string,std::string> mymap =
            { {"house","maison"}, {"car","voiture"}, {"grapefruit","pamplemousse"} };
            MAPSTREQ("grapefruit:pamplemousse,car:voiture,house:maison,", mymap);

            mymap.clear();
            mymap["hello"]="bonjour";
            mymap["sun"]="soleil";

            MAPSTREQ("sun:soleil,hello:bonjour,", mymap);

        }
        {
            my_unordered_map<std::string,std::string>
            first = {{"Star Wars","G. Lucas"},{"Alien","R. Scott"},{"Terminator","J. Cameron"}},
            second  = {{"Inception","C. Nolan"},{"Donnie Darko","R. Kelly"}};

            first.swap(second);

            MAPSTREQ("Donnie Darko:R. Kelly,Inception:C. Nolan,", first);


            MAPSTREQ("Terminator:J. Cameron,Alien:R. Scott,Star Wars:G. Lucas,", second);

        }
        {
            my_unordered_map<std::string,std::string> mymap = {
                {"house","maison"},
                {"apple","pomme"},
                {"tree","arbre"},
                {"book","livre"},
                {"door","porte"},
                {"grapefruit","pamplemousse"}
            };

            unsigned n = mymap.bucket_count();
            std::cout << "mymap has " << n << " buckets.\n";

            for (unsigned i=0; i<n; ++i) {
                std::cout << "bucket #" << i << " contains: ";
                for (auto it = mymap.begin(i); it!=mymap.end(i); ++it)
                    std::cout << "[" << it->first << ":" << it->second << "] ";
                std::cout << "\n";
            }
        }
        {
            my_unordered_map<std::string,std::string> mymap = {
                {"us","United States"},
                {"uk","United Kingdom"},
                {"fr","France"},
                {"de","Germany"}
            };

            unsigned nbuckets = mymap.bucket_count();

            std::cout << "mymap has " << nbuckets << " buckets:\n";

            for (unsigned i=0; i<nbuckets; ++i) {
                std::cout << "bucket #" << i << " has " << mymap.bucket_size(i) << " elements.\n";
            }

        }
        {
            my_unordered_map<int , int> mymap;
            for (int i = 0 ; i < 10000; i++) {
                mymap[i] = i;
            }
        }
    }
}
}

#endif /* unordered_map_test_hpp */
