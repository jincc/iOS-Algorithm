//
//  letter_combinations_of_a_phone_number.h
//  backtracking
//
//  Created by junlongj on 2019/8/20.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef letter_combinations_of_a_phone_number_hpp
#define letter_combinations_of_a_phone_number_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <map>
/*
 17. 电话号码的字母组合
 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
 
 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

 示例:
 
 输入："23"
 输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    /*
     思路: 回溯法，遍历每个数字下可能出现的所有可能，注意终止条件。
     时间复杂度: 假设每个数字只对应三个字符。那么每一轮都有三种可能，一共N轮，N为字符串长度。所以复杂度为3^N。
     */
    std::vector<std::string> result;
    void letterCombinations(std::string &digits,std::map<char,std::vector<char>> &kvs, int ct, std::string str) {
        if (ct == digits.length()){
            result.push_back(str);
            return;
        }
        std::vector<char> mm = kvs[digits[ct]];
        for(int i=0;i<mm.size();i++){
            letterCombinations(digits, kvs, ct+1, str+ mm[i]);
        }
    }
    std::vector<std::string> letterCombinations(std::string digits) {
        if (digits.empty()) return {};
        std::map<char,std::vector<char>> mm{{'2',{'a','b','c'}},
            {'3',{'d','e','f'}},
            {'4',{'g','h','i'}},
            {'5',{'j','k','l'}},
            {'6',{'m','n','o'}},
            {'7',{'p','q','r','s'}},
            {'8',{'t','u','v'}},
            {'9',{'w','x','y','z'}}};
        std::string s;
        letterCombinations(digits, mm, 0, s);
        return  result;
    }
    /*
     思路：DP思想，通过之前combinations[n-1]的状态推导出combinations[n]的状态。那么递推公式为：
     
     for x in combinations[n-1]: 遍历之前n-1个number的结果
        for y in set(y): number可能出现的字母
            x combination y; 合并
     */
    std::vector<std::string> letterCombinations2(std::string digits) {
        char  phone[10][4]={ {' ',  '\0', '\0', '\0' }, //0
            {'\0', '\0', '\0', '\0' }, //1
            {'a',  'b',  'c',  '\0' }, //2
            {'d',  'e',  'f',  '\0' }, //3
            {'g',  'h',  'i',  '\0' }, //4
            {'j',  'k',  'l',  '\0' }, //5
            {'m',  'n',  'o',  '\0' }, //6
            {'p',  'q',  'r',  's'  }, //7
            {'t',  'u',  'v',  '\0' }, //8
            {'w',  'x',  'y',  'z'  }  //9
        };
        std::vector<std::string> result;
        if (digits.empty()) {
            return result;
        }
        //初始化数据
        int fc = digits[0] - '0';
        for (int i=0;i<4 && phone[fc][i] != '\0';i++){
            std::string s;
            s+= phone[fc][i];
            result.push_back(s);
        }
        
        for (int j=1; j<digits.size(); j++) {
            int fc = digits[j] - '0';
            std::vector<std::string> r;
            for (int i=0; i<result.size(); i++) {
                for (int k=0; k< 4 && phone[fc][k]!= '\0'; k++) {
                    std::string s = result[i];
                    s+=phone[fc][k];
                    r.push_back(s);
                }
            }
            result = r;
        }
        
        return result;
    }
    void test_letterCombinations(){
        std::string s = "23";
        auto s1 = letterCombinations2(s);
        s1;
    }
}
#endif /* letter_combinations_of_a_phone_number_hpp */
