//
//  unordered_map.h
//  tiny_stl
//
//  Created by junl on 2020/11/21.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef unordered_map_hpp
#define unordered_map_hpp
#include "pair.h"
#include "allocator.h"
#include "util.h"
#include "iterator.h"
#include "vector.h"
#include <cassert>
namespace tiny{
#define BUCKET_DEFAULT_SIZE 10
#define PRIME_NUM 99
    
// 1. start with p = 101
// 2. p = next_prime(p * 1.7)
// 3. if p < (2 << 63), go to step 2, otherwise, go to step 4
// 4. end with p = prev_prime(2 << 63 - 1)
static constexpr size_t hashtable_prime_list[] = {
    101ull, 173ull, 263ull, 397ull, 599ull, 907ull, 1361ull, 2053ull, 3083ull,
    4637ull, 6959ull, 10453ull, 15683ull, 23531ull, 35311ull, 52967ull, 79451ull,
    119179ull, 178781ull, 268189ull, 402299ull, 603457ull, 905189ull, 1357787ull,
    2036687ull, 3055043ull, 4582577ull, 6873871ull, 10310819ull, 15466229ull,
    23199347ull, 34799021ull, 52198537ull, 78297827ull, 117446801ull, 176170229ull,
    264255353ull, 396383041ull, 594574583ull, 891861923ull, 1337792887ull,
    2006689337ull, 3010034021ull, 4515051137ull, 6772576709ull, 10158865069ull,
    15238297621ull, 22857446471ull, 34286169707ull, 51429254599ull, 77143881917ull,
    115715822899ull, 173573734363ull, 260360601547ull, 390540902329ull,
    585811353559ull, 878717030339ull, 1318075545511ull, 1977113318311ull,
    2965669977497ull, 4448504966249ull, 6672757449409ull, 10009136174239ull,
    15013704261371ull, 22520556392057ull, 33780834588157ull, 50671251882247ull,
    76006877823377ull, 114010316735089ull, 171015475102649ull, 256523212653977ull,
    384784818980971ull, 577177228471507ull, 865765842707309ull, 1298648764060979ull,
    1947973146091477ull, 2921959719137273ull, 4382939578705967ull, 6574409368058969ull,
    9861614052088471ull, 14792421078132871ull, 22188631617199337ull, 33282947425799017ull,
    49924421138698549ull, 74886631708047827ull, 112329947562071807ull, 168494921343107851ull,
    252742382014661767ull, 379113573021992729ull, 568670359532989111ull, 853005539299483657ull,
    1279508308949225477ull, 1919262463423838231ull, 2878893695135757317ull, 4318340542703636011ull,
    6477510814055453699ull, 9716266221083181299ull, 14574399331624771603ull, 18446744073709551557ull
};
#define UNORDERED_DECLARE  template <class Key, class T, class Hash, class Pred>
#define UNORDERED_NSP unordered_map<Key, T, Hash, Pred>
template<class Key, class Value>
struct unordered_map_node{
    typedef tiny::pair<const Key, Value> element_type;
    unordered_map_node *next;
    tiny::pair<const Key, Value> value;
    unordered_map_node() = default;
    unordered_map_node(const element_type &val):value(val), next(nullptr){}
    unordered_map_node(element_type &&val):value(tiny::move(val)), next(nullptr){}
};

UNORDERED_DECLARE
class unordered_map;
template<class Key, class Value, class Pointer, class Reference, class Hash, class Key_equal>
struct unordered_map_iterator : iterator<tiny::forward_iterator_tag, tiny::pair<const Key, Value>>{
    typedef tiny::pair<const Key, Value> value_type;
    typedef Pointer pointer;
    typedef Reference reference;
    typedef ptrdiff_t difference_type;
    typedef unordered_map_iterator self_type;
    typedef unordered_map_iterator<Key, Value, value_type*, value_type&, Hash, Key_equal> iterator_type;
    typedef unordered_map_iterator<Key, Value, const value_type*, const value_type&, Hash, Key_equal> const_iterator_type;
    typedef unordered_map_node<const Key, Value>* node_ptr;
    typedef const unordered_map<Key, Value, Hash, Key_equal>* hashtable_ptr;
    //vals
    node_ptr node = nullptr;
    hashtable_ptr ht = nullptr;
    
    unordered_map_iterator() = default;
    unordered_map_iterator(node_ptr nptr, const hashtable_ptr t):node(nptr), ht(t){}
    unordered_map_iterator(const iterator_type &lhs):node(lhs.node), ht(lhs.ht){}
    unordered_map_iterator(const const_iterator_type &lhs):node(lhs.node), ht(lhs.ht){}
    unordered_map_iterator& operator=(const unordered_map_iterator &lhs){
        if (&lhs != this){
            node = lhs.node;
            ht = lhs.ht;
        }
        return *this;
    }
    bool operator==(const self_type &rhs){
        return node == rhs.node && ht == rhs.ht;
    }
    bool operator!=(const self_type &rhs){
        return !(*this == rhs);
    }
    reference operator*() {
        return node->value;
    }
    pointer operator->(){
        return &(operator*());
    }
    self_type& operator++() {
        assert(node != nullptr);
        node_ptr old = node;
        node = node->next;
        if (node == nullptr){
            auto idx = ht->hash(old->value.first);
            while (!node && ++idx < ht->_bucketCnt)
                node = ht->_buckets[idx];
        }
        return *this;
    }
    self_type operator++(int) {
        self_type tmp(*this);
        ++*this;
        return tmp;
    }
};

template<class Key, class Value, class Pointer, class Reference>
struct unordered_map_local_iterator : iterator<tiny::forward_iterator_tag, tiny::pair<const Key, Value>>{
    typedef typename unordered_map_node<const Key, Value>::element_type value_type;
    typedef Pointer pointer;
    typedef Reference reference;
    typedef ptrdiff_t difference_type;
    typedef unordered_map_local_iterator self_type;
    typedef unordered_map_local_iterator<Key, Value, value_type*, value_type&> iterator_type;
    typedef unordered_map_local_iterator<Key, Value, const value_type*, const value_type&> const_iterator_type;
    typedef unordered_map_node<const Key, Value>* node_ptr;
    //vals
    node_ptr node = nullptr;
    unordered_map_local_iterator() = default;
    unordered_map_local_iterator(node_ptr ptr):node(ptr){}
    unordered_map_local_iterator(const iterator_type & rhs): node(rhs.node){}
    unordered_map_local_iterator(const const_iterator_type & rhs): node(rhs.node){}
    unordered_map_local_iterator& operator=(const iterator_type & rhs){
        if (this != &rhs){
            node = rhs.node;
        }
        return *this;
    }
    unordered_map_local_iterator& operator=(const const_iterator_type & rhs){
        if (this != &rhs){
            node = rhs.node;
        }
        return *this;
    }
    bool operator==(const self_type &rhs){
        return node == rhs.node;
    }
    bool operator!=(const self_type &rhs){
        return node != rhs.node;
    }
    reference operator*() {
        return node->value;
    }
    pointer operator->(){
        return &(operator*());
    }
    self_type& operator++() {
        assert(node != nullptr);
        node = node->next;
        return *this;
    }
    self_type operator++(int) {
        self_type tmp(*this);
        ++*this;
        return tmp;
    }
};

template <class Key, class T, class Hash = std::hash<Key>, class Pred = std::equal_to<Key>>
class unordered_map {
public:
    typedef Key key_type;
    typedef T mapped_type;
//        typedef typename unordered_map_node<const Key, T>::element_type value_type;
    typedef tiny::pair<const Key, T> value_type;
    typedef Hash hasher;
    typedef Pred key_equal;
    typedef tiny::allocator<value_type> allocator_type;
    typedef tiny::allocator<unordered_map_node<const Key, T>> node_allocator_type;
    typedef typename allocator_type::reference  reference;
    typedef typename allocator_type::const_reference  const_reference;
    typedef typename allocator_type::pointer  pointer;
    typedef typename allocator_type::const_pointer  const_pointer;
    typedef unordered_map_iterator<Key, T, value_type*, value_type&, Hash, Pred> iterator;
    typedef unordered_map_iterator<Key, T, const value_type*, const value_type&, Hash, Pred> const_iterator;
    typedef unordered_map_local_iterator<Key, T, value_type*, value_type&> local_iterator;
    typedef unordered_map_local_iterator<Key, T, const value_type*, const value_type&> const_local_iterator;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef unordered_map_node<const Key, T>* node_ptr;
    
    friend unordered_map_iterator<Key, T, pointer, reference, hasher, key_equal>;
    friend unordered_map_iterator<Key, T, const_pointer, const_reference, hasher, key_equal>;

private:
    tiny::vector<node_ptr> _buckets;
    size_type _bucketCnt;
    size_type _size;
    hasher _hash;
    key_equal _equal;
    float _maxLoadFactor = 1.0;
public:
    //构造，复制，拷贝
    explicit unordered_map(size_type n = 0, const hasher& hf = hasher(), const key_equal& eql = key_equal()):  _hash(hf), _equal(eql) {
        _init_bucket(n);
    }
    //range
    template<class InputIterator, typename std::enable_if<
                    tiny::is_input_iterator<InputIterator>::value &&
                    std::is_constructible<value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                    int>::type = 0>
    unordered_map(InputIterator first, InputIterator last , size_type n = 0, const hasher& hf = hasher(), const key_equal& eql = key_equal()): _hash(hf), _equal(eql) {
        _init_bucket(n);
        _assign(first, last);
    };
    //copy
    unordered_map(const unordered_map& rhs):_hash(rhs._hash), _equal(rhs._equal), _maxLoadFactor(rhs._maxLoadFactor){
        _init_bucket(rhs._bucketCnt);
        _assign(rhs.cbegin(), rhs.cend());
    }
    //move
    unordered_map(unordered_map &&rhs):_buckets(tiny::move(rhs._buckets)), _bucketCnt(rhs._bucketCnt), _size(rhs._size), _hash(rhs._hash), _equal(rhs._equal), _maxLoadFactor(rhs._maxLoadFactor){
        rhs._buckets = {};
        rhs._size = 0;
        rhs._bucketCnt = 0;
        rhs._maxLoadFactor = 0;
    };
    unordered_map(std::initializer_list<value_type> il, size_type n = 0, const hasher& hf = hasher(),const key_equal& eql = key_equal()): _hash(hf), _equal(eql) {
        _init_bucket(n);
        _assign(il.begin(), il.end());
    }
    //operator=
    unordered_map& operator=(const unordered_map &ump){
        if (&ump != this){
            unordered_map tmp(ump);
            this->swap(tmp);
        }
        return *this;
    }
    unordered_map& operator=(unordered_map && ump){
        if (&ump != this){
            unordered_map tmp(tiny::move(ump));
            this->swap(tmp);
        }
        return *this;
    }
    unordered_map& operator=(std::initializer_list<value_type> il ){
        unordered_map tmp(il);
        using std::swap;
        this->swap(tmp);
        return *this;
    }
    ~unordered_map() {clear();};
    //capacity
    bool empty() const noexcept{return _size == 0;}
    size_type size() const noexcept {return _size;};
    //Iterators
    iterator begin() noexcept {return iterator(_find_first_vaild_node(), this);}
    const_iterator begin() const noexcept {return const_iterator(_find_first_vaild_node(), this);}
    local_iterator begin(size_type n) {assert(n < _bucketCnt); return local_iterator(_buckets[n]);}
    const_local_iterator begin(size_type n) const {assert(n < _bucketCnt); return const_local_iterator(_buckets[n]);}
    iterator end() noexcept {return iterator(nullptr, this);};
    const_iterator end() const noexcept {return const_iterator(nullptr, this);};
    local_iterator end(size_type n) {assert(n < _bucketCnt); return local_iterator(nullptr);}
    const_local_iterator end(size_type n) const {assert(n < _bucketCnt); return const_local_iterator(nullptr);};
    const_iterator cbegin() const noexcept {
        return const_iterator(_find_first_vaild_node(), this);};
    const_local_iterator cbegin ( size_type n ) const {assert(n < _bucketCnt); return const_local_iterator(nullptr);};
    const_iterator cend() const noexcept {return const_iterator(nullptr, this);};
    const_local_iterator cend(size_type n) const {assert(n < _bucketCnt); return const_local_iterator(nullptr);};
    
    //Element access
    mapped_type& operator[](const key_type &k);
    mapped_type& operator[](key_type &&k);
    mapped_type& at(const key_type &k);
    mapped_type& at(key_type &&k);
    //Element lookup
    iterator find(const key_type &k) {
        return iterator(_find(k), this);
    };
    const_iterator find(const key_type &k) const {
        return const_iterator(_find(k), this);
    }
    size_type count(const key_type &k) const {
        return _find(k) != nullptr ? 1 : 0;
    }
    //Modifiers
    template<class... Args>
    tiny::pair<iterator, bool> emplace(Args&&... args);
    tiny::pair<iterator, bool> insert(const value_type& val) {
        return emplace(val);
    };
    template<class P>
    tiny::pair<iterator, bool> insert(P &&val) {
        return emplace(tiny::move(val));
    }
    template <class InputIterator, typename std::enable_if<
                                tiny::is_input_iterator<InputIterator>::value &&
                                std::is_constructible<value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                                int>::type = 0>
    void insert ( InputIterator first, InputIterator last );
    void insert ( std::initializer_list<value_type> il ) {
        insert(il.begin(), il.end());
    };
    iterator erase(const_iterator position);
    size_type erase(const key_type &k);
    iterator erase(const_iterator first, const_iterator last);
    void clear();
    void swap (unordered_map& ump );
    //Buckets
    size_type bucket_count() const noexcept {return _bucketCnt;};
    /*
     Returns the number of elements in bucket n.

     A bucket is a slot in the container's internal hash table to which elements are assigned based on the hash value of their key.

     The number of elements in a bucket influences the time it takes to access a particular element in the bucket. The container automatically increases the number of buckets to keep the load factor (which is the average bucket size) below its max_load_factor.
     */
    size_type bucket_size(size_type n) const;
    size_type bucket(const key_type &k) const {
        return hash(k);
    }
    float load_factor() const noexcept {
        return  _bucketCnt ? (float)_size / (float)_bucketCnt : 0;
    }
    float max_load_factor() const noexcept {
        return _maxLoadFactor;
    }
    void max_load_factor(float z) {
        _maxLoadFactor = z;
    }
    //TODO:
    /*
     Sets the number of buckets in the container to n or more.

     If n is greater than the current number of buckets in the container (bucket_count), a rehash is forced. The new bucket count can either be equal or greater than n.

     If n is lower than the current number of buckets in the container (bucket_count), the function may have no effect on the bucket count and may not force a rehash.

     A rehash is the reconstruction of the hash table: All the elements in the container are rearranged according to their hash value into the new set of buckets. This may alter the order of iteration of elements within the container.

     Rehashes are automatically performed by the container whenever its load factor is going to surpass its max_load_factor in an operation.

     Notice that this function expects the number of buckets as argument. A similar function exists, unordered_map::reserve, that expects the number of elements in the container as argument.
     */
    void rehash(size_type n);
    void reserve(size_type count)
    { rehash(static_cast<size_type>((float)count / max_load_factor() + 0.5f)); }
private:
    static allocator_type data_allocator;
    static node_allocator_type node_allocator;
    void _init_bucket(size_type n);
    size_type hash(const key_type & key) const {
        return _hash(key) % _bucketCnt;
    }
    size_type _next_size(size_type n) {
        const size_type* first = hashtable_prime_list;
        const size_type* last = hashtable_prime_list + PRIME_NUM;
        const size_type* pos = std::lower_bound(first, last, n);
        n = pos == last ? *(last - 1) : *pos;
        return n;
    }
    
    void rehash_ifneed(size_type n);
    void replace_bucket(size_type n);
    template<class ...Args>
    node_ptr _create_node(Args... args);
    void _free_node(node_ptr node);
    node_ptr _find_local_equal(size_type position, const key_type &key) const;
    node_ptr _find(const key_type &k) const;
    node_ptr _find_first_vaild_node() const;
    //asign
    template<class InputIterator>
    void _assign(InputIterator first, InputIterator last);
};
UNORDERED_DECLARE
typename UNORDERED_NSP::allocator_type UNORDERED_NSP::data_allocator;
UNORDERED_DECLARE
typename tiny::allocator<unordered_map_node<const Key, T>> UNORDERED_NSP::node_allocator;
UNORDERED_DECLARE
template<class ...Args>
typename UNORDERED_NSP::node_ptr
UNORDERED_NSP::_create_node(Args... args){
    auto node = node_allocator.allocate(1);
    data_allocator.construct(&(node->value), tiny::forward<Args>(args)...);
    node->next = nullptr;
    return node;
}
UNORDERED_DECLARE
void UNORDERED_NSP::_free_node(node_ptr node){
    data_allocator.destroy(&(node->value));
    node_allocator.deallocate(node, 1);
}
UNORDERED_DECLARE
typename UNORDERED_NSP::node_ptr
UNORDERED_NSP::_find_local_equal(size_type position, const key_type &key) const{
    for (auto it = _buckets[position]; it != nullptr; it = it->next) {
        if (_equal(it->value.first, key)) {
            return it;
        }
    }
    return nullptr;
}
UNORDERED_DECLARE
void UNORDERED_NSP::_init_bucket(size_type n){
    n = _next_size(n);
    _buckets.resize(n, nullptr);
    _bucketCnt = n;
    _size = 0;
}
UNORDERED_DECLARE
template<typename InputIterator>
void UNORDERED_NSP::_assign(InputIterator first, InputIterator last){
    _size = static_cast<size_type>(tiny::distance(first, last));
    for (; first != last; first++) {
        size_type pos = hash(first->first);
        auto node = _create_node(*first);
        if (_buckets[pos] == nullptr){
            _buckets[pos] = node;
        }else{
            //如果已经存储了{key, oldValue}跳过
            if (_find_local_equal(pos, first->first)){
                _free_node(node);
                continue;
            }
            node->next = _buckets[pos];
            _buckets[pos] = node;
        }
    }
}

UNORDERED_DECLARE
typename UNORDERED_NSP::node_ptr
UNORDERED_NSP::_find_first_vaild_node() const{
    for (size_type i = 0; i < _bucketCnt; i++) {
        if (_buckets[i] != nullptr)
            return _buckets[i];
    }
    return nullptr;
}

UNORDERED_DECLARE
typename UNORDERED_NSP::node_ptr
UNORDERED_NSP::_find(const key_type &k) const{
    size_type pos = hash(k);
    if (_buckets[pos] == nullptr) {
        return nullptr;
    }else{
        auto ret = _find_local_equal(pos, k);
        return ret;
    }
}

UNORDERED_DECLARE
void UNORDERED_NSP::clear() {
    for (size_type i = 0; i < _bucketCnt; i++) {
        if (_buckets[i] == nullptr) continue;
        for (node_ptr node = _buckets[i]; node;) {
            node_ptr pToBeDeleteNode = node;
            _free_node(pToBeDeleteNode);
            node = node->next;
        }
        _buckets[i] = nullptr;
    }
}
UNORDERED_DECLARE
typename UNORDERED_NSP::mapped_type&
UNORDERED_NSP::operator[](const key_type &k){
    auto ret = emplace(k, mapped_type());
    return ret.first->second;
}
UNORDERED_DECLARE
typename UNORDERED_NSP::mapped_type&
UNORDERED_NSP::operator[](key_type &&k){
    auto ret = emplace(tiny::move(k), mapped_type());
    return ret.first->second;
}

UNORDERED_DECLARE
typename UNORDERED_NSP::mapped_type&
UNORDERED_NSP::at(const key_type &k){
    auto it = _find(k);
    if (!it) throw std::out_of_range("No Key.");
    return it->value.second;
}

UNORDERED_DECLARE
typename UNORDERED_NSP::mapped_type&
UNORDERED_NSP::at(key_type &&k){
    auto it = _find(k);
    if (!it) throw std::out_of_range("No Key.");
    return it->value.second;
}
UNORDERED_DECLARE
void UNORDERED_NSP::swap(unordered_map& ump ){
    tiny::swap(_buckets, ump._buckets);
    tiny::swap(_bucketCnt, ump._bucketCnt);
    tiny::swap(_size, ump._size);
    tiny::swap(_hash, ump._hash);
    tiny::swap(_equal, ump._equal);
}

UNORDERED_DECLARE
template<class... Args>
tiny::pair<typename UNORDERED_NSP::iterator, bool>
UNORDERED_NSP::emplace(Args&&... args){
    auto node = _create_node(tiny::forward<Args>(args)...);
    
    auto *old = _find(node->value.first);
    if (old != nullptr) {
        _free_node(node);
        return {iterator(old, this), false};
    }
    //插入新元素
    rehash_ifneed(1);
    size_type pos = hash(node->value.first);
    node->next = _buckets[pos];
    _buckets[pos] = node;
    _size++;
    return {iterator(node, this), true};
}

UNORDERED_DECLARE
template <class InputIterator, typename std::enable_if<
                    tiny::is_input_iterator<InputIterator>::value &&
                    std::is_constructible<typename UNORDERED_NSP::value_type, typename tiny::iterator_traits<InputIterator>::reference>::value,
                    int>::type>
void UNORDERED_NSP::insert (InputIterator first, InputIterator last ){
    rehash_ifneed(static_cast<size_type>(tiny::distance(first, last)));
    for (; first != last; first++) {
        auto *old = _find(first->first);
        if (old != nullptr) {
            continue;
        };
        auto node = _create_node(*first);
        //插入新元素
        size_type pos = hash(node->value.first);
        node->next = _buckets[pos];
        _buckets[pos] = node;
        _size++;
    }
}

UNORDERED_DECLARE
typename UNORDERED_NSP::size_type
UNORDERED_NSP::erase(const key_type &k){
    size_type pos = hash(k);
    if (_buckets[pos] == nullptr) {
        return 0;
    }else{
        node_ptr it = _buckets[pos], pre = nullptr;
        bool isFind = false;
        for (it = _buckets[pos]; it != nullptr && !isFind; pre = it, it = it->next) {
            if (_equal(it->value.first, k)) {
                isFind = true;
                break;
            }
        }
        if (!isFind) return 0;
        //存在node
        node_ptr pToDeleteNode = it;
        if (!pre) {
            _buckets[pos] = it->next;
        }else{
            pre->next = it->next;
        }
        _free_node(pToDeleteNode);
        --_size;
        return 1;
    }
}

UNORDERED_DECLARE
typename UNORDERED_NSP::iterator
UNORDERED_NSP::erase(const_iterator position){
    size_type pos = hash(position->first);
    node_ptr it = _buckets[pos], pre = nullptr;
    bool isFind = false;
    for (it = _buckets[pos]; it != nullptr && !isFind; pre = it, it = it->next) {
        if (position.node == it) {
            isFind = true;
            break;
        }
    }
    if (!isFind) throw std::runtime_error("erase position error.");
    //存在node
    node_ptr pToDeleteNode = it;
    if (!pre) {
        _buckets[pos] = it->next;
    }else{
        pre->next = it->next;
    }
    auto ret = iterator(it->next, this);
    _free_node(pToDeleteNode);
    --_size;
    return ret;
}
UNORDERED_DECLARE
typename UNORDERED_NSP::iterator
UNORDERED_NSP::erase(const_iterator first, const_iterator last){
    iterator it;
    for (; first != last; first++) {
        it = erase(first);
    }
    return it;
}
UNORDERED_DECLARE
typename UNORDERED_NSP::size_type
UNORDERED_NSP::bucket_size(size_type n) const{
    size_type ret = 0;
    for (auto it = _buckets[n]; it != nullptr; it = it->next, ret++)
        ;
    return ret;
}
UNORDERED_DECLARE
void UNORDERED_NSP::rehash(size_type n){
    n = _next_size(n);
    if (n > _bucketCnt){
        //rehash
        replace_bucket(n);
    }else{
        if ((float)_size / (float)n < max_load_factor() - 0.25 &&
            (float)n < _bucketCnt * 0.75) {//worth rehash
            replace_bucket(n);
        }
    }
}
UNORDERED_DECLARE
void UNORDERED_NSP::replace_bucket(size_type n){
//    if (_size == 0) return;
    std::cout << "rehash------" << _bucketCnt << "  =>  " << n << std::endl;
    tiny::vector<node_ptr> new_buckets(n, nullptr);
    for(size_type i = 0; i < _bucketCnt; i++){
        node_ptr it = _buckets[i], next = nullptr;
        for (; it != nullptr; it = next) {
            size_type pos = _hash(it->value.first) % n;
            next = it->next;
            it->next = new_buckets[pos];
            new_buckets[pos] = it;
        }
    }
    tiny::swap(_buckets, new_buckets);
    _bucketCnt = n;
}
UNORDERED_DECLARE
void swap(const UNORDERED_NSP &lhs, const UNORDERED_NSP &rhs){
    lhs.swap(rhs);
};
UNORDERED_DECLARE
void UNORDERED_NSP::rehash_ifneed(size_type n){
    n += _size;
    if (_bucketCnt > 0 && ((float) n / (float)_bucketCnt) > max_load_factor())
        rehash(n);
        
}
}

#endif /* unordered_map_hpp */
