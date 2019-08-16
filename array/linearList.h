//
//  linearList.h
//  ALG-DS
//
//  Created by junl on 2019/4/29.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef linearList_h
#define linearList_h

// 线性表抽象描述 base ADT
template <typename T>
class  linearList {
public:
    virtual ~linearList(){};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int index)  = 0;
    virtual int indexOf(const T& element) const = 0;
    virtual void earse(int index) = 0;
    virtual void insert(int index, const T& element) = 0;
};
#endif /* linearList_h */
