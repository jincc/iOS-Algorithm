//
//  addBinary.h
//  string
//
//  Created by junlongj on 2019/8/14.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef addBinary_hpp
#define addBinary_hpp

#include <stdio.h>
/*67.二进制求和
 给定两个二进制字符串，返回他们的和（用二进制表示）。
 
 输入为非空字符串且只包含数字 1 和 0。
 
 示例 1:
 
 输入: a = "11", b = "1"
 输出: "100"
 示例 2:
 
 输入: a = "1010", b = "1011"
 输出: "10101"
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/add-binary
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
namespace leetcode {
    //good
    //思路：从两字符串末尾开始遍历，如果碰到较短字符串左边界的话，那么取0继续运算》
    std::string addBinary(std::string a, std::string b){
        if (a.empty()||b.empty()) return "";
        int alen = a.length()-1;
        int blen = b.length()-1;
        int flag = 0;//表示进一位
        std::string result;
        while (alen >=0 || blen>=0){
            int a1= alen<0 ? 0 : a[alen]-'0';
            int b1= blen<0 ? 0 : b[blen]-'0';
            int c = a1+b1+flag;
            result = std::to_string(c%2) + result;
            flag = c/2;
            alen--;blen--;
        }
        if (flag)
            return "1"+result;
        return result;
    }
    
    //bad
    std::string addBinary2(std::string a, std::string b) {
        if (a.empty()||b.empty())return "";
        if (a.length()<b.length()){
            swap(a,b);
        }
        //a长b短
        int blen = b.length();
        int alen = a.length();
        for(int i=0;i<alen-blen;i++){
            b = "0"+ b;
        }
        int flag=0;
        std::string result;
        for(int i=alen-1;i>=0;i--){
            int n1=a[i]-'0';
            int n2=b[i]-'0';
            result = std::to_string((n1+n2+flag)%2) + result;
            flag = (n1+n2+flag)/2;
        }
        if (flag)
            result = "1" + result;
        return result;
    }
    
    void test_addBinary(){
        std::string s = "1";
        std::string s2 = "111";
        std::cout << "test_addBinary: " << addBinary(s, s2) << std::endl;
    }
}
#endif /* addBinary_hpp */
