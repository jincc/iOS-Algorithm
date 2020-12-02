//
//  deque.h
//  tiny_stl
//
//  Created by junl on 2020/11/18.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef deque_hpp
#define deque_hpp
#include <iostream>
#include "allocator.h"
#include "iterator.h"
#include "util.h"
#include "alg.h"
#include <cassert>
namespace tiny {

//#define DEBUG_FEATURE
#define DEQUE_MAP_INIT_SIZE 8
    
#ifdef DEBUG_FEATURE
    template<typename...Args>
    void
    log_info(const Args&... args){
        errorMsg(std::cerr, debug_rep(args)...) << std::endl;
    }
#else
    template<typename...Args>
    void
    log_info(const Args&... args){}
#endif

template<class T>
struct deque_trunk_size{
#ifdef DEBUG_FEATURE
    static constexpr size_t value = 10;
#else
    static constexpr size_t value = sizeof(T) < 256 ? 4096 / sizeof(T) : 16;
#endif
};
    
template<class T, class Reference, class Pointer>
struct deque_iterator : public iterator<tiny::random_access_iterator_tag, T>{
    typedef random_access_iterator_tag           iterator_category;
    typedef T                                    value_type;
    typedef Pointer                              pointer;
    typedef Reference                            reference;
    typedef ptrdiff_t                            difference_type;
    typedef value_type*                          value_pointer;
    typedef value_pointer*                             map_pointer;
    typedef deque_iterator                       self_type;
    typedef deque_iterator<value_type, value_type&, value_type*> iterator;
    typedef deque_iterator<value_type, const value_type&, const value_type*> const_iterator;
    
    value_pointer cur;//位于trunk块中的位置
    value_pointer first;//用于确定trunk中的边界
    value_pointer last;//用于确定trunk中的边界
    map_pointer node;//用于定位当前trunk位于map中的哪个位置
    static constexpr size_t trunkSizePerPage = deque_trunk_size<T>::value;
    deque_iterator():cur(nullptr), first(nullptr), last(nullptr), node(nullptr){}
    deque_iterator(value_pointer cur, map_pointer node):cur(cur), first(*node), last(*node + trunkSizePerPage),node(node){}
    deque_iterator(const iterator& other):cur(other.cur), first(other.first), last(other.last), node(other.node){}
    deque_iterator(const const_iterator& other):cur(other.cur), first(other.first), last(other.last), node(other.node){}
    deque_iterator(deque_iterator &&other): cur(other.cur), first(other.first), last(other.last), node(other.node){
        other.cur = other.first = other.last = nullptr;
        other.node = nullptr;
    }
    self_type& operator=(const self_type &other){
        if (&other != this){
            cur = other.cur;
            first = other.first;
            last = other.last;
            node = other.node;
        }
        return *this;
    }
    self_type& operator=(self_type &&other){
        if (&other != this){
            cur = other.cur;
            first = other.first;
            last = other.last;
            node = other.node;
            other.cur = other.first = other.last = nullptr;
            other.node = nullptr;
        }
        return *this;
    }
    //Can be compared for equivalence using the equality/inequality operators
   //(meaningful when both iterator values iterate over the same underlying sequence).
    bool operator==(const self_type &other) const {
        return other.node == node && other.cur == cur;
    }
    bool operator!=(const self_type &other) const{
        return !(*this == other);
    }
    //Can be compared with inequality relational operators (<, >, <= and >=).
    bool operator<(const self_type &other) const{
        return node < other.node || (node == other.node && cur < other.cur);
    }
    bool operator>(const self_type &other) const{
        return node > other.node || (node == other.node && cur > other.cur);
    }
    bool operator<=(const self_type &other) const{
        return !(*this > other);
    }
    bool operator>=(const self_type &other) const{
        return !(*this < other);
    }
    //Can be dereferenced as an rvalue (if in a dereferenceable state).
    reference operator*(){
        return *cur;
    }
    pointer operator->(){
        return &(operator*());
    }
    self_type& operator++(){
        ++cur;
        if (cur == last) {
            set_node(node + 1);
            cur = first;
        }
        return *this;
    }
    self_type operator++(int) {
        self_type tmp(*this);
//        operator++();
        ++*this;
        return tmp;
    }
    self_type& operator--(){
        if (cur == first) {
            set_node(node - 1);
            cur = last;
        }
        --cur;
        return *this;
    }
    self_type& operator--(int){
        self_type tmp(*this);
//        operator--();
        --*this;
        return tmp;
    }
    void set_node(map_pointer newnode){
        node = newnode;
        first = *newnode;
        last = first + trunkSizePerPage;
    }
    self_type operator+(difference_type step){
        self_type temp(*this);
        temp+=step;
        return temp;
    }
    self_type& operator+=(difference_type step){ //step可正可负
        difference_type offset = cur - first + step;
        if (offset >= 0 && static_cast<size_t>(offset) < trunkSizePerPage){
            cur += step;
        }else{
            const auto node_offset = offset > 0
              ? offset / static_cast<difference_type>(trunkSizePerPage)
              : -static_cast<difference_type>((-offset - 1) / trunkSizePerPage) - 1;
            set_node(node + node_offset);
            cur = first + (offset - node_offset * static_cast<difference_type>(trunkSizePerPage));
        }
        return *this;
    }
    self_type operator-(difference_type step){
        self_type temp(*this);
        temp-=step;
        return temp;
    }
    self_type& operator-=(difference_type step){
//        return operator+=(-step);
        return *this += -step;
    }
    reference operator[](int idx) {
//        return *(operator+(idx));
        return *(*this + idx);
    }
    difference_type operator-(const self_type& rhs) const {
        return static_cast<difference_type>(trunkSizePerPage) * (node - rhs.node) + (cur - first) - (rhs.cur - rhs.first);
    }
};

template<class T, class Reference, class Pointer>
void swap(deque_iterator<T, Reference, Pointer> &lhs, deque_iterator<T, Reference, Pointer> &rhs){
    using std::swap;
    swap(lhs.cur, rhs.cur);
    swap(lhs.first, rhs.first);
    swap(lhs.last, rhs.last);
    swap(lhs.node, rhs.node);
}

template<class T>
class deque{
public:
    typedef T value_type;
    typedef tiny::deque_iterator<value_type, value_type&, value_type*> iterator;
    typedef tiny::deque_iterator<value_type, const value_type&, const value_type*> const_iterator;
    typedef tiny::reverse_iterator<iterator> reverse_iterator;
    typedef tiny::reverse_iterator<iterator> const_reverse_iterator;
    typedef typename iterator::map_pointer map_pointer;
    typedef typename iterator::value_pointer value_pointer;
    typedef tiny::allocator<T> allocator_type;
    typedef tiny::allocator<T*> map_allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::size_type size_type;
private:
    iterator _begin;
    iterator _end;
    map_pointer _map;
    size_type _trunk_cnt;
    static constexpr size_t trunkSizePerPage = deque_trunk_size<T>::value;
    static map_allocator_type map_allocator;
    static allocator_type data_allocator;
public:
    //deque
    deque(){_fill_n_elements(0, value_type());};
    //fill
    explicit deque(size_type n){_fill_n_elements(n, value_type());};
    deque(size_type n, const value_type& val){_fill_n_elements(n, val);};
    //range
    template<class InputIterator, typename std::enable_if<
                        tiny::is_input_iterator<InputIterator>::value &&
                        std::is_constructible<value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                            int>::type = 0>
    deque(InputIterator first, InputIterator last){_fill_elements(first, last);};
    //copy
    deque(const deque &x){_fill_elements(x.begin(), x.end());};
    //move
    deque(deque &&x):_begin(tiny::move(x._begin)), _end(tiny::move(x._end)), _map(tiny::move(x._map)), _trunk_cnt(tiny::move(x._trunk_cnt)){
        x._begin = x._end = iterator();
        x._map = nullptr;
        x._trunk_cnt = 0;
    };
    //initializer list
    deque(std::initializer_list<value_type> il){_fill_elements(il.begin(), il.end());};
    ~deque() {
        _free_all_elements(true);
        _free_first_trunk_memory();
        _free_map();
    };
    //operator= Any elements held in the container before the call are either assigned to or destroyed.
    deque& operator=(const deque &x) {
        assign(x.begin(), x.end());
        return *this;
    }
    deque& operator==(deque &&x) {
        if (&x == this) return *this;
        clear();
        _begin = tiny::move(x._begin);
        _end = tiny::move(x._end);
        _map = x._map;
        _trunk_cnt = x._trunk_cnt;
        x._begin = x._end = x._map = nullptr;
        x._trunk_cnt = 0;
        return *this;
    };
    deque& operator=(std::initializer_list<value_type> il){
        assign(il);
        return *this;
    }
    
    iterator begin() noexcept{return _begin;}
    iterator end() noexcept{return _end;}
    const_iterator begin() const noexcept {return _begin;}
    const_iterator end() const noexcept{return _end;}
    reverse_iterator rbegin() noexcept {return reverse_iterator(end());}
    const_reverse_iterator rbegin() const noexcept {return const_reverse_iterator(end());};
    reverse_iterator rend() noexcept {return reverse_iterator(begin());}
    const_reverse_iterator rend() const noexcept {return const_reverse_iterator(begin());};
    const_iterator cbegin() const noexcept {return _begin;};
    const_iterator cend() const noexcept {return _end;};
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end());};
    const_reverse_iterator crend() const noexcept {return const_reverse_iterator(begin());};
    
    //Capacity
    bool empty() const {return _begin == _end;};
    size_type size() const {return _end - _begin;}
    void resize(size_type n) {return resize(n, value_type());};
    void resize(size_type n, const value_type &val);
    void shrink_to_fit();
    //Element access:
    reference back() {
        assert(!empty());
        return *(_end - 1);
    }
    const_reference back() const {
        assert(!empty());return *(_end - 1);
    };
    reference front() {
        assert(!empty());
        return *_begin;
    }
    const_reference front() const{
        assert(!empty());
        return *_begin;
    };
    
    reference at (size_type n){
        if (n >= size()) throw std::out_of_range("at out of range");
        return (*this)[n];
    }
    const_reference at (size_type n) const{
        if (n >= size()) throw std::out_of_range("at out of range");
        return (*this)[n];
    }
    reference operator[](size_type n) {
        return *(_begin + n);
    }
    const_reference operator[](size_type n) const {
        return *(_begin + n);
    }
    void clear() {_free_all_elements(true);}
    //Modifiers
    template<class InputIterator, typename std::enable_if<
                            tiny::is_input_iterator<InputIterator>::value &&
                            std::is_constructible<value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                                int>::type = 0>
    void assign(InputIterator first, InputIterator last){
        _assign_elements(first, last);
    }
    void assign(size_type n, const value_type &val) {
        _assign_elements(n, val);
    }
    void assign(std::initializer_list<value_type> il){
        _assign_elements(il.begin(), il.end());
    }
    
    void push_back(const value_type &val);
    void push_back(value_type &&val) {emplace_back(tiny::move(val));};
    template <class ...Args>
    void emplace_back (Args&& ...args);
    void pop_back();
    
    void push_front(const value_type &val);
    void push_front(value_type &&val){emplace_front(tiny::move(val));};
    template<class... Args>
    void emplace_front(Args&&... args);
    void pop_front();
    
    template<class... Args>
    iterator emplace(const_iterator positon, Args&&... args);
    //insert
    iterator insert(const_iterator position, const value_type &val) {
        return insert(position, 1, val);
    };
    iterator insert(const_iterator position, size_type n, const value_type &val);
    template<class InputIterator, typename std::enable_if<
                            tiny::is_input_iterator<InputIterator>::value &&
                            std::is_constructible<value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                                int>::type = 0>
    iterator insert(const_iterator position, InputIterator first, InputIterator last) {
        return _insert_range(position, first, last);
    };
    iterator insert(const_iterator position, value_type &&val);
    iterator insert(const_iterator position, std::initializer_list<value_type> il){
        return _insert_range(position, il.begin(), il.end());
    };
    iterator erase(const_iterator position) {return erase(position, position + 1);};
    iterator erase(const_iterator first, const_iterator last);
    void swap (deque& x);

private:
    //创建表结构，初始化各节点
    void _map_init(size_type n);
    //创建map表结构
    map_pointer _create_map(size_type n);
    void _free_map();
    //分配每一页的内存，每一页固定trunkSizePerPage条目
    void _alloc_trunkpage_memory(map_pointer startPage, map_pointer endPage);
    void _free_trunkpage_memory(map_pointer startPage, map_pointer endPage);
//    //调用value_type析构函数, 不会释放trunk块的内存
    void _destroy_elements(const_iterator first, const_iterator last);
    //调用vlaue_type析构函数，释放除了第一页的 trunk memory
    void _free_all_elements(bool isFreeMemory);
    //释放第一页的trunk memory
    void _free_first_trunk_memory();
    //确保新增n个元素，当前内存能够存放的下
    void _require_capacity(size_type new_n, bool isFront);
    //重建map, 并在后部添加need_page_cnt个page
    void _realloc_map_at_back(size_type need_page_cnt);
    //重建map, 并在前部添加need_page_cnt个page
    void _realloc_map_at_front(size_type need_page_cnt);
    
    void _fill_n_elements(size_type n, const value_type& val);
    template<class InputIterator, typename std::enable_if<
                        tiny::is_input_iterator<InputIterator>::value &&
                        std::is_constructible<value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                            int>::type = 0>
    void _fill_elements(InputIterator first, InputIterator last);
    template<class InputIterator, typename std::enable_if<
                        tiny::is_input_iterator<InputIterator>::value &&
                        std::is_constructible<value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                            int>::type = 0>
    void _assign_elements(InputIterator first, InputIterator last);
    void _assign_elements(size_type n, const value_type &val);
    size_type _ct_alloc_page_size() {
        return _end.node - _begin.node + 1;
    }
    //insert helper
    iterator _insert_aux(const_iterator position, size_type n, const value_type &val);
    template<class InputIterator>
    iterator _insert_range(const_iterator position, InputIterator first, InputIterator last);
    template<class InputIterator>
    iterator _insert_range_aux(const_iterator position, size_type n, InputIterator first, InputIterator last);
};
template<class T>
typename deque<T>::map_allocator_type deque<T>::map_allocator;
template<class T>
typename deque<T>::allocator_type deque<T>::data_allocator;
    
template<class T>
void deque<T>::_fill_n_elements(size_type n, const value_type& val){
    //fill
    _map_init(n);
    if (!n) return;
    for (auto it = _begin.node; it != _end.node; it++) {
        tiny::uninitialized_fill(*it, *it + trunkSizePerPage, val);
    }
    tiny::uninitialized_fill(_end.first, _end.cur, val);
}

template<class T>
template<class InputIterator, typename std::enable_if<
                    tiny::is_input_iterator<InputIterator>::value &&
                    std::is_constructible<typename deque<T>::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                        int>::type>
void deque<T>::_fill_elements(InputIterator first, InputIterator last){
    auto distance = last - first;
    _map_init(static_cast<size_t>(distance));
    if (!distance) return;
    
    for (auto it = _begin.node; it != _end.node; it++) {
        auto next = first;
        tiny::advance(next, trunkSizePerPage);
        tiny::uninitialized_copy(first, next, *it);
        first = next;
    }
    tiny::uninitialized_copy(first, last, _end.first);
}

template<class T>
template<class InputIterator, typename std::enable_if<
                    tiny::is_input_iterator<InputIterator>::value &&
                    std::is_constructible<typename deque<T>::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                        int>::type>
void deque<T>::_assign_elements(InputIterator first, InputIterator last){
    _destroy_elements(begin(), end());
    auto it = begin();
    for(; it != end() && first != last; it ++){
        *it = *first++;
    }
    if (first != last){
        insert(end(), first, last);
    }else if(it != end()){
        erase(it, end());
    }
}
template<class T>
void deque<T>::_assign_elements(size_type n, const value_type &val){
    _destroy_elements(begin(), end());
    auto it = begin();
    for(; it != end() && n--; it ++){
        *it = val;
    }
    if (n){
        insert(end(), n, val);
    }else if(it != end()){
        erase(it, end());
    }
}

template<class T>
void deque<T>::_map_init(size_type n){
    size_type need_trunk_sz = n / trunkSizePerPage + 1;
    _trunk_cnt = need_trunk_sz + 2; //buffer
    if (_trunk_cnt < DEQUE_MAP_INIT_SIZE) {
        _trunk_cnt = DEQUE_MAP_INIT_SIZE;
    }
    _map = _create_map(_trunk_cnt);
    //分配trunkmemory
    size_type beg = (_trunk_cnt - need_trunk_sz) / 2, end =  need_trunk_sz > 0 ? beg + need_trunk_sz - 1 : beg;
    _alloc_trunkpage_memory(_map + beg, _map + end);
    _begin.set_node(_map + beg);
    _end.set_node(_map + end);
    _begin.cur = _begin.first;
    _end.cur = _end.first + (n % trunkSizePerPage);
}
template<class T>
typename deque<T>::map_pointer deque<T>::_create_map(size_type n){
    auto ret = map_allocator.allocate(n);
    for (size_type i = 0; i < n ; i++) {
        ret[i] = nullptr;
    }
    return ret;
}
template<class T>
void deque<T>::_free_map(){
    if (_map) {
        map_allocator.deallocate(_map, trunkSizePerPage);
        _map = nullptr;
        _trunk_cnt = 0;
    }
}
template<class T>
void deque<T>::_alloc_trunkpage_memory(map_pointer startPage, map_pointer endPage){
    log_info("alloc page : ", endPage - startPage + 1);
    for (auto it = startPage; it <= endPage; it++) {
        *it = data_allocator.allocate(trunkSizePerPage);
    }
}
template<class T>
void deque<T>::_free_trunkpage_memory(map_pointer startPage, map_pointer endPage){
    log_info("free page : ", endPage - startPage + 1);
    for (auto it = startPage; it <= endPage; it++) {
        data_allocator.deallocate(*it, trunkSizePerPage);
        *it = nullptr;
    }
}

template<class T>
void deque<T>::_free_all_elements(bool isFreeMemory){
    if (empty()) return;
    
    auto free_task = [isFreeMemory](value_pointer start, size_type sz){
        if (isFreeMemory){
            data_allocator.deallocate(start, sz);
        }
    };
    
    for (auto it = _begin.node + 1; it < _end.node; it++) {
        auto first = *it, last = first + trunkSizePerPage;
        //.~T()
        tiny::uninitialized_destory(first, last);
        //deallocate
        free_task(first, trunkSizePerPage);
    }
    if (_begin.node != _end.node){
        tiny::uninitialized_destory(_end.first, _end.cur);
        free_task(_end.first, trunkSizePerPage);
    }else{
    }
    tiny::uninitialized_destory(_begin.cur, _begin.last);
    //第一页内存暂时不释放
    if (isFreeMemory) {
        _end.set_node(_begin.node);
        _end.cur = _end.first;
        _begin.cur = _begin.first;
    }
}

template<class T>
void deque<T>::_destroy_elements(const_iterator first, const_iterator last){
    for (auto it = first.node + 1; it  <  last.node; it++) {
        tiny::uninitialized_destory(*it, *it + trunkSizePerPage);
    }
    if (first.node != last.node){
        tiny::uninitialized_destory(last.first, last.cur);
    }
    tiny::uninitialized_destory(first.cur, first.last);
}

template<class T>
void deque<T>::_free_first_trunk_memory() {
    data_allocator.deallocate(_begin.first, trunkSizePerPage);
}
template<class T>
void deque<T>::_require_capacity(size_type new_n, bool isFront){
    if (isFront) {
        size_t ct = _begin.cur - _begin.first;
        if (ct > new_n) return;

        new_n -= ct;
        size_type need_page_cnt = new_n / trunkSizePerPage + 1;
        if (_begin.node - _map  < need_page_cnt) {
            //需要重建map
            _realloc_map_at_front(need_page_cnt);
            return;
        }
        _alloc_trunkpage_memory(_begin.node - need_page_cnt, _begin.node - 1);
    }else{
        size_type ct = _end.last - _end.cur;//**
        if (ct > new_n) return;
        //当前page存放不下
        new_n -= ct;
        size_type need_page_cnt = new_n / trunkSizePerPage + 1;
        if (_trunk_cnt - (_end.node - _map) - 1 < need_page_cnt ) {
            //需要重建map
            _realloc_map_at_back(need_page_cnt);
            return;
        }
        _alloc_trunkpage_memory(_end.node+1, _end.node + need_page_cnt);
    }
}

template<class T>
void deque<T>::_realloc_map_at_back(size_type need_page_cnt){
    size_type newTrunkSize = _trunk_cnt << 1;
    log_info("发生后向扩容: 重建map, 当前", _trunk_cnt, "重建后", newTrunkSize);
    size_type ctAllocSIze = _ct_alloc_page_size();
    size_type needAllocPageSize =  ctAllocSIze + need_page_cnt;
    
    auto newMap = _create_map(newTrunkSize);
    auto beginPage = newMap + (newTrunkSize - needAllocPageSize) / 2;
    auto midPage = beginPage + ctAllocSIze;
    auto endPage = midPage + need_page_cnt;
    
    for (auto it = beginPage, it2 = _begin.node; it != midPage; it++, it2++) {
        *it = *it2;
    }
    _alloc_trunkpage_memory(midPage, endPage);
    
    _free_map();
    _map = newMap;
    _trunk_cnt = newTrunkSize;
    _begin = iterator(*beginPage + (_begin.cur - _begin.first), beginPage);
    _end = iterator(*(midPage - 1) + (_end.cur - _end.first), midPage - 1);
}
    
template<class T>
void deque<T>::_realloc_map_at_front(size_type need_page_cnt){
    size_type newTrunkSize = _trunk_cnt << 1;
    log_info("发生前向扩容: 重建map, 当前", _trunk_cnt, "重建后", newTrunkSize);
    size_type ctAllocSize = _ct_alloc_page_size();
    size_type needAllocPageSize =  ctAllocSize + need_page_cnt;
    
    auto newMap = _create_map(newTrunkSize);
    auto beginPage = newMap + (newTrunkSize - needAllocPageSize) / 2;
    auto midPage = beginPage + need_page_cnt;
    auto endPage = midPage + ctAllocSize;
    
    for (auto it = midPage, it2 = _begin.node; it != endPage; it++, it2++) {
        *it = *it2;
    }
    _alloc_trunkpage_memory(beginPage, midPage - 1);
    
    _free_map();
    _map = newMap;
    _trunk_cnt = newTrunkSize;
    _begin = iterator(*midPage + (_begin.cur - _begin.first), midPage);
    _end = iterator(*(endPage - 1) + (_end.cur - _end.first), endPage - 1);
}

template<class T>
void deque<T>::resize(size_type n, const value_type &val){
    size_type sz = size();
    if (n < sz){
        erase(_begin + n, _end);
    }else if (n > sz){
        insert(_end, n - sz, val);
    }
}

template<class T>
void deque<T>::push_back(const value_type &val){
    if (_end.cur != _end.last - 1) {
        data_allocator.construct(_end.cur, val);
        ++_end;
    }else{
        //需要分配新一页
        _require_capacity(1, false);
        data_allocator.construct(_end.cur, val);
        ++_end;
    }
}
template<class T>
template <class ...Args>
void deque<T>::emplace_back (Args&& ...args){
    if (_end.cur != _end.last - 1) {
        data_allocator.construct(_end.cur, tiny::forward<Args>(args)...);
        ++_end;
    }else{
        //需要分配新一页
        _require_capacity(1, false);
        data_allocator.construct(_end.cur, tiny::forward<Args>(args)...);
        ++_end;
    }
}
template<class T>
void deque<T>::pop_back(){
    if (empty()) return;
    if (_end.cur != _end.first){
        --_end;
        data_allocator.destroy(_end.cur);
    }else{
        --_end;
        data_allocator.destroy(_end.cur);
        _free_trunkpage_memory(_end.node + 1, _end.node + 1);
//        log_info("test : ", back());
    }
}
template<class T>
void deque<T>::push_front(const value_type &val){
    if (_begin.cur != _begin.first) {
        --_begin;
        data_allocator.construct(_begin.cur, val);
    }else{
        _require_capacity(1, true);
        --_begin;
        data_allocator.construct(_begin.cur, val);
    }
}
template<class T>
template<class... Args>
void deque<T>::emplace_front(Args&&... args){
    if (_begin.cur != _begin.first) {
        --_begin;
        data_allocator.construct(_begin.cur, tiny::forward<Args>(args)...);
    }else{
        _require_capacity(1, true);
        --_begin;
        data_allocator.construct(_begin.cur, tiny::forward<Args>(args)...);
    }
}
template<class T>
void deque<T>::pop_front(){
    if (empty()) return;
    if (_begin.cur != _begin.last - 1) {
        data_allocator.destroy(_begin.cur);
        ++_begin;
    }else{
        data_allocator.destroy(_begin.cur);
        ++_begin;
        _free_trunkpage_memory(_begin.node - 1, _begin.node - 1);
    }
}
template<class T>
typename deque<T>::iterator
deque<T>::insert(const_iterator position, value_type &&val){
    if (position == _begin) {
        emplace_front(tiny::move(val));
        return _begin;
    }else if (position == _end){
        emplace_back(tiny::move(val));
        return _end-1;
    }else{
        return _insert_aux(position, 1,  tiny::move(val));
    }
}
template<class T>
template<class... Args>
typename deque<T>::iterator
deque<T>::emplace(const_iterator position, Args&&... args){
     if (position == _begin) {
        emplace_front(tiny::forward<Args>(args)...);
        return _begin;
    }else if (position == _end){
        emplace_back(tiny::forward<Args>(args)...);
        return _end-1;
    }else{
        value_type val = value_type(tiny::forward<Args>(args)...);
        return _insert_aux(position, 1,  tiny::move(val));
    }
}
template<class T>
typename deque<T>::iterator
deque<T>::insert(const_iterator position, size_type n, const value_type &val){
    if (position == _begin) {
        _require_capacity(n, true);
        _begin -= n;
        tiny::uninitialized_fill_n(_begin.cur, n, val);
        return _begin;
    }else if (position == _end){
        _require_capacity(n, false);
        tiny::uninitialized_fill_n(_end.cur, n, val);
        _end += n;
        return _end - n;
    }else{
        //在任意位置插入
        return _insert_aux(position, n, val);
    }
}
template<class T>
typename deque<T>::iterator
deque<T>::_insert_aux(const_iterator position, size_type n, const value_type &val){
    //插入n个元素，需要移动之前的数据，首先判断在上部分插入还是下半部分插入开销小
    size_type offset = static_cast<size_type>(position - _begin);
    if (offset < size() / 2) {
        _require_capacity(n, true);
        auto oldBegin = _begin, oldEnd = oldBegin + offset;
        auto newBegin = _begin - n;
        tiny::uninitialized_copy(oldBegin, oldEnd, newBegin);
        tiny::uninitialized_fill_n((newBegin + offset).cur, n, val);
        _begin = newBegin;
        return _begin + offset;
    }else{
        _require_capacity(n, false);
        position  = _begin + offset;
        auto oldBegin = position;
        auto oldEnd = _end;
//        auto newBegin = oldBegin + n;
        auto newEnd = oldEnd + n;
        tiny::uninitialized_copy(reverse_iterator(oldEnd), reverse_iterator(oldBegin), reverse_iterator(newEnd));
        tiny::uninitialized_fill_n(position.cur, n, val);
        _end = newEnd;
        return position;
    }
}
template<class T>
template<class InputIterator>
typename deque<T>::iterator
deque<T>::_insert_range(const_iterator position, InputIterator first, InputIterator last){
    size_type n = last - first;
    if (position == _begin) {
        _require_capacity(n, true);
        _begin -= n;
        tiny::uninitialized_copy(first, last, _begin.cur);
        return _begin;
    }else if (position == _end){
        _require_capacity(n, false);
        tiny::uninitialized_copy(first, last, _end.cur);
        _end += n;
        return _end - n;
    }else{
        //在任意位置插入
        return _insert_range_aux(position, n , first, last);
    }
}

template<class T>
template<class InputIterator>
typename deque<T>::iterator
deque<T>::_insert_range_aux(const_iterator position, size_type n, InputIterator first, InputIterator last){
    //插入n个元素，需要移动之前的数据，首先判断在上部分插入还是下半部分插入开销小
    size_type offset = static_cast<size_type>(position - _begin);
    if (offset < size() / 2) {
        _require_capacity(n, true);
        auto oldBegin = _begin, oldEnd = oldBegin + offset;
        auto newBegin = _begin - n;
        position = _begin + offset;
        tiny::uninitialized_copy(oldBegin, oldEnd, newBegin);
        tiny::uninitialized_copy(first, last, (newBegin + offset).cur);
        _begin = newBegin;
        return position;
    }else{
        _require_capacity(n, false);
        position  = _begin + offset;
        auto oldBegin = position;
        auto oldEnd = _end;
//        auto newBegin = oldBegin + n;
        auto newEnd = oldEnd + n;
        tiny::uninitialized_copy(reverse_iterator(oldEnd), reverse_iterator(oldBegin), reverse_iterator(newEnd));
        tiny::uninitialized_copy(first, last, position.cur);
        _end = newEnd;
        return position;
    }
}

template<class T>
typename deque<T>::iterator
deque<T>::erase(const_iterator first, const_iterator last){
    //[first, last)
    if (first == cbegin() && last == cend()) {
        clear();
        return end();
    }
    _destroy_elements(first, last);
    size_type positon = static_cast<size_type>(first - _begin);
    if (positon < size() / 2){
        //更偏前部分
        auto oldBegin = _begin;
        auto oldEnd = first;
        tiny::uninitialized_copy(reverse_iterator(oldEnd), reverse_iterator(oldBegin), reverse_iterator(last));
        _begin = last - positon;
        _free_trunkpage_memory(oldBegin.node, _begin.node - 1);
        return last;
    }else{
        auto oldEnd = _end;
        tiny::uninitialized_copy(last, cend(), first.cur);
        _end = first + (_end - last);
        _free_trunkpage_memory(_end.node + 1, oldEnd.node);
        return first;
    }
}
template<class T>
void deque<T>::swap (deque& x){
    using std::swap;
    swap(x._begin, _begin);
    swap(x._end, _end);
    swap(x._map, _map);
    swap(x._trunk_cnt, _trunk_cnt);
}
template<class T>
void deque<T>::shrink_to_fit(){
    for (auto it = _map; it < _begin.node; it++) {
        if (*it){
            data_allocator.deallocate(*it, trunkSizePerPage);
            *it = nullptr;
        }
    }
    for (auto it = _end.node + 1; it < _map + _trunk_cnt; it++) {
        if (*it){
            data_allocator.deallocate(*it, trunkSizePerPage);
            *it = nullptr;
        }
    }
}
template <class T>
bool operator== (const deque<T>& lhs, const deque<T>& rhs){
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), std::equal_to<T>());
}
template <class T>
bool operator!= (const deque<T>& lhs, const deque<T>& rhs){
    return !operator==(lhs, rhs);
}
template <class T>
bool operator<  (const deque<T>& lhs, const deque<T>& rhs){
    return tiny::lexicographical_compare(lhs.begin(), lhs.end(),lhs.begin(),rhs.end(), std::less<T>());
}
template <class T>
bool operator<= (const deque<T>& lhs, const deque<T>& rhs){
    return tiny::lexicographical_compare(lhs.begin(), lhs.end(),lhs.begin(),rhs.end(), std::less_equal<T>());
}
template <class T>
bool operator>  (const deque<T>& lhs, const deque<T>& rhs){
    return tiny::lexicographical_compare(lhs.begin(), lhs.end(),lhs.begin(),rhs.end(), std::greater<T>());
}
template <class T>
bool operator>= (const deque<T>& lhs, const deque<T>& rhs){
    return tiny::lexicographical_compare(lhs.begin(), lhs.end(),lhs.begin(),rhs.end(), std::greater_equal<T>());
}
}

#endif /* deque_hpp */
