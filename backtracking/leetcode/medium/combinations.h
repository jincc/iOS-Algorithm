//
//  combinations.h
//  backtracking
//
//  Created by junl on 2019/9/22.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef combinations_hpp
#define combinations_hpp

#include <stdio.h>

/*
 给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
 
 示例:
 
 输入: n = 4, k = 2
 输出:
 [
 [2,4],
 [3,4],
 [2,3],
 [1,2],
 [1,3],
 [1,4],
 ]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/combinations
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    class Solution77 {
    public:
        /*
         思路:回溯
         其实这题和全排列思路是一样的，区别在于排列数只有k个数.
         
         我们把问题的求解分为K个阶段，每个阶段需要从1...n中随机选择一个数，这样K个阶段后，就能求出k个数的组合.
         
         这种解法效率有点低，看解法2
         */
        vector<vector<int>> combine(int n, int k) {
            if (k > n) return {};
            
            vector<int> elements;
            vector<int> st;
            st.resize(n+1);
            vector<vector<int>> results;
            combine(n, k, elements, st, results);
            return results;
        }
        
        void combine(int n, int k, vector<int> elements, vector<int> st, vector<vector<int>>& results){
            if (elements.size() == k){
                //find
                results.push_back(elements);
                return;
            }
            
            for(int i=1;i<=n;i++){
                if(st[i]) //跳过重复数字
                    continue;
                if(elements.size()>0 && i<= elements.back()){
                    continue;
                }
                elements.push_back(i);st[i]=true;
                combine(n, k, elements, st, results);
                elements.pop_back();st[i]=false;
            }
            
        }
        
        
        /*
         思路:
         利用模式匹配，比如n=5,k=3.构建状态[11100],我们需要将它变换成[00111],即把左边的1依次移动到右边去，每一次移动就是一种排列的可能。
         */
        vector<vector<int>> combine2(int n, int k){
            if (k > n) return {};
            vector<vector<int>> results;
            vector<int> st;
            for (int i=0; i<n; i++) {
                st.push_back(i<k ? 1 : 0);
            }
            while (true) {
                vector<int> temp;
                for (int i=0; i<n; i++) {
                    if (st[i]) {
                        temp.push_back(i);
                    }
                }
                results.push_back(temp);
                
                //1.找到10的结构，然后转换为01
                //2.移动右边的1到最左边
                int found = false;
                int one_count = 0;
                for (int i=0; i<n-1; i++) {
                    if (st[i] == 1 && st[i+1] == 0) {
                        st[i]=0;st[i+1]=1;
                        found = true;
                        
                        for (int j=0; j<i; j++) {
                            st[j] = one_count-- > 0 ? 1:0;
                        }
                        break;
                    }
                    if (st[i] == 1){
                        one_count++;
                    }
                }
                if (!found) {
                    break;
                }
            }
            
            
            return results;
        }
    };
    
    void test_combinations(){
        Solution77 solution;
        cout << "test_combinations starting ........" << endl;
        auto x = solution.combine(4, 2);
        x;
    }
}
#endif /* combinations_hpp */
