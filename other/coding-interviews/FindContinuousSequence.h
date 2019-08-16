//
//  FindContinuousSequence.h
//  other
//
//  Created by junl on 2019/8/5.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef FindContinuousSequence_hpp
#define FindContinuousSequence_hpp

#include <stdio.h>
#include <vector>
/*
 剑指Offer（四十一）：和为S的连续正数序列

 小明很喜欢数学,有一天他在做数学作业时,要求计算出9~16的和,他马上就写出了正确答案是100。但是他并不满足于此,他在想究竟有多少种连续的正数序列的和为100(至少包括两个数)。没多久,他就得到另一组连续正数和为100的序列:18,19,20,21,22。现在把问题交给你,你能不能也很快的找出所有和为S的连续正数序列? Good Luck!
 输出所有和为S的连续正数序列。序列内按照从小至大的顺序，序列间按照开始数字从小到大的顺序

 https://www.nowcoder.com/practice/c451a3fd84b64cb19485dad758a55ebe?tpId=13&tqId=11194&tPage=3&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    std::vector<std::vector<int> > FindContinuousSequence(int sum) {
        /*
    left和right表示序列中的最小值和最大值，如果left...right之间的和比sum小,那么right向右滑动一步。如果left...right之间的和比sum大,那么left向右滑动一步.直到他们到达中间节点。
         */
        std::vector<std::vector<int>> results;
        std::vector<int> temp;
        int left = 1;
        int right = 2;
        int mid = (sum + 1 ) / 2;
        int ctsum = left+right;
        while (left <= mid && right <= mid) {
            if (ctsum < sum) {
                right++;
                ctsum+=right;
            }else if (ctsum > sum){
                ctsum -= left;
                left++;
            }else{
                temp.clear();
                for (int i=left;i<=right;i++){
                    temp.push_back(i);
                }
                results.push_back(temp);
                
                right++;
                ctsum+=right;
            }
        }
        return results;
    }
    
    void test_FindContinuousSequence(){
        std::cout << "FindContinuousSequence starting......." << std::endl;
        std::vector< std::vector<int> > res = FindContinuousSequence(100);
        for (auto &v : res){
            for (auto &a : v){
                std::cout << a << ", " ;
            }
            std::cout << std::endl;
        }
    }
}
#endif /* FindContinuousSequence_hpp */
