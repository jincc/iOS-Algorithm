//
//  integer_to_roman.h
//  string
//
//  Created by junlongj on 2019/8/19.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef integer_to_roman_hpp
#define integer_to_roman_hpp

#include <stdio.h>
/*
 12.整数转罗马数字
 罗马数字包含以下七种字符： I， V， X， L，C，D 和 M。
 
 字符          数值
 I             1
 V             5
 X             10
 L             50
 C             100
 D             500
 M             1000
 例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。
 
 通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：
 
 I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
 X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
 C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
 给定一个整数，将其转为罗马数字。输入确保在 1 到 3999 的范围内。
 
 
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/integer-to-roman
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    //思路：贪心思想，先按照所有可能出现的字符组合按照金币大小排序，然后按照贪心的思想先消费掉大的，在使用小的。
    std::string intToRoman(int num) {
        std::string symbols[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        int values[] =     {1000,900,500,400, 100, 90,  50, 40, 10,  9  , 5 , 4  , 1};
        std::string result;
        for(int i=0;i<sizeof(values)/sizeof(int) && num != 0;){
            if (num >= values[i]){
                num -= values[i];
                result += symbols[i];
            }else{
                i++;
            }
        }
        return result;
    }
    //思路:
    std::string intToRoman2(int num) {
        std::string result;
        int a1=num/1000;
        while(a1>0){
            result+='M';
            a1--;
        }
        num = num%1000;
        int units[3] = {100,10,1};
        char cs[3] = {'C','X','I'};
        char cs2[3] = {'D','L','V'};
        char cs3[3] = {'M','C','X'};//c1表示100,c2表示500,c3表示1000
        //计算X00,X0,X的逻辑步骤是一样的,提取功能代码
        for (int i=0;i<3;i++){
            a1=num/units[i];
            num%=units[i];
            if (a1 == 4){
                result = result + cs[i] + cs2[i];
            }else if (a1 == 9){
                result = result + cs[i] + cs3[i];
            }else{
                //a1 < 3 || a1>5
                while(a1>0){
                    if (a1>=5){
                        a1-=5;
                        result+=cs2[i];
                    }else{
                        a1--;
                        result+=cs[i];
                    }
                }
            }
        }
        return result;
    }
}
#endif /* integer_to_roman_hpp */
