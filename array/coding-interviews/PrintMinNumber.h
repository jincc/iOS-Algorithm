//
//  PrintMinNumber.h
//  array
//
//  Created by junlongj on 2019/8/3.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef PrintMinNumber_hpp
#define PrintMinNumber_hpp

#include <stdio.h>
#include <string>
#include <vector>

/*
 剑指Offer（三十二）：把数组排成最小的数
 输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。
https://www.nowcoder.com/practice/8fecd3f8ba334add803bf2a06af1b993?tpId=13&tqId=11185&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */


namespace codinginterviews {
    /*
     这个解题思路可以转换为，我们把整个数组看成是一个整数，现在的认为是把数组排好序，然后顺序组合起来的数字最小。
     
     在这里我们自己定义一个规则，对拼接后的字符串进行比较。
     排序规则如下：
     若ab > ba 则 a 大于 b，
     若ab < ba 则 a 小于 b，
     若ab = ba 则 a 等于 b；
     根据上述规则，我们需要先将数字转换成字符串再进行比较，因为需要串起来进行比较。比较完之后，按顺序输出即可。
     */
    
    static bool Compare(int a, int b){
        std::string A = std::to_string(a) + std::to_string(b);
        std::string B = std::to_string(b) + std::to_string(a);
        return A < B;//说明b比a大
    }
    std::string PrintMinNumber(std::vector<int> numbers) {
        std::sort(numbers.begin(), numbers.end(), Compare);
        std::string s;
        for (auto it = numbers.begin(); it != numbers.end(); it++) {
            s+=std::to_string(*it);
        }
        return s;
    }
#pragma mark - v2
    using namespace std;
    vector<string> results;
    void permutation(vector<int> &numbers, string str, vector<bool> st, int level){
        if (level == numbers.size()){
            results.push_back(str);
            return;
        }
        
        for (int i=0;i<numbers.size();i++){
            if (st[i]) continue;
            st[i] = true;
            permutation(numbers, str+to_string(numbers[i]), st, level + 1);
            st[i] = false;
        }
    }
    string PrintMinNumber2(vector<int> numbers) {
        if (numbers.empty()) return "";
        vector<bool> st;
        st.resize(numbers.size());
        fill(st.begin(), st.end(), false);
        string str;
        permutation(numbers, str, st, 0);
        sort(results.begin(), results.end());
        return results[0];
    }
    
    void test_PrintMinNumber(){
        std::vector<int> a{3,32,321};
        std::cout << "test_PrintMinNumber starting........" << std::endl;
        std::cout << PrintMinNumber2(a) << std::endl;
    }
}
#endif /* PrintMinNumber_hpp */
