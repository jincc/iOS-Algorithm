//
//  maxArea.h
//  array
//
//  Created by junl on 2019/7/26.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef maxArea_hpp
#define maxArea_hpp

#include <stdio.h>
#include <vector>
/*
 11. 给定 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
 
 说明：你不能倾斜容器，且 n 的值至少为 2。
 
 
 
 图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
 
  
 
 示例:
 
 输入: [1,8,6,2,5,4,8,3,7]
 输出: 49
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/container-with-most-water
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

#pragma mark - 方法一:双指针前后移动
int maxArea(const std::vector<int>& height) {
    //1,2,4,3
    //0,1,2,3
    if (height.size() <= 1) {
        return 0;
    }
    int  maxarea=0;
    size_t i=0;
    size_t j=height.size()-1;
    while (i < j) {
        int  area =  static_cast<int>((j - i) * std::min(height[i], height[j]));
        maxarea = std::max(maxarea, area);
        // 区域的面积实际上是由最短的一条边决定的，因此我们想要增加增大面积其实就是要增加最短边的值。
        // height[i] < height[j] ? i++ : j--;
        // 高效的方式
        if (height[i] < height[j]) {
            do{
                i++;
            } while (i< j && height[i-1] >= height[i]) ; //找到比左边那条边大的
        }else{
            do{
                j--;
            }while (i < j && height[j] <= height[j+1]);
        }
    }
    return maxarea;
}

#endif /* maxArea_hpp */
