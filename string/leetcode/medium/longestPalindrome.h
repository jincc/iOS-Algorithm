//
//  longestPalindrome.h
//  string
//
//  Created by junlongj on 2019/8/15.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef longestPalindrome_hpp
#define longestPalindrome_hpp

#include <stdio.h>
#include <string>
/*
 5.最长回文子串
 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
 
 示例 1：
 
 输入: "babad"
 输出: "bab"
 注意: "aba" 也是一个有效答案。
 示例 2：
 
 输入: "cbbd"
 输出: "bb"
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/longest-palindromic-substring
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
namespace leetcode {
    int palindrome(std::string &s, int left,int right);
    //思路：将字符串看成2n-1个子字符串，每个字符串都有一个中心，从中心发散出去，判断是否是回文.然后获取最长的回文字符串.注意start起点位置的计算，可以多画图参考
    std::string longestPalindrome(std::string s) {
        if (s.length()<=1) return s;
        int maxlen=1;
        int start=0;
        for(int i=1;i<s.length();i++){
            int len1=palindrome(s,i-1,i);
            int len2=palindrome(s,i,i);
            if (len1>maxlen){
                maxlen=len1;
                start = i-maxlen/2;
            }
            if (len2>maxlen){
                maxlen=len2;
                start=i-(maxlen-1)/2;
            }
        }
        return s.substr(start,maxlen);
    }
    int palindrome(std::string &s, int left,int right){
        while(left>=0 && right<s.length() && s[left] == s[right]){
            left--;right++;
        }
        return right-left-1;
    }
    
    void test_longestPalindrome(){
        std::string s = "bb";
        std::cout << "longestPalindrome: " << longestPalindrome(s) << std::endl;
    }
}
#endif /* longestPalindrome_hpp */
