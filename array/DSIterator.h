//
//  DSIterator.hpp
//  ALG-DS
//
//  Created by junl on 2019/4/23.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef DSIterator_hpp
#define DSIterator_hpp
#include <iterator>


/**
 * @brief 自定义一个双向的迭代器. 需要实现向前迭代，前后迭代. 也就是说需要实现*,->,++,++(int),--,--(int),!=,==
 */
template <typename _Iter>
class DSIterator {
public:
    typedef  std::bidirectional_iterator_tag iterator_category;
    typedef _Iter       value_type;
    typedef std::ptrdiff_t difference_type;
    typedef _Iter*       pointer;
    typedef _Iter&       reference;
    DSIterator(_Iter* thePosition=0):position(thePosition){}
    //解引用
    _Iter& operator*(){
        return *position;
    }
    _Iter* operator->(){
        return &*position;
    }
    //例如++a
    DSIterator& operator++() {
        ++position;
        //this指向的是DSIterator<_Iter>,*this才是DSIterator<_Iter>
        return *this;
    }
    //例如a++
    DSIterator  operator++(int) {
        DSIterator __tmp(*this);
        ++position;
        return __tmp;
    }
    DSIterator& operator--() {
        --position;
        return *this;}
    DSIterator  operator--(int) {
        DSIterator __tmp(*this);
        --position;
        return __tmp;}
    
    bool operator==(const DSIterator& other){
        return position == other.position;
    }
    bool operator!=(const DSIterator& other){
        return position != other.position;
    }
protected:
    _Iter* position;//指向数组里的元素
};


#endif /* DSIterator_hpp */
