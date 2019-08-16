//
//  merge.h
//  array
//
//  Created by junlongj on 2019/8/7.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef merge_hpp
#define merge_hpp

#include <stdio.h>
/*
 88. 合并两个有序数组
 给定两个有序整数数组 nums1 和 nums2，将 nums2 合并到 nums1 中，使得 num1 成为一个有序数组。
 
 说明:
 
 初始化 nums1 和 nums2 的元素数量分别为 m 和 n。
 你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
 示例:
 
 输入:
 nums1 = [1,2,3,0,0,0], m = 3
 nums2 = [2,5,6],       n = 3
 
 输出: [1,2,2,3,5,6]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/merge-sorted-array
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

 */
namespace leetcode {
#pragma mark - bad
    /*
     思路:从前向后遍历，每次在nums2[j]和nums1[i]选取最小的元素让在nums1的后面.
     如果nums2[j]比nums1[i]小的话，那么先将nums2【i】后面的所以元素都向右移动一位，然后插入nums2[j].
     如果nums2[j]大的话，那么跳过.
     
     这种遍历会有大量数据移动
     */
    void merge2(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        int i=0;
        int j=0;
        while(i<m && j < n){
            //需要把nums2[j]插入进来
            if (nums1[i]>nums2[j]){
                //先将nums1[i....]所有的元素向后移动一位
                for (int k=m-1;k>=i;k--){
                    nums1[k+1] = nums1[k];
                }
                //插入nums2[j];
                nums1[i++]=nums2[j++];
                m++;
            }else{
                i++;
            }
        }
        //说明nums2还有内容没插入完.
        while (j < n){
            nums1[i++]=nums2[j++];
            m++;
        }
    }
    
#pragma mark - good
    /*
     从后向前遍历，每次选取最大的元素放在末尾。
     */
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        int i1=m-1;
        int i2=n-1;
        for(int k=m+n-1;k>=0;k--){
            if (i2<0){
                break;
            }
            if (i1<0 && i2>=0){
                nums1[k]=nums2[i2--];
                continue;
            }
            
            if (nums1[i1] > nums2[i2]){
                nums1[k] = nums1[i1--];
            }else{
                nums1[k] = nums2[i2--];
            }
        }
    }
}
#endif /* merge_hpp */
