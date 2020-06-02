//
//  Permutation.h
//  string
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef Permutation_hpp
#define Permutation_hpp

#include <stdio.h>
#include <string>
#include <vector>
/*
 剑指Offer（二十七）：字符串的排列
 输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。
https://www.nowcoder.com/practice/fe6b651b66ae47d7acce78ffdd9a96c7?tpId=13&tqId=11180&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    
    std::vector<std::string> insertChar(std::string &s, char c){
        std::vector<std::string> v;
        for (int i=0;i<s.size();i++){
            std::string s1 = s;
            if (s[i] == c) {//如果当前字符和要添加字符一样的话，为了不让重复插入，这里丢弃前方插入
                continue;
            }
            s1.insert(s1.begin()+i, c);
            v.push_back(s1);
        }
        v.push_back(s+c);
        return v;
    }

#pragma mark - v1
    std::vector<std::string> Permutation(std::string &str) {
        if (str.empty()) {
            return {};
        }
        std::vector<std::string> temp;
        temp.push_back(std::string{str[0]});
        for (int i=1; i<str.length(); i++) {//获取第i个字符
            std::vector<std::string> result;
            for (int j =0;j<temp.size();j++){
                std::vector<std::string> s = insertChar(temp[j], str[i]);
                std::copy(s.begin(), s.end(),std::back_inserter(result));
            }
            temp = result;
        }
        std::sort(temp.begin(), temp.end());
        return temp;
    }
#pragma mark - v2
    std::vector<std::string> permutations;
    /*
     思路:将字符串看成两部分，第一个字符为固定的，后面剩余字符串又为待全排的字符串。所以我们首先要计算第一个位置可能出现的字符,即把第一个字符和后面的所有字符进行交换.
     */
    bool isskip(std::string &s, int start, int end);
    void helper(std::string &s, std::vector<std::string> &result, int len,  int nStep);

    std::vector<std::string> permutation(std::string s) {
        std::vector<std::string> result;
        helper(s, result, s.size(), 0);
        return result;
    }
    void helper(std::string &s, std::vector<std::string> &result, int len,  int nStep){
        if (nStep == len){
            result.push_back(s);
        }
        for(int i = nStep; i < len; i++){
            if (isskip(s, nStep, i)) continue;//跳过重复的值
            std::swap(s[nStep], s[i]);
            helper(s, result, len, nStep+1);
            std::swap(s[nStep], s[i]);
        }
    }
    bool isskip(std::string &s, int start, int end){
        /*
         比如 0 1 2 3 4 5 6 4 7，现在pos在位置3，表示0 1 2是已经做过排列的子集， 如果3和第一个4交换递归到下一层就是0 1 2 4 3 5 6 4 7，此时pos为4；如果3和第二个4交换递归到下一层就是0 1 2 4 4 5 6 3 7，此时pos也为4， 这两种情况pos相等且排列好的前缀也相等， 继续递归会不会出现重复？
        */
        for (int i=start; i < end; i++){
            if (s[i] == s[end]) return true;
        }
        return false;
    }
    void test_Permutation(){
        std::string s = "abc";
        std::vector<std::string> x = permutation(s);
        std::cout << "test_Permutation starting......" << std::endl;
        for (auto &str: x){
            std::cout << str <<"," ;
        }
        std::cout << std::endl;
    }
}
#endif /* Permutation_hpp */
