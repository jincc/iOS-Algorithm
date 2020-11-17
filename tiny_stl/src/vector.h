//
//  vector.h
//  tiny_stl
//
//  Created by junl on 2020/11/13.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef vector_h
#define vector_h
#include "allocator.h"
#include "iterator.h"
#include <algorithm>
#include <iostream>
namespace tiny{
/*
 @parameter T. Type of the elements.
 Only if T is guaranteed to not throw while moving, implementations can optimize to move elements instead of copying them during reallocations.
 Aliased as member type vector::value_type.
 
 @parameter Alloc. Type of the allocator object used to define the storage allocation model. By default, the allocator class template is used, which defines the simplest memory allocation model and is value-independent.
 Aliased as member type vector::allocator_type.
 */
template<class T>
class vector{
public:
    typedef T value_type;
    typedef tiny::allocator<T> allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef tiny::reverse_iterator<iterator> reverse_iterator;
    typedef tiny::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    
#pragma mark - 构造，拷贝，移动构造
    //Constructs an empty container, with no elements.
    explicit vector() : elements(nullptr), first_free(nullptr), cap(nullptr){};
    //Constructs a container with n elements. Each element is a copy of val (if provided).
    explicit vector(size_type n) {
        _construct_n(n, value_type());
    };
    vector(size_type n, const value_type &val) {
        _construct_n(n, val);
    };
    //Constructs a container with as many elements as the range [first,last), with each element emplace-constructed from its corresponding element in that range, in the same order.
    template <class _InputIterator, typename std::enable_if<
    tiny::is_input_iterator<_InputIterator>::value &&
    std::is_constructible<value_type, typename tiny::iterator_traits<_InputIterator>::reference>::value,
    int>::type = 0>
    vector(_InputIterator __first, _InputIterator __last){
                                     _construct(__first, __last);
                                 }
    //Constructs a container with a copy of each of the elements in x, in the same order.
    vector(const vector& x){
        _construct(x.begin(), x.end());
    }
    //Constructs a container that acquires the elements of x. If alloc is specified and is different from x's allocator, the elements are moved. Otherwise, no elements are constructed (their ownership is directly transferred). x is left in an unspecified but valid state.
    vector(vector &&x):elements(x.elements), first_free(x.first_free), cap(x.cap){
        x.elements =  x.first_free = x.cap = nullptr;
    };
    //Constructs a container with a copy of each of the elements in il, in the same order.
    vector(std::initializer_list<value_type> il){
        _construct(il.begin(), il.end());
    }
    //This calls allocator_traits::destroy on each of the contained elements, and deallocates all the storage capacity allocated by the vector using its allocator.
    ~vector() {
        _free();
    }
#pragma mark - operator=
    vector& operator=(const vector& x);
    vector& operator=(vector&& x);
    vector& operator=(std::initializer_list<value_type> il);
    
    iterator begin() noexcept {
        return static_cast<iterator>(elements);
    }
    const_iterator begin() const noexcept {
        return static_cast<const_iterator>(elements);
    }
    iterator end() noexcept {
        return static_cast<iterator>(first_free);
    }
    const_iterator end() const noexcept {
        return static_cast<const_iterator>(first_free);
    }
    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }
    const_iterator cbegin() const noexcept {
        return static_cast<const_iterator>(elements);
    }
    const_iterator cend() const noexcept {
        return static_cast<const_iterator>(first_free);
    }
    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(begin());
    }
    size_type size() const {
        return static_cast<size_type>(first_free - elements);
    }
//    size_type max_size() const noexcept;
    /*
     Resizes the container so that it contains n elements.
     
     If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
     
     If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
     
     If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
     
     Notice that this function changes the actual content of the container by inserting or erasing elements from it.
     */
    void resize (size_type n);
    void resize (size_type n, const value_type& val);
    size_type capacity() const noexcept {return static_cast<size_type>(cap - elements);};
    bool empty() const {return first_free == elements;};
    /*
     Requests that the vector capacity be at least enough to contain n elements.
     
     If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
     
     In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
     
     This function has no effect on the vector size and cannot alter its elements.

     */
    void reserve (size_type n);
    void shrink_to_fit();
    reference operator[] (size_type n) {return static_cast<reference>(elements[n]);};
    const_reference operator[] (size_type n) const {return static_cast<const_reference>(elements[n]);};
    reference at (size_type n) {
        check_index(n);
        return operator[](n);
    };
    const_reference at (size_type n) const{
        check_index(n);
        return operator[](n);
    }
    reference front() {
         check_index(0);
        return operator[](0);
    }
    const_reference front() const{
         check_index(0);
        return operator[](0);
    }
    reference back(){
         check_index(size() - 1);
        return operator[](size() - 1);
    }
    const_reference back() const{
        check_index(size() - 1);
        return operator[](size() - 1);
    }
    value_type* data() noexcept {
        return elements;
    }
    const value_type* data() const noexcept{
        return elements;
    }
    //Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
    template <class InputIterator,typename std::enable_if<
    tiny::is_input_iterator<InputIterator>::value &&
    std::is_constructible<value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,int>::type = 0>
    void assign (InputIterator first, InputIterator last);
    void assign (size_type n, const value_type& val);
    void assign (std::initializer_list<value_type> il);
    
    void push_back (const value_type& val);
    void pop_back();
    /*
     The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
     
     This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
     
     Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end causes the container to relocate all the elements that were after position to their new positions. This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).
     
     The parameters determine how many elements are inserted and to which values they are initialized:
     */
    iterator insert (const_iterator position, const value_type& val);
    iterator insert (const_iterator position, size_type n, const value_type& val);
    template <class InputIterator, typename std::enable_if<
                                    tiny::is_input_iterator<InputIterator>::value &&
                                    std::is_constructible<value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,int>::type = 0>
    iterator insert (const_iterator position, InputIterator first, InputIterator last);
    iterator insert (const_iterator position, value_type&& val);
    iterator insert (const_iterator position, std::initializer_list<value_type> il);
    
    iterator erase (const_iterator position);
    iterator erase (const_iterator first, const_iterator last);
    
    void swap (vector& x);
    template <class... Args>
    iterator emplace (const_iterator position, Args&&... args);
    template <class... Args>
    void emplace_back (Args&&... args);
    void clear();
private:
    void allocate(size_type n){
        try {
            first_free = elements = alloc.allocate(n);
            cap = elements + n;
        } catch (...) {
            first_free = elements = cap = nullptr;
        }
    }
    void _construct_n(size_type n, const value_type &val);
    
    template<class InputIterator, typename std::enable_if<
    tiny::is_input_iterator<InputIterator>::value &&
    std::is_constructible<typename vector<T>::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,int>::type = 0>
    void _construct(InputIterator first, InputIterator last);
    

    void _free();
    void _assign(size_type n);
    template<typename InputIterator>
    void _assign(InputIterator beg, InputIterator end);
    void _advance(size_type step = 1){
        first_free += step;
    }
    void check_index(size_type n) {
        if (n >= size()) throw std::out_of_range("index out of range");
    };
    void reallocate(size_type n);
    void check_reallocate();
    void check_reallocate(size_type min_size);
    value_type *elements;//start location
    value_type *first_free;//空闲位置
    value_type *cap;//容量位置
    static allocator_type alloc;
};

template<class T>
typename tiny::vector<T>::allocator_type tiny::vector<T>::alloc;
template<class T>
template<typename InputIterator>
void vector<T>::_assign(InputIterator _beg, InputIterator _end){
    size_type new_sz  = _end - _beg;
    if (new_sz > capacity()){
        _free();
        _construct(_beg, _end);
    }else{
        std::for_each(begin(), end(), [](T& p){
            alloc.destroy(&p);
        });
        std::uninitialized_copy(_beg, _end, begin());
        first_free  = begin() + new_sz;
    }
}
template<class T>
vector<T>& vector<T>::operator=(const vector& x){
    if (&x != this){
        _assign(x.begin(), x.end());
    }
    return *this;
}
template<class T>
vector<T>& vector<T>::operator=(vector&& x){
    if (&x != this){
        elements = x.elements;
        first_free = x.first_free;
        cap = x.cap;
        x.elements = x.first_free = x.cap = nullptr;
    }
    return *this;
}
template<class T>
vector<T>& vector<T>::operator=(std::initializer_list<value_type> il){
    _assign(il.begin(), il.end());
    return *this;
}
template<class T>
void vector<T>::_free(){
    std::for_each(begin(), end(), [](T& p){
        alloc.destroy(&p);
    });
    alloc.deallocate(elements, capacity());
    first_free = elements = cap = nullptr;
}

template<class T>
void vector<T>::reallocate(size_type n){
//    if (n <= capacity()) return;
    pointer newdata = alloc.allocate(n);
    pointer dst = newdata;
    pointer src = elements;
    size_type sz = std::min(size(), n);
    try {
        for (size_type i = 0; i < sz; i++) {
            alloc.construct(dst++, tiny::move(*src++));
        }
    } catch (...) {
        alloc.deallocate(newdata, n);
        throw;
    }
    alloc.deallocate(elements, capacity());
    elements = newdata;
    first_free = dst;
    cap = elements + n;
}
template<class T>
void vector<T>::check_reallocate(){
    check_reallocate(size()+1);
}
template<class T>
void vector<T>::check_reallocate(size_type sz){
    if (sz > capacity())
        reallocate(!sz ? 1 : 2 * sz);
}
template<class T>
void vector<T>::resize(size_type n){
    resize(n, value_type());
}
template<class T>
void vector<T>::resize(size_type n, const value_type& val){
    if (n > capacity()) {
        reallocate(n);
    }
    size_type ct_sz = size();
    if (n > ct_sz){
        //在末尾添加剩余元素
        for (size_type i = ct_sz; i <= n; i++) {
            alloc.construct(first_free++, val);
        }
    }else if (n < ct_sz){
        //销毁多余元素
        for(size_type i = n; i < ct_sz; i++){
            alloc.destroy(--first_free);
        }
    }
}
template<class T>
void vector<T>::reserve (size_type n){
    if (n > capacity())
        reallocate(n);
}
template<class T>
void vector<T>::shrink_to_fit(){
    reallocate(size());
}
template<class T>
void vector<T>::_assign(size_type sz){
    if (sz > capacity()) {
        _free();
        allocate(sz);
    }else{
        erase(begin(), end());
//        first_free = elements;
    }
}
template<class T>
template<class InputIterator, typename std::enable_if<
                             tiny::is_input_iterator<InputIterator>::value &&
                            std::is_constructible<typename vector<T>::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,int>::type>
void vector<T>::_construct(InputIterator first, InputIterator last){
    size_type n = last - first;
    allocate(n);
    for (; n--; ) {
        alloc.construct(first_free++, *first++);
    }
}
template<class T>
void vector<T>::_construct_n(size_type n, const value_type &val){
    allocate(n);
    for (size_type i = 0; i < n ; i++) {
        alloc.construct(first_free++, val);
    }
}
template<class T>
template<class InputIterator,typename std::enable_if<
tiny::is_input_iterator<InputIterator>::value &&
std::is_constructible<typename vector<T>::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,int>::type>
void vector<T>::assign(InputIterator first, InputIterator last){
    size_type sz = last - first;
    _assign(sz);
    for (; first != last; first++) {
        alloc.construct(first_free++, *first);
    }
}
template<class T>
void vector<T>::clear(){
    auto it = begin();
    for (; it != end(); it++) {
        alloc.destroy(&*it);
    }
    first_free = elements;
}
template<class T>
void vector<T>::assign (size_type n, const value_type& val){
    _assign(n);
    for (size_type i = 0; i < n; i++) {
        alloc.construct(first_free++, val);
    }
}
template<class T>
void vector<T>::assign (std::initializer_list<value_type> il){
    assign(il.begin(), il.end());
}
    
template<class T>
void vector<T>::push_back (const value_type& val){
    check_reallocate();
    alloc.construct(first_free++, val);
}
template<class T>
void vector<T>::pop_back(){
    if (empty()) throw std::out_of_range("pop from empty vector");
    alloc.destroy(--first_free);
}
    
//inset
template<class T>
typename vector<T>::iterator
vector<T>::insert (const_iterator position, const value_type& val){
    difference_type diff = position - cbegin();
    check_reallocate();
    position = cbegin() + diff;
    if (position == cend()) {
        push_back(val);
    }else{
        auto it = end();
        _advance();
        while (it != position) {
            *it = tiny::move(*(it-1));
            --it;
        }
        *it = val;
    }
    return const_cast<iterator>(position);
}
template<class T>
typename vector<T>::iterator
vector<T>::insert (const_iterator position, size_type n, const value_type& val){
    difference_type diff = position - cbegin();
    check_reallocate(size()+n);
    position = cbegin() + diff;
    if (position == cend()) {
        while (n--) {
            push_back(val);
        }
    }else{
        auto it = end()+n-1;
        _advance(n);
        while ((it-position) != n-1) {
            *it = tiny::move(*(it-n));
            --it;
        }
        while (n--) {
            *it-- = val;
        }
    }
    return const_cast<iterator>(position);
}
template<class T>
template <class InputIterator, typename std::enable_if<
tiny::is_input_iterator<InputIterator>::value &&
std::is_constructible<typename vector<T>::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,int>::type>
typename vector<T>::iterator
vector<T>::insert (const_iterator position, InputIterator first, InputIterator last){
    size_type n = last - first;
    difference_type diff = position - cbegin();
    check_reallocate(size()+n);
    position = cbegin() + diff;
    if (position == cend()) {
        while (first != last) {
            push_back(*first++);
        }
    }else{
        auto it = end()+n-1;
        _advance(n);
        while ((it-position) != n-1) {
            *it = tiny::move(*(it-n));
            --it;
        }
        while (n--) {
            *it-- = *--last;
        }
    }
    return const_cast<iterator>(position);
}
template<class T>
typename vector<T>::iterator
vector<T>::insert (const_iterator position, value_type&& val){
    difference_type diff = position - cbegin();
    check_reallocate();
    position = cbegin() + diff;
    if (position == cend()) {
        push_back(val);
    }else{
        auto it = end();
        _advance();
        while (it != position) {
            *it = tiny::move(*(it-1));
            --it;
        }
        *it = val;
    }
    return const_cast<iterator>(position);
}

template<class T>
typename vector<T>::iterator
vector<T>::insert (const_iterator position, std::initializer_list<value_type> il){
    return insert(position, il.begin(), il.end());
}
    
template<class T>
typename vector<T>::iterator
vector<T>:: erase (const_iterator first, const_iterator last){
    if (last == end()) {
        while (first != last) {
            alloc.destroy(first++);
        }
        first_free = static_cast<value_type *>(const_cast<iterator>(first));
        return end();
    }else{
        iterator f = const_cast<iterator>(first);
        iterator e = const_cast<iterator>(last);
        while (end() != e) {
            //释放之前
            //保存之后
            alloc.destroy(f);
            *f++ = *e++;
        }
        first_free -= last - first;
        return const_cast<iterator>(first);
    }
}
    
template<class T>
typename vector<T>::iterator
vector<T>:: erase (const_iterator first){
    return erase(first, first+1);
}
    
template<class T>
void vector<T>::swap (vector& x){
    using std::swap;
    swap(elements, x.elements);
    swap(first_free,x.first_free);
    swap(cap, x.cap);
}
template<class T>
void swap(vector<T> &lhs, vector<T> &rhs){
    lhs.swap(rhs);
}
    
template<class T>
template <class... Args>
void vector<T>::emplace_back (Args&&... args){
    check_reallocate();
    alloc.construct(first_free++, tiny::forward<Args>(args)...);
}
template<class T>
template <class... Args>
typename vector<T>::iterator
vector<T>::emplace (const_iterator position, Args&&... args){
    return insert(position, T(tiny::forward<Args>(args)...));
}

template <class T>
bool operator== (const vector<T>& lhs, const vector<T>& rhs){
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T>
bool operator!= (const vector<T>& lhs, const vector<T>& rhs){
    return !operator==(lhs, rhs);
}

template <class T>
bool operator<  (const vector<T>& lhs, const vector<T>& rhs){
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::less<T>());
}

template <class T>
bool operator<= (const vector<T>& lhs, const vector<T>& rhs){
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::less_equal<T>());
}

template <class T>
    bool operator>  (const vector<T>& lhs, const vector<T>& rhs){
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::greater<T>());

    }

template <class T>
    bool operator>= (const vector<T>& lhs, const vector<T>& rhs){
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::greater_equal<T>());
    }
    
template<class T>
std::ostream& operator<<(std::ostream &os, vector<T> &vec){
    auto it = vec.begin();
    while (it != vec.end()) {
        os << *it++ << " ";
    }
    os << std::endl;
    return os;
}
}

#endif /* vector_h */
