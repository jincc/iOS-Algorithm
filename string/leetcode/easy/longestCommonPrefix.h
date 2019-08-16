//
//  longestCommonPrefix.h
//  string
//
//  Created by junlongj on 2019/8/12.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef longestCommonPrefix_hpp
#define longestCommonPrefix_hpp

#include <stdio.h>
#include <string>
#include <vector>
/*
 14. 最长公共前缀
 编写一个函数来查找字符串数组中的最长公共前缀。
 
 如果不存在公共前缀，返回空字符串 ""。
 
 示例 1:
 
 输入: ["flower","flow","flight"]
 输出: "fl"
 示例 2:
 
 输入: ["dog","racecar","car"]
 输出: ""
 解释: 输入不存在公共前缀。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/longest-common-prefix
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    /*
     LCP(s1,s2......sn) =  LCP(LCP(LCP(s1,s2),s3),.....)
     水平扫描:先计算第一个字符串和第二个字符串的最长前缀，然后结果和第三个字符串继续计算前缀。。。。
     */
    std::string longestCommonPrefix2(std::vector<std::string>& strs) {
        //最长公共前缀，找的是前缀
        if (strs.empty()) return "";
        
        std::string match = strs[0];
        for(int i=1;i<strs.size();i++){
            int j=0;
            for(;j<strs[i].length();j++){
                if(match[j] != strs[i][j])
                    break;
            }
            if (j == 0){
                return "";
            }
            match=match.substr(0,j);
        }
        return match;
    }
    /*
     纵向扫描,先判断每一列是否相等，然后进行下一列判断。
     上面解法：复杂度为O(S*len),S为S数组大小，len为每项字符串长度
     当前解法：复杂度为O(S*minlen),S为S数组大小，minlen为最短字符串长度.
     */
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        //纵向扫描
        if (strs.empty()) return "";
        int len = strs[0].length();
        for (int i=0;i<len;i++){
            for(int j=1;j<strs.size();j++){
                //如果字符不匹配，或者当前字符串没有该项，直接返回结果。
                if( i>strs[j].length() || strs[j][i]!= strs[0][i]){
                    return strs[0].substr(0,i);
                }
            }
        }
        return strs[0];
    }
}
#endif /* longestCommonPrefix_hpp */
