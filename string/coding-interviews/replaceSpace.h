//
//  replaceSpace.h
//  string
//
//  Created by junlongj on 2019/8/3.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef replaceSpace_hpp
#define replaceSpace_hpp

#include <stdio.h>
/*
 剑指Offer(二)：替换空格
 请实现一个函数，将一个字符串中的每个空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

https://www.nowcoder.com/practice/4060ac7e3e404ad1a894ef3e17650423?tpId=13&tqId=11155&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 */
namespace codinginterviews{
    /*
     思路：将空格替换为%20，那么字符长度肯定会变长，为了不让下标变化，我们从后往前遍历。只要遇到空格，就将空格后面的字符整体x向后移动2个位置，这样就可以插入%20了》
     */
#pragma mark - 暴力法
    void replaceSpace(char *str,int length) {
        int i=length-1;
        while (i>=0) {
            if (str[i] == ' ') {
                //进行替换
                int j = length-1;
                for (; j>=i+1; j--) {
                    str[j+2]=str[j];
                }
                length+=2;
                str[j++] = '%';
                str[j++] = '2';
                str[j++] = '0';
                i--;
            }else{
                i--;
            }
        }
    }
    
#pragma mark - 优解
    void replaceSpace2(char *str,int length){
        /*
         上面的思路，每次遇到空格都会重复的移动大量数据。所以，我们可以提前计算好空格的个数，这样新的字符串的长度就知道了，那么一次移动就ok。
         */
        int count = 0;
        for (int i=0; i<length; i++) {
            if (str[i] == ' ') {
                count++;
            }
        }
        int newlen = length+count*2;
        for (int i=length-1,j=newlen-1; i>=0&&j>=0;) {//i指向老字符串的末尾，j指向新字符串的末尾
            if (str[i] == ' ') {
                str[j--] = '0';
                str[j--] = '2';
                str[j--] = '%';
                i--;
            }else{
                str[j--] = str[i--];
            }
        }
    }
    
    void test_replaceSpace(){
        char a[100] = "We Are Happy";
        replaceSpace2(a, 13);
        std::cout << "test_replaceSpace starting ......." << std::endl;
        std::cout << a << std::endl;
    }
}

#endif /* replaceSpace_hpp */
