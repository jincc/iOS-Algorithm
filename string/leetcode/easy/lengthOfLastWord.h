//
//  lengthOfLastWord.h
//  string
//
//  Created by junlongj on 2019/8/14.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef lengthOfLastWord_hpp
#define lengthOfLastWord_hpp

#include <stdio.h>
#include <string>
/*
 58. 最后一个单词的长度
 给定一个仅包含大小写字母和空格 ' ' 的字符串，返回其最后一个单词的长度。
 
 如果不存在最后一个单词，请返回 0 。
 
 说明：一个单词是指由字母组成，但不包含任何空格的字符串。
 
 示例:
 
 输入: "Hello World"
 输出: 5
 
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/length-of-last-word
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
namespace leetcode {
    int lengthOfLastWord(std::string s) {
        int length=0;
        if (s.empty()) return 0;
        bool ch = false;//是否已经出现过字符
        for(int i=s.length()-1;i>=0;i--){
            if (s[i] == ' '){
                if (ch){
                    return length;
                }
            }else{
                ch = true;
                length++;
            }
        }
        return ch ? length : 0 ;
    }
}
#endif /* lengthOfLastWord_hpp */
