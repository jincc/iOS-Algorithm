//
//  main.cpp
//  sort
//
//  Created by junl on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "bubbleSort.h"
#include "insertSort.h"
#include "selectSort.h"
#include "mergeSort.h"
#include "quickSort.h"
#include "kthSmallest.h"
#include "countingSort.h"
#include "heapSort.h"
#include "bucketSort.h"
#include "merge_intervals.h"
#include "sort_colors.h"
using namespace std;
class Solution {
public:
    int InversePairs(vector<int> data) {
        if (data.empty())
            return 0;
        return InversePairs(data, 0 , data.size()-1);
    }
    int InversePairs(vector<int> &data, int start, int end){
        if (start >= end)
            return 0;
        int mid = (start + end)/2;
        int leftcnt = InversePairs(data, start, mid);
        int rightcnt = InversePairs(data, mid+1, end);
        
        int cnt = 0;
        int temp[end-start+1];
        int top, i, j;
        top = 0;
        i = start;
        j = mid+1;
        for(;i <= mid && j <= end;){
            if (data[i] > data[j]){
                //存在逆序对
                temp[top++] = data[j++];
                cnt += mid-i+1;
            }else{
                temp[top++] = data[i++];
            }
        }
        for(; i <= mid; i++){
            temp[top++] = data[i];
        }
        for(; j <= end; j++){
            temp[top++] = data[j];
        }
        
        for(i=start,top=0; i <= end;i++,top++){
            data[i] = temp[top];
        }
        return cnt + leftcnt + rightcnt;
    }
};

using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int num[] = {7,5,6,4};
    Solution so;
    int count = so.InversePairs({7,5,6,4});
    
#pragma mark - o(n^2)
//    bubbleSort(num, 8);
//    insertSort(num,8);
//    selectSort(num, 8);
    
#pragma mark -
    
    mergeSort(num, 4);
//    quickSort(num, 8);
//    int n = kthSmallest(num, 8, 0, 7, 5);
    
//    countingSort(num, 8);
//    heapSort(num, 8);
    test_bucketsort();
    leetcode::test_merge_intervals();
    return 0;
}
