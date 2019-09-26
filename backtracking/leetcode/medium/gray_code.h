//
//  gray_code.h
//  backtracking
//
//  Created by junl on 2019/9/25.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef gray_code_hpp
#define gray_code_hpp

#include <stdio.h>
#include <math.h>
/*
 89. 格雷编码
 格雷编码是一个二进制数字系统，在该系统中，两个连续的数值仅有一个位数的差异。
 
 给定一个代表编码总位数的非负整数 n，打印其格雷编码序列。格雷编码序列必须以 0 开头。
 
 示例 1:
 
 输入: 2
 输出: [0,1,3,2]
 解释:
 00 - 0
 01 - 1
 11 - 3
 10 - 2
 
 对于给定的 n，其格雷编码序列并不唯一。
 例如，[0,2,3,1] 也是一个有效的格雷编码序列。
 
 00 - 0
 10 - 2
 11 - 3
 01 - 1
 */

namespace leetcode {
    class Solution89 {
    public:
        vector<int> results;
        
        vector<int> grayCode(int n) {
            if (n == 0) return {0};
            map<string,bool> st;
            string elements;
            for(int i=0;i<n;i++){
                elements+='0';
            }
            int totalCount = pow(2,n);
            grayCode(elements, st, totalCount);
            return results;
        }
        
        void grayCode(string elements, map<string,bool> &st, int totalCount){
            if (results.size() == totalCount || st[elements])
                return;
            int loc = calc10(elements);
            results.push_back(loc);
            st[elements] = true;
            for(int i=0;i<elements.size();i++){
                elements[i] =  elements[i] == '0' ? '1' : '0';
                grayCode(elements, st, totalCount);
                elements[i] =  elements[i] == '0' ? '1' : '0';
            }
        }
        
        int calc10(string &nums){
            int sum=0;
            int l = 1;
            for(int i=nums.size()-1;i>=0;i--){
                sum+=(nums[i]-'0')*l;
                l*=2;
            }
            return sum;
        }
    };
    
    void test_gray_code(){
        cout << "test_gray_code starting...." << endl;
        Solution89 so;
        vector<int> results = so.grayCode(2);
        for (auto &i:results){
            cout << i << ", ";
        }
        cout << endl;
    }
}
#endif /* gray_code_hpp */
