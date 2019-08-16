//
//  ReverseSentence.h
//  string
//
//  Created by junlongj on 2019/8/4.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef ReverseSentence_hpp
#define ReverseSentence_hpp

#include <stdio.h>
#include <string>
#include <vector>


/*
 剑指Offer（四十四）：翻转单词顺序序列
 牛客最近来了一个新员工Fish，每天早晨总是会拿着一本英文杂志，写些句子在本子上。同事Cat对Fish写的内容颇感兴趣，有一天他向Fish借来翻看，但却读不懂它的意思。例如，“student. a am I”。后来才意识到，这家伙原来把句子单词的顺序翻转了，正确的句子应该是“I am a student.”。Cat对一一的翻转这些单词顺序可不在行，你能帮助他么？
https://www.nowcoder.com/practice/3194a4f4cf814f63919d0790578d51f3?tpId=13&tqId=11197&tPage=3&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    std::string ReverseSentence(std::string str) {
        std::vector<std::string> stk;
        std::string s;
        for (auto &c  : str) {
            if (c == ' ') {
                if (s.empty()) {
                    continue;
                }
                stk.push_back(s);
                s = "";
            }else{
                s += c;
            }
        }
        if (!s.empty()) {
            stk.push_back(s);
        }
        if (stk.empty()) {
            return str;
        }
        std::string result;
        while (!stk.empty()) {
            result += stk.back();
            if (stk.size() != 1) {
                result += ' ';
            }
            stk.pop_back();
        }
        return result;
    }
    
    void test_ReverseSentence(){
        std::cout << "ReverseSentence starting......." << std::endl;
        std::string s(" 1");
        std::cout << ReverseSentence(s) << std::endl;
    }
}
#endif /* ReverseSentence_hpp */
