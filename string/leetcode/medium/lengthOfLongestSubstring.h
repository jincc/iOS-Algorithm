//
//  lengthOfLongestSubstring.h
//  string
//
//  Created by junlongj on 2019/8/15.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef lengthOfLongestSubstring_hpp
#define lengthOfLongestSubstring_hpp

#include <stdio.h>
#include <string>
#include <map>
/*
 3.无重复字符的最长子串
 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
 
 示例 1:
 
 输入: "abcabcbb"
 输出: 3
 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
namespace leetcode {
    //思路：求的是最长子串，是连续的。利用滑动窗口，hash_table的特性来判断是否包含。
    int lengthOfLongestSubstring(std::string s) {
        if (s.empty()) return 0;
        int left=0;
        int right=0;
        std::map<char,int> mm;//字符对应的下标
        int maxlen=0;
        for(;right<s.length();right++){
            char c = s[right];
            //如果不在map中，或者在滑动窗口left的左边都认为是是不重复的。
            if(mm.count(c) == 0 || mm[c] < left){
                mm[c]=right;
                maxlen=std::max(maxlen,right-left+1);
            }else{
                //已经存在相等的值了
                left=mm[c]+1;
                mm[c]=right;
            }
        }
        return maxlen;
    }
}
#endif /* lengthOfLongestSubstring_hpp */
