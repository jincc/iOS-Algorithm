//
//  base.hpp
//  base
//
//  Created by junl on 2019/7/17.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef base_
#define base_

#include <stdio.h>
#include <stdio.h>
#include <string>
#include <sstream>
/* The classes below are exported */
#pragma GCC visibility push(default)
//#pragma GCC visibility push(hidden)
template <typename T>
//利用stringstream进行安全的类型转换
void to_string( std::string &result, const T& t){
    std::stringstream stream;
    stream << t;
    result = stream.str();
}
template<class out_type,class in_value>
out_type convert(const in_value & t){
    std::stringstream stream;
    stream<<t;//向流中传值
    out_type result;//这里存储转换结果
    stream>>result;//向result中写入值
    return result;
}

/// 创建二位数组
template <typename T>
void make2Array(T**& a,int row,int column) {
    a = new T* [row];//申请行
    for (int i=0; i<row; i++) {
        a[i] = new T[column];//为每一列申请q空间
    }
}
/// 删除二位数组
template <typename T>
void delete2Array(T**& a,int row,int column) {
    for (int i = 0; i<row ; i++) {
        delete [] a[i];
    }
    delete [] a;
    a = nullptr;
}
/// 改变二位数组长度
template <typename T>
void changeLength2Array(T**& a ,int oldrow,int oldcolumn,int row,int column) {
    T** newArray;
    make2Array(newArray, row, column);
    int minrow = std::min(oldrow, row);
    int mincolumn = std::min(oldcolumn, column);
    for (int i=0; i<minrow; i++) {
        for (int j=0; j<mincolumn; j++) {
            newArray[i][j] = a[i][j];
        }
    }
    a = newArray;
}
/// 创建一维数组
template <typename T>
void makearray(T*& a,int oldlen, int len) {
    T* arr = new T [len];
    std::copy(a, a+std::min(oldlen, len), arr);
    a = arr;
}

#pragma GCC visibility pop
#endif
