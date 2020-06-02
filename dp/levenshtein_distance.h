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

int min3(int x, int y, int z) {return min(min(x, y),z);}
int levenshtein_distance_dp(char *pStr1, char *pStr2){
    /*
     现在我们假设pStr1[i] != pStr2[j], 那么有以下几种情况可以使它们相等:
        1. 删除pStr1[i], distance = st[i-1][j] + 1
        2. 删除pStr2[j], distance = st[i][j-1] + 1
        3. 在pStr1前面新增字符,  distance = st[i-1][j] + 1
        4. 在pStr2前面新增字符, distance = st[i][j-1] + 1
        5. 替换s1,s2的当前字符 distance = st[i-1][j-1] + 1
     */
    size_t s1, s2;
    s1 = strlen(pStr1);
    s2 = strlen(pStr2);
    int st[s1][s2];//到达字符串pStr1的i位置和pStr2的j位置的最短距离.
    memset(st, 0, sizeof(st));
    
    //初始化初始状态
    st[0][0] = pStr1[0] == pStr2[0] ? 0 : 1;
    for (int i=1; i < s1; i++) {
        st[0][i] = st[0][i-1] + 1;
    }
    for (int i=1; i < s2; i++) {
        st[i][0] = st[i-1][0] + 1;
    }
    
    for (int i=1; i < s1; i++) {
        for (int j=1; j < s2; j++) {
            if (pStr1[i] != pStr2[i]){
                st[i][j] = min3(st[i-1][j] + 1, st[i][j-1] + 1, st[i-1][j-1] + 1);
            }else{
                /*
                 如果pStr1[i] ==  pStr2[j],那么有三种情况:
                    1. 从(i-1, j-1)不需要做任何操作。
                    2. 从(i-1, j) 删除pStr1[i]
                    3. 从(i, j-1) 删除pStr2[j]
                 */
                st[i][j] = min3(st[i-1][j] + 1, st[i][j-1] + 1, st[i-1][j-1]);
            }
        }
    }
    return st[s1-1][s2-1];
}

void test_levenshtein_distance(){
    std::cout << "-----------莱文斯坦距离-------------\n" << std::endl;
    class levenshtein_distance so;
    std::string s1 = "mitcmu";
    std::string s2 = "mtacnu";
    std::cout << so.solve(s1, s2) << std::endl;
    std::cout << levenshtein_distance_dp("mitcmu", "mtacnu") << std::endl;
}

#endif /* levenshtein_distance_hpp */
