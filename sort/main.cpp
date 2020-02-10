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
        mergeSort(data, 0, data.size()-1);
        return count;
    }
    
    void mergeSort(vector<int> &data,int start, int end){
        if (start >= end)
            return;
        int mid = start + (end - start)/2;
        mergeSort(data, start, mid);
        mergeSort(data, mid+1, end);
        merge(data,start,mid,end);
    }
    void merge(vector<int> &data,int start,int mid, int end){
        vector<int> temp;
        temp.resize(end-start+1);
        int i=start;
        int j=mid+1;
        int index=0;
        while(i<=mid && j<=end){
            if (data[i] > data[j]){
//                std::cout << data[i] << ", " << data[j] << std::endl;
                temp[index++] = data[i++];
                count++;
            }else{
                temp[index++] = data[j++];
            }
        }
        while(i<=mid){
            temp[index++] = data[i++];
        }
        while(j<=end){
            temp[index++] = data[j++];
        }
        index=0;
        for(i=start;i<=end;i++){
            data[i] = temp[index++];
        }
    }
    int count = 0;
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
