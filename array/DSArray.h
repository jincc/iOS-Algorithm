//
//  DSArray.hpp
//  ALG-DS
//
//  Created by junl on 2019/4/22.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef DSArray_hpp
#define DSArray_hpp
#include <iostream>
#include "DSIterator.h"
#include "linearList.h"
void testDSArray();

// 实现数组
template <typename T>
class arrayList : public linearList<T> {
protected:
    T *elements; //储存结构
    int arrayLength;//数组长度
    int capacity;//数组容量
    void checkIndex(int index) const;
    void resize(int size);
public:
    arrayList(int capacity = 2);
    arrayList(const arrayList& );
    //ADT
    bool empty() const {
        return arrayLength == 0;
    };
    int size() const {
        return arrayLength;
    };
    T& get(int index) ;
    int indexOf(const T& element) const;
    void earse(int index);
    void push_back(const T& element);
    void insert(int index, const T& element);
    /// 使数组的长度arrayLength等于capacity
    void trimToSize();
    /// 使线性表的长度=size
    void setSize(int size);
    void swap(arrayList<T>& other);
    /// 把数组容量修改为capacity
    void reserve(int capacity);
    /// 修改下标元素
    T& set(int index,const T& element);
    /// 清空数组
    void clear();
    void removeRange(int start ,int end);
    /// 返回指定元素出现的最后一个索引
    int lastIndexOf(const T& element);
    ~arrayList();
    void output() const;
    //返回迭代器,自定义迭代器以后，DSArray就能够使用STL里面的标准算法了.
    DSIterator<T> begin(){
        return DSIterator<T>(elements);
    };
    DSIterator<T> end(){
        return DSIterator<T>(elements+arrayLength);
    }
    //下标
    T& operator[](int index);
    //当且仅当所有元素相等时，才为真
    bool operator==(const arrayList<T>& other);
    bool operator!=(const arrayList<T>& other);
    bool operator<(const arrayList<T>& other);
    friend std::ostream& operator<< (std::ostream &out,  arrayList<T>& array);
};

template <typename T>
std::ostream& operator<< (std::ostream &out,  arrayList<T>& array);

#endif /* DSArray_hpp */
