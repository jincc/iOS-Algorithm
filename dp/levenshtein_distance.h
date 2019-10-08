//
//  levenshtein_distance.h
//  dp
//
//  Created by junl on 2019/10/6.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef levenshtein_distance_hpp
#define levenshtein_distance_hpp

#include <stdio.h>

/*
如何量化两个字符串的相似度?
 
有一个非常著名的量化方法就是编辑距离。编辑距离指的是将一个字符串转换成另一个字符串需要的最少的编辑次数。比如莱文斯坦距离和最长公共子串长度.
莱文斯坦距离允许增加，删除，修改字符这三个操作，而最长公共子串长度只允许增加，删除操作.
 
 */

class levenshtein_distance {
public:
    /*
     计算这两个字符串的莱文斯坦距离。
     m i t   c m u
     m   t a c n u
     
     比如上面两个字符串，依次比较每个字符，如果两个字符相等，继续比较下一个字符。
     如果不等的话，有下面几种情况：
        1. 删除后是否后续满足？
        2. 新增后是否满足？
        3. 修改后是否满足?
     */
    int solve(std::string &s1, std::string &s2){
        solve(s1, s2, 0, 0, 0);
        return result;
    }
private:
    int result = INT_MAX;
    void solve(std::string &s1, std::string &s2 ,int i1, int i2, int distance){
        if (i1 == s1.size() || i2 == s2.size()) {
            //计算距离.
            if (i1 < s1.size()) {
                distance += s1.size() - i1;
            }
            if (i2 < s2.size()) {
                distance += s2.size() - i2;
            }
            result = std::min(distance , result);
            return;
        }
        
        if (s1[i1] == s2[i2]) {
            solve(s1, s2, i1+1, i2+1, distance);//继续比较下一个
        }else{
            //1.删除s1[i1]，然后递归考察s1[i1+1]和s2[i2]
            //2.删除s2[i2], 然后递归考察s1[i1]和s2[i2+1]
            //3.在s1的前面新增s2[i2],然后递归考察s1[i1]和s2[i2+1]
            //4.在s2的前面新增s1[i1],然后递归考擦s1[i1+1]和s2[i2]
            //5.替换s1,s2的当前字符
            solve(s1, s2, i1+1, i2, distance+1);
            solve(s1, s2, i1, i2+1, distance+1);
            solve(s1, s2, i1+1, i2+1, distance+1);
        }
        
    }
};


void test_levenshtein_distance(){
    std::cout << "-----------莱文斯坦距离-------------\n" << std::endl;
    class levenshtein_distance so;
    std::string s1 = "mitcmu";
    std::string s2 = "mtacnu";
    std::cout << so.solve(s1, s2) << std::endl;
}

#endif /* levenshtein_distance_hpp */
