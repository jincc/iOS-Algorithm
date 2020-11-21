//
//  list.h
//  tiny_stl
//
//  Created by junl on 2020/11/15.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef list_hpp
#define list_hpp
#include "allocator.h"
#include "iterator.h"
#include "util.h"
#include "alg.h"
#include <stdio.h>
#include <cassert>
namespace tiny{
template<class T>
class list_node_base;
template<class T>
class list_node;
//节点
template<class T>
class list_traits{
public:
    typedef list_node_base<T>* base_ptr;
    typedef list_node<T>* node_ptr;
};

//用于创建头结点，不含包element
template<class T>
class list_node_base{
public:
    typedef typename list_traits<T>::base_ptr base_ptr;
    typedef typename list_traits<T>::node_ptr node_ptr;
    list_node_base *pre;
    list_node_base *next;
    
    base_ptr as_base()  {
        return static_cast<base_ptr>(&*this);
    }
    node_ptr as_node()  {
        return static_cast<node_ptr>(&*this);
    }
    void unlink() {
        pre = next = as_base();
    }
    ~list_node_base() = default;
};
template<class T>
class list_node : public list_node_base<T>{
public:
    typedef typename list_traits<T>::base_ptr base_ptr;
    typedef typename list_traits<T>::node_ptr node_ptr;
    list_node(const T &val):element(val){}
    node_ptr as_node()  {
        return static_cast<node_ptr>(&*this);
    }
    base_ptr as_base()  {
        return static_cast<base_ptr>(&*this);
    }
    T element;
};


template<class T>
class list_iterator : public tiny::iterator<tiny::bidirectional_iterator_tag, T>{
public:
    typedef typename list_traits<T>::base_ptr base_ptr;
    typedef typename list_traits<T>::node_ptr node_ptr;
    typedef list_iterator<T> self_type;
    typedef ptrdiff_t            difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    list_iterator(const base_ptr &ptr):cur(ptr){}
    bool operator==(const list_iterator &rhs){
        return cur == rhs.cur;
    }
    bool operator!=(const list_iterator &rhs){
        return !operator==(rhs);
    }
    reference operator*() {
        return cur->as_node()->element;
    }
    pointer operator->(){
        return &(operator*());
    }
    self_type& operator++() {
        assert(cur != nullptr);
        cur = cur->next;
        return *this;
    }
    self_type operator++(int) {
        self_type tmp(*this);
        operator++();
        return tmp;
    }
    self_type& operator--(){
        assert(cur != nullptr);
        cur = cur->pre;
        return *this;
    }
    self_type operator--(int){
        self_type tmp(*this);
        operator--();
        return tmp;
    }
    base_ptr getPtr() {
        return cur;
    }
    self_type operator+(int a){
        self_type tmp(*this);
        while (a--) {
            tmp.operator++();
        }
        return tmp;
    }
private:
    base_ptr cur;
};

template<class T>
class list_const_iterator : public tiny::iterator<tiny::bidirectional_iterator_tag, T>{
public:
    typedef typename list_traits<T>::base_ptr base_ptr;
    typedef typename list_traits<T>::node_ptr node_ptr;
    typedef list_const_iterator<T> self_type;
    typedef ptrdiff_t            difference_type;
    typedef const T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    list_const_iterator(const base_ptr &ptr):cur(ptr){}
    bool operator==(const list_const_iterator &rhs){
        return cur == rhs.cur;
    }
    bool operator!=(const list_const_iterator &rhs){
        return !operator==(rhs);
    }
    reference operator*() {
        return cur->as_node()->element;
    }
    pointer operator->(){
        return &(operator*());
    }
    self_type& operator++() {
        assert(cur != nullptr);
        cur = cur->next;
        return *this;
    }
    self_type operator++(int) {
        self_type tmp(*this);
        operator++();
        return tmp;
    }
    self_type& operator--(){
        assert(cur != nullptr);
        cur = cur->pre;
        return *this;
    }
    self_type operator--(int){
        self_type tmp(*this);
        operator--();
        return tmp;
    }
    base_ptr getPtr() {
        return cur;
    }
    self_type operator+(int a){
        self_type tmp(*this);
        while (a--) {
            tmp.operator++();
        }
        return tmp;
    }
private:
    base_ptr cur;
};

template<class T>
class list{
public:
    typedef T value_type;
    typedef tiny::allocator<T> data_allocator_type;
    typedef tiny::allocator<list_node_base<T>> basenode_allocator_type;
    typedef tiny::allocator<list_node<T>> node_allocator_type;
    typedef typename data_allocator_type::reference reference;
    typedef typename data_allocator_type::const_reference const_reference;
    typedef typename data_allocator_type::pointer pointer;
    typedef typename data_allocator_type::const_pointer const_pointer;
    typedef typename data_allocator_type::difference_type difference_type;
    typedef typename data_allocator_type::size_type size_type;
    
    typedef list_iterator<value_type> iterator;
    typedef list_const_iterator<value_type> const_iterator;
    typedef tiny::reverse_iterator<iterator> reverse_iterator;
    typedef tiny::reverse_iterator<const_iterator> const_reverse_iterator;
    
    typedef typename list_traits<T>::base_ptr base_ptr;
    typedef typename list_traits<T>::node_ptr node_ptr;
    
    //Constructs move copy
    list();
    explicit list(size_type n);
    list(size_type n, const value_type &val);
    //fill
    template<class InputIterator, typename std::enable_if<
                            tiny::is_input_iterator<InputIterator>::value &&
                            std::is_constructible<value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                                int>::type = 0>
    list(InputIterator first, InputIterator last);
    //copy
    list(const list &x);
    //move
    list(list &&x);
    //initializer list
    list(std::initializer_list<value_type> il);
    //destructor
    //This calls allocator_traits::destroy on each of the contained elements, and deallocates all the storage capacity allocated by the list container using its allocator.
    ~list();
    
    //operator=
    //Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
    list& operator=(const list& x);
    list& operator=(list &&x);
    list& operator=(std::initializer_list<value_type> il);
    
    //Iterators
    iterator begin() noexcept {
        return iterator(_head());
    }
    const_iterator begin() const noexcept{
        return const_iterator(_head());
    }
    iterator end() noexcept{
        return iterator(_tail);
    }
    const_iterator end() const noexcept {
        return const_iterator(_tail);
    }
    reverse_iterator rbegin(){
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const{
        return const_reverse_iterator(end());
    }
    reverse_iterator rend() noexcept{
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const noexcept{
        return const_reverse_iterator(begin());
    }
    const_iterator cbegin() const noexcept{
        return const_iterator(_head());
    }
    const_iterator cend() const noexcept{
        return const_iterator(_tail);
    }
    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator crend() const noexcept{
        return const_reverse_iterator(begin());
    }
    
    //capacity
    bool empty() const noexcept {
        return _size == 0;
    }
    size_type size() const noexcept {
        return _size;
    }

    //Element access:
    reference front() {
        if (empty()) throw std::out_of_range("front out of range");
        return *begin();
    };
    const_reference front() const{
        if (empty()) throw std::out_of_range("front out of range");
        return *begin();
    }
    reference back() {
        if (empty()) throw std::out_of_range("back out of range");
        return _tail->pre->as_node()->element;
    }
    const_reference back() const {
        if (empty()) throw std::out_of_range("back out of range");
        return _tail->pre->element;
    }
    //Modifiers
    //Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
    template <class InputIterator,typename std::enable_if<
                                tiny::is_input_iterator<InputIterator>::value &&
                                std::is_constructible<value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,int>::type = 0>
    void assign (InputIterator first, InputIterator last);
    void assign (size_type n, const value_type& val);
    void assign (std::initializer_list<value_type> il);
    
    /*
     Inserts a new element at the beginning of the list, right before its current first element. This new element is constructed in place using args as the arguments for its construction.
     
     This effectively increases the container size by one.
     
     The element is constructed in-place by calling allocator_traits::construct with args forwarded.
     
     A similar member function exists, push_front, which either copies or moves an existing object into the container.
     */
    template <class... Args>
    void emplace_front (Args&&... args);
    /*
     Inserts a new element at the beginning of the list, right before its current first element. The content of val is copied (or moved) to the inserted element.
     
     This effectively increases the container size by one.
     */
    void push_front(const value_type &val);
    void push_front(value_type&& val);
    void pop_front();
    
    template <class... Args>
    void emplace_back (Args&&... args);
    void push_back(const value_type& val);
    void push_back(value_type&& val);
    void pop_back();
    /*
     The container is extended by inserting a new element at position. This new element is constructed in place using args as the arguments for its construction.
     
     This effectively increases the container size by one.
     
     Unlike other standard sequence containers, list and forward_list objects are specifically designed to be efficient inserting and removing elements in any position, even in the middle of the sequence.

     */
    template<class... Args>
    iterator emplace(const_iterator position, Args&&... args);
    
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

    void swap(list &x);
    
    void resize(size_type n);
    void resize(size_type n, const value_type& val);
    void clear();
    /*
     This effectively inserts those elements into the container and removes them from x, altering the sizes of both containers. The operation does not involve the construction or destruction of any element. They are transferred, no matter whether x is an lvalue or an rvalue, or whether the value_type supports move-construction or not.
     */
    void splice (const_iterator position, list& x);
    void splice (const_iterator position, list&& x);
    void splice (const_iterator position, list& x, const_iterator i);
    void splice (const_iterator position, list&& x, const_iterator i);
    void splice (const_iterator position, list& x,
                 const_iterator first, const_iterator last);
    void splice (const_iterator position, list&& x,
                 const_iterator first, const_iterator last);
    
    void remove (const value_type& val);
    template <class Predicate>
    void remove_if (Predicate pred);
    /*
     The version with no parameters (1), removes all but the first element from every consecutive group of equal elements in the container.

     Notice that an element is only removed from the list container if it compares
     */
    void unique();
    template <class BinaryPredicate>
    void unique (BinaryPredicate binary_pred);
    
    void merge (list& x);
    void merge (list&& x);
    template <class Compare>
    void merge (list& x, Compare comp);
    template <class Compare>
    void merge (list&& x, Compare comp);
    void sort();
    template <class Compare>
    void sort (Compare comp);
    void reverse() noexcept;
    
private:
    base_ptr _tail = nullptr;//尾结点指针
    size_type _size = 0;
    static data_allocator_type data_allocator;
    static basenode_allocator_type basenode_allocator;
    static node_allocator_type node_allocator;
    base_ptr _head() const {
        return _tail->next;
    }
    void _createTail();
    void _construct(size_type n, const value_type& val);
    template<class InputIterator, typename std::enable_if<
                            tiny::is_input_iterator<InputIterator>::value &&
                            std::is_constructible<typename list<T>::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                                int>::type = 0>
    void _construct(InputIterator first, InputIterator last);
    //复用之前的内存
    template<class InputIterator, typename std::enable_if<
                            tiny::is_input_iterator<InputIterator>::value &&
                            std::is_constructible<typename list<T>::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                                int>::type = 0>
    void _assign_range(InputIterator first, InputIterator last);
    template <class... Args>
    base_ptr _createNode (Args&&... args);
    void _link_to_tail(base_ptr first);
    void _link_to_head(base_ptr first);
    //[first, last)
    void _link_to_tail(base_ptr first, base_ptr last);
    //[first, last]
    iterator _link_nodes(base_ptr pos, base_ptr first, base_ptr last);
    //[first ,last]
    void _unlink(base_ptr first, base_ptr last);
    iterator _erase_nofree(const_iterator first, const_iterator last);
    void _free_elements();
    void _destory_node(base_ptr node);
    template <class Compare>
    const_iterator _sort(const_iterator first, const_iterator last, size_type n, Compare cmp);
    
};

template <class T>
typename list<T>::data_allocator_type
list<T>::data_allocator;

template <class T>
typename list<T>::basenode_allocator_type
list<T>::basenode_allocator;

template <class T>
typename list<T>::node_allocator_type
list<T>::node_allocator;

//private
template<class T>
void list<T>::_createTail(){
    _tail = basenode_allocator.allocate(1);
    basenode_allocator.construct(_tail);
    _tail->unlink();
}

template<class T>
template<class... Args>
typename list<T>::base_ptr
list<T>::_createNode (Args&&... args){
    node_ptr ret = node_allocator.allocate(1);
    data_allocator.construct(&(ret->element), tiny::forward<Args>(args)...);
    ret->unlink();
    return ret->as_base();
}

template<class T>
void list<T>::_link_to_tail(base_ptr first){
    _tail->pre->next= first;
    first->pre = _tail->pre;
    first->next = _tail;
    _tail->pre = first;
}

template<class T>
void list<T>::_link_to_tail(base_ptr first, base_ptr last){
    _tail->pre->next= first;
    first->pre = _tail->pre;
    last->pre->next = _tail;
    _tail->pre = last->pre;
}

template<class T>
void list<T>::_link_to_head(base_ptr node){
    base_ptr head = _head();
    node->next = head;
    head->pre = node;
    _tail->next = node;
    node->pre = _tail;
}
    
template <class T>
typename list<T>::iterator
list<T>::_link_nodes(base_ptr pos, base_ptr first, base_ptr last)
{
  pos->pre->next = first;
  first->pre = pos->pre;
  pos->pre = last;
  last->next = pos;
  return iterator(pos);
}

template<class T>
void list<T>::_unlink(base_ptr first, base_ptr last){
    first->pre->next = last->next;
    last->next->pre = first->pre;
}
template<class T>
void list<T>::_construct(size_type n, const value_type& val){
    _createTail();
    for (; n--; ) {
        //create node
        auto node = _createNode(val);
        //link
        _link_to_tail(node->as_base());
    }
}

template<class T>
template<class InputIterator, typename std::enable_if<
                        tiny::is_input_iterator<InputIterator>::value &&
                        std::is_constructible<typename list<T>::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                            int>::type>
void list<T>::_assign_range(InputIterator first, InputIterator last){
    auto b = begin(), e = end();
    for (; b != e && first != last; b++, first++) {
        *b = *first;
    }
    if (first != last) {
        //insert
        insert(cend(), first, last);
    }else if (b != e){
        erase(b.getPtr(), e.getPtr());
    }
}

template<class T>
template<class InputIterator, typename std::enable_if<
                        tiny::is_input_iterator<InputIterator>::value &&
                        std::is_constructible<typename list<T>::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                            int>::type>
void list<T>::_construct(InputIterator first, InputIterator last){
    _createTail();
    for (; first != last; first++) {
        auto node = _createNode(*first);
        _link_to_tail(node->as_base());
    }
}

template<class T>
void list<T>::_free_elements(){
    if (empty()) return;
    for (iterator beg = begin(); beg != end(); beg++) {
        node_ptr node = beg.getPtr()->as_node();
        _destory_node(node);
    }
    _tail->unlink();
    _size = 0;
}
template<class T>
void list<T>::_destory_node(base_ptr node){
    data_allocator.destroy(&node->as_node()->element);
    node_allocator.deallocate(node->as_node(), 1);
}

//构造，拷贝，移动
template<class T>
list<T>::list() {
    _createTail();
}

template<class T>
list<T>::list(size_type n){
    _construct(n, value_type());
    _size = n;
}
template<class T>
list<T>::list(size_type n, const value_type &val){
    _construct(n, val);
    _size = n;
}
template<class T>
template<class InputIterator, typename std::enable_if<
                        tiny::is_input_iterator<InputIterator>::value &&
                        std::is_constructible<typename list<T>::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                            int>::type>
list<T>::list(InputIterator first, InputIterator last){
    _construct(first, last);
    _size = tiny::distance(first, last);
}
template<class T>
list<T>::list(const list &x){
    _construct(x.begin(), x.end());
    _size = x.size();
}
template<class T>
list<T>::list(list &&x):_tail(x._tail), _size(x._size){
    x._tail = nullptr;
    x._size = 0;
}
template<class T>
list<T>::list(std::initializer_list<value_type> il){
    _construct(il.begin(), il.end());
    _size = il.size();
}
template<class T>
list<T>::~list(){
    if (size()) {
     _free_elements();
    }
    basenode_allocator.destroy(_tail);
    basenode_allocator.deallocate(_tail, 1);
    _tail = nullptr;
}

////operator=
////Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
template<class T>
list<T>& list<T>::operator=(const list& x){
    if (&x != this) {
        _assign_range(x.begin(), x.end());
        _size = x.size();
    }
    return *this;
}
template<class T>
list<T>& list<T>::operator=(list &&x) {
    if (&x != this){
        _free_elements();
        basenode_allocator.destroy(_tail);
        basenode_allocator.deallocate(_tail, 1);
        _tail = x._tail;
        _size = x._size;
        x._tail = nullptr;
        x._size = 0;
    }
    return *this;
}
template<class T>
list<T>& list<T>::operator=(std::initializer_list<value_type> il){
    _assign_range(il.begin(), il.end());
    _size = il.size();
    return *this;
}


//assign
template<class T>
template <class InputIterator,typename std::enable_if<
                            tiny::is_input_iterator<InputIterator>::value &&
                            std::is_constructible<typename list<T>::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,int>::type>
void list<T>::assign (InputIterator first, InputIterator last){
    _assign_range(first, last);
    _size = tiny::distance(first, last);
}

template<class T>
void list<T>::assign (std::initializer_list<value_type> il){
    _assign_range(il.begin(), il.end());
    _size = il.size();
}

template<class T>
void list<T>::assign (size_type n, const value_type& val){
    auto b = begin(), e = end();
    for (; b != e && n != 0; b++, n--) {
        *b = val;
    }
    if (n) {
        //insert
        insert(cend(), n, val);
    }else if (b != e){
        erase(b.getPtr(), e.getPtr());
    }
    _size = n;
}

template<class T>
template <class... Args>
void list<T>::emplace_front(Args&&... args){
    auto node = _createNode(tiny::forward<Args>(args)...);
    _link_to_head(node);
    ++_size;
}

template<class T>
void list<T>::push_front(const value_type &val){
    auto node = _createNode(val);
    _link_to_head(node);
    ++_size;
}
template<class T>
void list<T>::push_front(value_type&& val){
    auto node = _createNode(tiny::move(val));
    _link_to_head(node);
    ++_size;
}
template<class T>
void list<T>::pop_front(){
    if (empty()) {
        throw std::runtime_error("pop_front on empty list");
    }
    base_ptr head = _head();
    _tail->next = head->next;
    head->next->pre = _tail;
    _destory_node(head);
    _size--;
}
template<class T>
template <class... Args>
void list<T>::emplace_back(Args&&... args){
    auto node = _createNode(tiny::forward<Args>(args)...);
    _link_to_tail(node);
    ++_size;
}
template<class T>
void list<T>::push_back(const value_type& val){
    auto node = _createNode(val);
    _link_to_tail(node);
    ++_size;
}
template<class T>
void list<T>::push_back(value_type&& val){
    auto node = _createNode(tiny::move(val));
    _link_to_tail(node);
    ++_size;
}
template<class T>
void list<T>::pop_back(){
    if (empty()) {
        throw std::runtime_error("pop_back on empty list");
    }
    auto tail = _tail->pre;
    _tail->pre = tail->pre;
    tail->pre->next = _tail;
    _destory_node(tail);
    --_size;
}
template<class T>
template<class... Args>
typename list<T>::iterator
list<T>::emplace(const_iterator position, Args&&... args){
    ++_size;
    auto node = _createNode(tiny::forward<Args>(args)...);
    return _link_nodes(position.getPtr(), node, node);
}
template<class T>
typename list<T>::iterator
list<T>::insert (const_iterator position, const value_type& val){
    ++_size;
    auto node = _createNode(val);
    return _link_nodes(position.getPtr(), node, node);
}
template<class T>
typename list<T>::iterator
list<T>::insert(const_iterator position, size_type n, const value_type& val){
    list_node_base<T> tmp;
    base_ptr it = &tmp;
    while (n--) {
        auto node = _createNode(val);
        it->next = node;
        node->pre = it;
        it = it->next;
        ++_size;
    }
    return _link_nodes(position.getPtr(), tmp.next, it);
}

template<class T>
template <class InputIterator, typename std::enable_if<
                                tiny::is_input_iterator<InputIterator>::value &&
                                std::is_constructible<typename list<T>::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,int>::type>
typename list<T>::iterator
list<T>::insert (const_iterator position, InputIterator first, InputIterator last){
    list_node_base<T> tmp;
    base_ptr it = &tmp;
    while (first != last) {
        auto node = _createNode(*first++);
        it->next = node;
        node->pre = it;
        it = it->next;
        ++_size;
    }
    return _link_nodes(position.getPtr(), tmp.next, it);
}
template<class T>
typename list<T>::iterator
list<T>::insert (const_iterator position, value_type&& val){
    _size++;
    auto node = _createNode(tiny::move(val));
    return _link_nodes(position.getPtr(), node, node);
}
template<class T>
typename list<T>::iterator
list<T>::insert (const_iterator position, std::initializer_list<value_type> il){
    return insert(position, il.begin(), il.end());
}
template<class T>
typename list<T>::iterator
list<T>::erase (const_iterator position){
    if (empty()) {
        throw std::runtime_error("erase on empty list");
    }
    base_ptr after = position.getPtr()->next;
    if (position == cbegin()) {
        pop_front();
    }else if (after == _tail){
        pop_back();
    }else{
        base_ptr pToDeleteNode = position.getPtr();
        pToDeleteNode->pre->next = after;
        after->pre = pToDeleteNode->pre;
        _destory_node(pToDeleteNode);
    }
    --_size;
    return iterator(after);
}

template<class T>
typename list<T>::iterator
list<T>::erase (const_iterator first_iterator, const_iterator last_iterator){
    base_ptr first = first_iterator.getPtr(), last = last_iterator.getPtr();
    first->pre->next = last;
    last->pre = first->pre;
    while (first != last) {
        base_ptr pToDeleteNode = first;
        _destory_node(pToDeleteNode);
        --_size;
        first = first->next;
    }
    return iterator(last);
}
template<class T>
typename list<T>::iterator
list<T>::_erase_nofree(const_iterator first, const_iterator last){
    difference_type diff = tiny::distance(first, last);
    base_ptr first_ptr = first.getPtr(), last_ptr = last.getPtr();
    first_ptr->pre->next = last_ptr;
    last_ptr->pre = first_ptr->pre;
    _size -= diff;
    return iterator(last_ptr);
}
template<class T>
void list<T>::swap(list &x){
    using std::swap;
    std::swap(_tail, x._tail);
    std::swap(_size, x._size);
}
template<class T>
void list<T>::resize(size_type n){
    resize(n, value_type());
}
template<class T>
void list<T>::resize(size_type n, const value_type& val){
    auto it = cbegin();
    for (; it != cend() && n ; ++it, --n)
        ;
    if (n) {
        //需要扩充
        insert(cend(), n, val);
    }else if (it != cend()){
        erase(it, cend());
    }
}
    
template<class T>
void list<T>::clear(){
    _free_elements();
}
template<class T>
void list<T>::splice (const_iterator position, list& x){
    splice(position, x, x.cbegin(), x.cend());
}
template<class T>
void list<T>::splice (const_iterator position, list&& x){
    splice(position, x, x.cbegin(), x.cend());
}
template<class T>
void list<T>::splice (const_iterator position, list& x, const_iterator i){
    splice(position, x, i, ++i);
}
template<class T>
void list<T>::splice (const_iterator position, list&& x, const_iterator i){
    splice(position, x, i, ++i);
}
template<class T>
void list<T>::splice (const_iterator position, list& x,
                      const_iterator first, const_iterator last){
    splice(position, static_cast<list&&>(x), first, last);
}
template<class T>
void list<T>::splice (const_iterator position, list&& x,
                      const_iterator first, const_iterator last){
    assert(first != last);
    difference_type diff = tiny::distance(first, last);
    const_iterator copy_first = first, copy_last = last--;
    //erase from x
    x._erase_nofree(copy_first, copy_last);
    //link to origin
    _link_nodes(position.getPtr(), first.getPtr(), last.getPtr());
    _size += diff;
}
template<class T>
void list<T>::remove (const value_type& val){
    remove_if([val](const value_type & v){
        return v == val;
    });
}
template<class T>
template <class Predicate>
void list<T>::remove_if (Predicate pred){
    if (empty()) return;
    auto beg = cbegin();
    while (beg != cend()) {
        if (pred(*beg)) {
            beg = erase(beg).getPtr();
        }else{
            ++beg;
        }
    }
}
template<class T>
void list<T>::unique(){
    unique([](const value_type lhs, const value_type rhs){
        return lhs == rhs;
    });
}
template<class T>
template <class BinaryPredicate>
void list<T>::unique (BinaryPredicate binary_pred){
    if (empty())
        return;
    
    auto ct = cbegin();
    auto pre = ct++;
    while (ct != cend()) {
        if (binary_pred(*pre, *ct)) {
            //[pre ...ct)
            auto deleteBegin = const_iterator(ct.getPtr());
            for (++ct;binary_pred(*pre, *ct);++ct )
                ;
            auto deleteAfter = erase(deleteBegin, ct);
            ct = const_iterator(deleteAfter.getPtr());
        }else{
            pre = ct++;
        }
    }
}
template<class T>
void list<T>::merge (list& x){
    merge(static_cast<list&&>(x));
}
template<class T>
void list<T>::merge (list&& x){
    merge(x, std::less_equal<T>());
}
template<class T>
template <class Compare>
void list<T>::merge (list& x, Compare comp){
    merge(static_cast<list&&>(x), comp);
}
template<class T>
template <class Compare>
void list<T>::merge (list&& x, Compare comp){
    if (&x == this || x.empty()) return;
    auto beg1 = cbegin(), beg2 = x.cbegin(), end1 = cend(), end2 = x.cend();
    while (beg1 != end1 && beg2 != end2) {
        if (!comp(*beg1, *beg2)) {
            //*beg2 < *beg1
            //从x中移除beg2并插入到this
            base_ptr pToDeletedPtr = beg2.getPtr();
            base_ptr pToDeleteAfterPtr = pToDeletedPtr->next;
            //移除
            x._erase_nofree(pToDeletedPtr, pToDeleteAfterPtr);
            beg2 = const_iterator(pToDeleteAfterPtr);
            
            _link_nodes(beg1.getPtr(), pToDeletedPtr, pToDeletedPtr);
            _size++;
        }else{
            ++beg1;
        }
    }
    std::cout << *this << std::endl;
    std::cout << x << std::endl;
    if (beg2 != end2) {
        difference_type sz = tiny::distance(beg2, end2);
        _size += sz;
        base_ptr s = beg2.getPtr(), e = end2.getPtr();
        _link_nodes(cend().getPtr(), s, e->pre);
        x._tail->unlink();
        x._size = 0;
    }
}
template <class T>
void list<T>::sort(){
    sort(std::less<T>());
}
template <class T>
template <class Compare>
void list<T>::sort (Compare comp){
    _sort(cbegin(), cend(), size(), comp);
}
template <class T>
void list<T>::reverse() noexcept{
    if (empty()) return;

    auto beg = begin();
    for (; beg != end(); beg--) {//方向不要弄错了
        auto pointer = beg.getPtr();
        std::swap(pointer->pre, pointer->next);
    }
    std::swap(_tail->next, _tail->pre);
}

template <class T>
template <class Compared>
typename list<T>::const_iterator
list<T>::_sort(const_iterator f1, const_iterator l2, size_type n, Compared comp)
{
  if (n < 2)
    return f1;

  if (n == 2)
  {
    if (comp(*--l2, *f1))
    {
      auto ln = l2.getPtr();
      _unlink(ln, ln);
      _link_nodes(f1.getPtr(), ln, ln);
      return l2;
    }
    return f1;
  }

  auto n2 = n / 2;
  auto l1 = f1;
  tiny::advance(l1, n2);
  auto result = f1 = _sort(f1, l1, n2, comp);  // 前半段的最小位置
  auto f2 = l1 = _sort(l1, l2, n - n2, comp);  // 后半段的最小位置

  // 把较小的一段区间移到前面
  if (comp(*f2, *f1))
  {
      result = f2;
  }


  // 合并两段有序区间
  while (f1 != l1 && f2 != l2)
  {
    if (comp(*f2, *f1))
    {
      auto m = f2;
      ++m;
      for (; m != l2 && comp(*m, *f1); ++m)
        ;
        //需要删除[f, l]
      auto f = f2.getPtr();
      auto l = m.getPtr()->pre;
      if (l1 == f2)
        l1 = m; //?
      f2 = m;
      _unlink(f, l);
      _link_nodes(f1.getPtr(), f, l);
      f1++;
    }
    else
    {
      ++f1;
    }
  }
  return result;
}
template <class T>
bool operator== (const list<T>& lhs, const list<T>& rhs){
    return tiny::equal(lhs.begin(), lhs.end(), rhs.begin(), std::equal_to<T>());
}
template <class T>
bool operator!= (const list<T>& lhs, const list<T>& rhs){
    return !operator==(lhs, rhs);
}
template <class T>
bool operator<  (const list<T>& lhs, const list<T>& rhs){
    return tiny::lexicographical_compare(lhs.begin(), lhs.end(),lhs.begin(),rhs.end(), std::less<T>());
}
template <class T>
bool operator<= (const list<T>& lhs, const list<T>& rhs){
    return tiny::lexicographical_compare(lhs.begin(), lhs.end(),lhs.begin(),rhs.end(), std::less_equal<T>());
}
template <class T>
bool operator>  (const list<T>& lhs, const list<T>& rhs){
    return tiny::lexicographical_compare(lhs.begin(), lhs.end(),lhs.begin(),rhs.end(), std::greater<T>());
}
template <class T>
bool operator>= (const list<T>& lhs, const list<T>& rhs){
    return tiny::lexicographical_compare(lhs.begin(), lhs.end(),lhs.begin(),rhs.end(), std::greater_equal<T>());
}
template <class T>
void swap (list<T>& x, list<T>& y){
    x.swap(y);
}
template<class T>
std::ostream& operator<<(std::ostream&os, tiny::list<T> list){
    auto beg = list.begin();
    while(beg != list.end()){
        os << *beg++ << ",";
    }
    return os;
}
}
#endif /* list_hpp */
