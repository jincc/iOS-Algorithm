//
//  sort_colors.h
//  sort
//
//  Created by junlongj on 2019/9/3.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef sort_colors_hpp
#define sort_colors_hpp

#include <stdio.h>
#include <vector>
/*
 75.颜色分类
 
 给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
 
 此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
 
 注意:
 不能使用代码库中的排序函数来解决这道题。
 
 示例:
 
 输入: [2,0,2,1,1,0]
 输出: [0,0,1,1,2,2]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/sort-colors
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    /*
     思路： 最简单的办法是利用计数排序，创建三个桶，第一轮循环在三个桶里面放各自的元素.第二次循环把三个桶连起来。
     但是题目要求的是原地排序.
     
     我们可以先将红和白看成一个桶里的元素，蓝色为另一个桶里的元素. 双指针法，一个在头，一个在尾，开始遍历找对方桶里面的元素，如果找到那么双方交换元素.
     这样第一轮下来，数组里面的内容就是:蓝色在最后面，而前面的红和白还是无序的。我们再次利用双指针来排序即可。

     */
    
    void sortColors(vector<int>& nums) {
        //使用双指针法，先将红和白看成一个桶里的元素，蓝色为另一个桶里的元素.
        
        if (nums.empty()) return;
        int i=0;
        int j=nums.size()-1;
        while(i<j){
            if (nums[i]==2 && (nums[j] == 0 || nums[j] == 1)){
                swap(nums[i++],nums[j--]);
            }else{
                if (nums[i] != 2){
                    i++;
                }
                if (nums[j] == 2){
                    j--;
                }
            }
        }
        
        //然后重新排序第一个桶里面红和白的顺序
        i=0;
        j=nums.size()-1;
        while(i<j){
            if (nums[j] == 2){
                j--;
                continue;
            }
            if (nums[i]==1 && nums[j] == 0){
                swap(nums[i++],nums[j--]);
            }else{
                if (nums[i] != 1){
                    i++;
                }
                if (nums[j] != 0){
                    j--;
                }
            }
        }
        
    }
    /*
     思路：定义两个指针，分别指向红球开始的地方(0)和蓝球开始的地方(nums.size()-1,这里蓝球是向下增长的)。
     
     依次遍历，如果当前是红球的话，那么把它放到红球部分的末尾。 如果当前是蓝球的话，也把它放到蓝球的末尾。这样，白色就到中间去了.
     */
    void sortColors2(vector<int>& nums) {
        if (nums.empty()) return;
        int i=0;
        int zero=0;
        int two=nums.size()-1;
        for (; i<=two; i++) {
            if (nums[i] == 0) {
                swap(nums[i], nums[zero++]);
            }else if(nums[i] == 2){
                swap(nums[i], nums[two--]);
                i--;//这里i--的意思是将2和某个元素交换以后，当前nums[i]还有可能也是红球.
            }
        }
    }
}
#endif /* sort_colors_hpp */
