//
//  zigzag_conversion.h
//  string
//
//  Created by junlongj on 2019/8/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef zigzag_conversion_hpp
#define zigzag_conversion_hpp

#include <stdio.h>
#include <string>
#include <vector>
/*
 */
using namespace std;
namespace leetcode {
    string convert(string s, int numRows) {
        if (s.empty() || numRows <= 1) return s;
        vector<vector<char>> result(numRows);
        int ctrow=0;
        int i=0;
        while(i<s.length()){
            //向下
            while(ctrow < numRows && i<s.length()){
                result[ctrow++].push_back(s[i++]);
            }
            ctrow--;ctrow--;//这里要退两行
            //斜上方
            while(ctrow >=0 && i<s.length()){
                result[ctrow--].push_back(s[i++]);
            }
            ctrow++;ctrow++;
        }
        string r;
        for(int i=0;i<result.size();i++){
            for(int j=0;j<result[i].size();j++){
                r+=result[i][j];
            }
        }
        return r;
    }
    
#pragma mark - 简化版
    /*
     相比上面的解法优化如下:
     
     1. vector里面存储的是每一行的结果.
     2. 通过stepdirection来控制运动方向，提取公共部分代码.
     */
    string convert2(string s, int numRows){
        if (s.empty() || numRows <= 1) return s;
        
        vector<string> result(numRows);
        int ctrow=0;
        int stepdirection = 1;
        for (int i=0; i<s.length(); i++) {
            //如果走到最后一行，向斜上方运动
            if(ctrow == numRows-1)
                stepdirection = -1;
            //如果运动到第一行，向正下方运动
            if (ctrow == 0)
                stepdirection = 1;
            
            result[ctrow]+=s[i];
            ctrow+=stepdirection;
        }
        
        string r;
        for (auto &str : result)
            r += str;
        return r;
    }
    void test_convert(){
        string s= "LEETCODEISHIRING";
        std::cout << convert(s, 4) << std::endl;//LDREOEIIECIHNTSG
    }
}
#endif /* zigzag_conversion_hpp */
