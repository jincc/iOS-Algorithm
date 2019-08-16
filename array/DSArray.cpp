//
//  DSArray.cpp
//  ALG-DS
//
//  Created by junl on 2019/4/22.
//  Copyright © 2019 junl. All rights reserved.
//

#include "DSArray.h"
#include <iostream>
#include <sstream>
#include "illegalParameterValue.h"
#include <algorithm>
#include <vector>
#include "base.h"
using namespace std;

template <typename T>
arrayList<T>::arrayList(int capacity) {
    if (capacity < 1) {
        ostringstream ss;
        ss << "Ininital capacity = " << capacity << " Must be > 0";
        throw illegalParameterValue(ss.str());
    }
    this->capacity = capacity;
    this->arrayLength = 0;
    this->elements = new T[capacity];
}


template <typename T>
arrayList<T>::arrayList(const arrayList& other){
    capacity = other.capacity;
    arrayLength = other.arrayLength;
    elements = new T[capacity];
    copy(other.elements, other.elements+arrayLength, elements);
}

template <typename T>
arrayList<T>::~arrayList<T>(){
    delete [] elements;
}

template <typename T>
void arrayList<T>::trimToSize(){
    if (arrayLength == capacity) {
        return;
    }
    //重新创建新数组
    makearray(elements, arrayLength, arrayLength);
    capacity = arrayLength;
}

template <typename T>
void arrayList<T>::setSize(int size) {
    makearray(elements, arrayLength, size);
    arrayLength = size;
    if (capacity < size) {
        capacity = size;
    }
}

template <typename T>
T& arrayList<T>::set(int index, const T &element) {
    checkIndex(index);
    T& value = elements[index];
    elements[index] = element;
    return value;
}


template <typename T>
T& arrayList<T>::operator[](int index){
    checkIndex(index);
    return elements[index];
}
template <typename T>
bool arrayList<T>::operator==(const arrayList<T> &other){
   return  equal(elements, elements+arrayLength, other.elements, other.elements+other.arrayLength);
}

template <typename T>
bool arrayList<T>::operator!=(const arrayList<T> &other){
    return  !(*this == other);
}

template <typename T>
bool arrayList<T>::operator<(const arrayList<T> &other){
    return  lexicographical_compare(elements, elements+arrayLength, other.elements, other.elements+other.arrayLength);
}

template <typename T>
void arrayList<T>::checkIndex(int index) const {
    if (index < 0|| index >= arrayLength ) {
        throw illegalParameterValue("index is invalid");
    }
}

template <typename T>
T& arrayList<T>::get(int index)  {
    checkIndex(index);
    return elements[index];
}

template <typename T>
int arrayList<T>::indexOf(const T& element) const {
    int index = (int)(find(elements, elements+arrayLength, element) - elements);
    if (index == arrayLength) {
        return -1;
    }
    return index;
}

template <typename T>
void arrayList<T>::resize(int size) {
    T* newArray = new T[size];
    int minLength = min(size, arrayLength);
    copy(elements, elements+minLength, newArray);
    elements = newArray;
    capacity = size;
}

template <typename T>
void arrayList<T>::reserve(int thecapacity) {
    if (thecapacity < capacity) {
        return;
    }
    resize(thecapacity);
}

template <typename T>
void arrayList<T>::clear() {
    elements = new T[1];
    arrayLength = 1;
    capacity = 1;
}

template <typename T>
void arrayList<T>::removeRange(int start, int end) {
    if (start <0 || end > arrayLength ) {
        return;
    }
    if (start > end) {
        return;
    }
    copy(elements+end, elements+arrayLength, elements+start);
    
    int newsize = arrayLength - end + start;
    
    //释放数组末尾无效的空间
    for (int i = newsize; i<arrayLength; i++) {
        elements[i].~T();
    }
    arrayLength = newsize;
}
template <typename T>
int arrayList<T>::lastIndexOf(const T &element){
    int index = -1;
    for (int i = 0; i<arrayLength; i++) {
        if (elements[i] == element) {
            index = i;
        }
    }
    return index;
}

template <typename T>
void arrayList<T>::earse(int index) {
    checkIndex(index);
    //当数组无用空间过多时m，修改内部数组长度
    if (arrayLength < capacity / 4) {
        resize(capacity/2);
    }
    copy(elements+index+1, elements+arrayLength, elements+index);
    arrayLength--;
}

template <typename T>
void arrayList<T>::swap(arrayList<T> &other) {
    std::__1::swap(this->elements, other.elements);
    std::__1::swap(this->capacity, other.capacity);
    std::__1::swap(this->arrayLength, other.arrayLength);
}


template <typename T>
void arrayList<T>::insert(int index, const T& element) {
    if (index < 0|| index > arrayLength ) {
        throw illegalParameterValue("index is invalid");
    }
    //数组满了需要重新分配
    if (capacity == arrayLength) {
        resize(arrayLength*2);
    }
    //copy_backward从最后一个元素开始拷贝
    copy_backward(elements+index, elements+arrayLength, elements+arrayLength+1);
    elements[index] = element;
    arrayLength++;
}

template <typename T>
void arrayList<T>::push_back(const T& element) {
    if (arrayLength == capacity) {
        resize(arrayLength*2);
    }
    elements[arrayLength] = element;
    arrayLength++;
}

template <typename T>
void arrayList<T>::output() const{
    copy(elements, elements+arrayLength, ostream_iterator<T>(cout,","));
}

template <typename T>
std::ostream& operator<< (std::ostream &out, const arrayList<T>& array){
    array.output();
    return out;
}

void testDSArray(){
    
    cout << "testDSArray" << endl;
    typedef int TYPE;
    arrayList<TYPE> array;
    array.trimToSize();
    array.push_back(0);
    array.push_back(1);
    array.push_back(2);
    cout << array[2] << endl;
    array.setSize(2);
    array.output();
    array.insert(0, -2);
    array.insert(0, -1);
    
    cout << "empty: " << array.empty() << ",size: " << array.size();
    cout << "indexOf0: "<< array.indexOf(0) << array.indexOf(1);
    cout << "get: " << array.get(0) << endl;
    array.earse(1);
    array.output();
    
    copy(array.begin(), array.end(), ostream_iterator<TYPE>(cout,","));

    arrayList<TYPE> array2;
    arrayList<TYPE> array3;
    array2.push_back(0);
    array2.push_back(1);
    array3.push_back(1);
    array3.push_back(1);
    array2.swap(array3);
    array2.reserve(100);
    array2.set(1, 100);
    cout << "set: " << array2[1] << endl;
    cout << "operator== : "<< (array2 != array3) << endl;
}

