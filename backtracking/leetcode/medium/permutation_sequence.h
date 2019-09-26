//
//  permutation_sequence.h
//  backtracking
//
//  Created by junl on 2019/9/21.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef permutation_sequence_hpp
#define permutation_sequence_hpp

#include <stdio.h>
#include <vector>
#include <string>
/*
 60.第k个排列
 给出集合 [1,2,3,…,n]，其所有元素共有 n! 种排列。
 
 按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：
 
 "123"
 "132"
 "213"
 "231"
 "312"
 "321"
 给定 n 和 k，返回第 k 个排列。
 
 说明：
 
 给定 n 的范围是 [1, 9]。
 给定 k 的范围是[1,  n!]。
 示例 1:
 
 输入: n = 3, k = 3
 输出: "213"
 示例 2:
 
 输入: n = 4, k = 9
 输出: "2314"
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/permutation-sequence
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    class Solution60 {
    public:
        /*
         思路:
         我们的目标是求出全排列的第k个排列,其实没必要全排列出前k个所有的情况. 在全排列里面我们可以把排列数分成两部分:第一部分是排列数前面已经确定的数，第二部分是为确定的数，而未确定数(x个)的情况，我们可以通过x!求得。
         
         比如: n=4,k=9
         第一轮，前面确定1，还剩[2,3,4]一共有3！中情况.可以直接跳过这种情况.这时k=9-6=3;
         第二轮, 前面固定2,还剩[1,3,4]，因为k < 3!，所以一定在这里面。
         第三轮，前面固定21，还剩[3,4],因为k > 2!,跳过. k = 3-2=1;
         第四轮, 前面固定23, 还剩[1,4]，因为k < 2!,所以在这里面.
         第五轮，前面固定231,还剩[4],bingo.
         */
        string getPermutation(int n, int k) {
            //先获取全排列，然后取第k个
            string el;
            vector<bool> st; //为了方便，设置n+1个位置
            st.resize(n+1);
            vector<int> level_nodes; //n+1个位置
            level_nodes.push_back(1);
            for(int i=1;i<=n;i++){
                level_nodes.push_back(factorial(i));
            }
            
            permutation(n,k, el, st,level_nodes);
            return result;
        }
        
    private:
        string result;
        int factorial(int n){
            int s=1;
            for (int i=1;i<=n;i++){
                s*=i;
            }
            return s;
        }
        
        void permutation(int n,
                         int k,
                         string elements,
                         vector<bool> st,
                         vector<int> &level_nodes){
            if (!result.empty()) return;
            
            if (elements.size() == n){
                if (--k == 0) {
                    result = elements;
                    return;
                }
            }
            
            for (int i=1;i<=n;i++){
                if (st[i] || elements.size() == n)//如果该数已经用过，直接跳过
                    continue;
                
                int level = elements.size();
                int residue_num = n-1-level;
                if (level_nodes[residue_num] < k){ //如果剩余数的排序组合总数小于k,那么一定不再这个里面.
                    k-=level_nodes[residue_num];
                    continue;
                }
                //通过前面的剪枝，寻找的排列数的前面部分已确定，后面还需要继续寻找。比如2,[1,3,4]
                elements+=to_string(i);
                st[i] = true;
                permutation(n, k, elements, st, level_nodes);
                elements.erase(elements.end()-1);
                st[i] = false;
            }
        }
    };
    void test_permutation_sequence(){
        cout << "permutation_sequence starting......" << endl;
        Solution60 solution;
        cout << solution.getPermutation(4, 9) << endl;
    }
}
#endif /* permutation_sequence_hpp */
