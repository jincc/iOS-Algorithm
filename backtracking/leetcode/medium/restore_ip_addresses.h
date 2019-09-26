//
//  restore_ip_addresses.h
//  backtracking
//
//  Created by junl on 2019/9/27.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef restore_ip_addresses_hpp
#define restore_ip_addresses_hpp

#include <stdio.h>
/*
 93.复原IP地址
 给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。
 
 示例:
 
 输入: "25525511135"
 输出: ["255.255.11.135", "255.255.111.35"]
 在真实的面试中遇到过这道题？
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/restore-ip-addresses
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    class Solution93 {
    public:
        /*
         思路:
         回溯,把问题的求解分成4个步骤，每个步骤里面我们可以随机在相邻的三位数字后面加入'.'，不行的话在回溯.
         */
        vector<string> restoreIpAddresses(string s) {
            vector<string> results;
            string temp;
            restoreIpAddresses(s, results, 0, 0, temp);
            return results;
        }
        
        
        void restoreIpAddresses(string &s, vector<string> & results, int p_num,int ctindex, string temp){
            if (ctindex >= s.length())
                return;
            if (p_num == 3){
                int substr_len = s.length()-ctindex;
                string substr = s.substr(ctindex, substr_len);
                int num = atoi(substr.c_str());
                if ( num  >= 0  && num <= 255){
                    //find
                    //过滤掉无效的IP，比如.010
                    if (substr_len > 1 && s[ctindex] == '0')
                        return;
                    
                    temp += substr;
                    results.push_back(temp);
                    return;
                }
                return;
            }
            
            for(int i=1;i<=3;i++){
                string substr = s.substr(ctindex, i);
                int num = atoi(substr.c_str());
                if (num>=0 && num <= 255){
                    //过滤掉无效的IP，比如.010
                    if (i > 1 && s[ctindex] == '0')
                        continue;
                    
                    int last_len = temp.length();
                    temp+=substr;
                    temp+='.';
                    ctindex+=i;
                    p_num+=1;
                    
                    restoreIpAddresses(s, results, p_num, ctindex, temp);
                    
                    ctindex-=i;
                    p_num-=1;
                    temp.erase(last_len, i+1);
                    
                }
            }
            
        }
        
    };
}
#endif /* restore_ip_addresses_hpp */
