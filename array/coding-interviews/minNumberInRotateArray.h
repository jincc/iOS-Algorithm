//
//  minNumberInRotateArray.h
//  array
//
//  Created by junlongj on 2019/8/3.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef minNumberInRotateArray_hpp
#define minNumberInRotateArray_hpp

#include <stdio.h>
#include <vector>
/*
 剑指Offer（六）：旋转数组的最小数字
 
 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。 输入一个非减排序的数组的一个旋转，输出旋转数组的最小元素。 例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。 NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。

 https://www.nowcoder.com/practice/9f3231a991af4f55b95579b44b7a01ba?tpId=13&tqId=11159&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */


namespace codinginterviews {
    int minNumberInRotateArray(std::vector<int> rotateArray) {
        if (rotateArray.size() == 0) {
            return 0;
        }
        int start=0;
        int end = rotateArray.size()-1;
        while (start <= end) {
            int mid = start + (end-start)/2;
//            if (mid == rotateArray.size() - 1) {
//                return std::min(rotateArray[mid], rotateArray[start]);
//            }
//            if (mid == 0) {
//                return std::min(rotateArray[mid], rotateArray[end]);
//            }
            if (rotateArray[mid] < rotateArray[mid-1]) {
                return rotateArray[mid];
            }
            //注意这里的判断条件，正常排序数组，应该中间节点小于为尾节点的值
            if (rotateArray[mid] > rotateArray[end]) {
                start=mid+1;
            }else
            {
                end=mid-1;
            }
        }
        return -1;
    }
    
    void test_minNumberInRotateArray(){
        std::vector<int> v{1,2,4,5,0};
        std::cout << "test_minNumberInRotateArray starting......" << std::endl;
        std::cout << minNumberInRotateArray(v) << std::endl;
    }
}
#endif /* minNumberInRotateArray_hpp */
