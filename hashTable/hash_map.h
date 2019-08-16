//
//  hash_map.h
//  alg-cpp
//
//  Created by junl on 2019/7/20.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef hash_map_hpp
#define hash_map_hpp

#include <stdio.h>
#include <vector>

/*
 散列表是数组的一种扩展结构，它来源于数组，利用的是数组支持下标随机访问元素的特性。
 
 ![IMAGE](quiver-image-url/0F325C9E9BF50CD39E0E45C904EDAFB6.jpg =1142x744)
 
 一个工业级的散列表应该满足下面这些要求：
 
 1. 支持快速查找，删除，添加
 2. 内存占用合理，不能浪费过多的内存空间
 3. 性能稳定，极端情况下，散列表的性能不会退化到无法接受的情况
 
 想要解决这些问题:
 
 1. 设计一个合理的散列函数，劲量让这些数据均匀的分布在每个桶里面,减少散列冲突
 2. 定义装载因子，并且设计动态扩容的策略。涉及到大数据量的搬运时，我们可以这样做。 装载因子触发阈值之后，我们只申请空间，但并不将老数据搬移到新散列表中。当新数据要插入的时候，我们再将新数据插入到散列表中，并将老的散列表中拿出一个放入到新散列表中。
 这样均摊的思想可以让插入做到o(1)
 3. 选择合适的散列冲突解决方法。
 
 常见的散列冲突解决办法有两种:
 
 1. 开放式寻址法
 2. 链表法
 
 开放式寻址法的思想是：先通过hash函数计算出下标，然后判断下标位置是否已经被其他占用了，如果已经被占用，就往后寻找空的位置，然后插入.
 ![IMAGE](quiver-image-url/9A012E1FAA05F55C1D2A3A7C27E45147.jpg =1142x530)
 
 开放式寻址法适用于数据量规模小，装载因子小的时候，这种情况下是很少会冲突的。如果装载因子过大，那么就意味着越容易产生冲突，我们就需要扩容，这就导致这种方法比链表更浪费空间。
 
 ![IMAGE](quiver-image-url/B2CA7EF001C71A15ABDFBE2B8456FB74.jpg =1142x640)
 链表法，因为数据是存储在链表结点里面的，所以这部分开销也是有的。所以，链表的散列冲突比较适合存储大数据对象，大数据量的散列表，同时为了提供效率，我们可以把链表改造为跳表，红黑树等结构，这样极端情况下，查询速度可以达到o(logn)
 
 */

template <typename key_t, typename value_t,typename hash=std::hash<key_t>>
class hash_map {
public:
    typedef std::pair<key_t, value_t> pair_t;
    typedef std::shared_ptr<pair_t> pair_pointer;
    static const size_t primes_[];
    hash_map(){
        size_level=0;
        size=0;
        elements.resize(primes_[size_level]);
        hasher = hash();
    }
    
    value_t& operator[](const key_t &key){
        //查找和插入
        size_t locaiton = hash_location(key);
        if (elements[locaiton] == nullptr) {
            elements[locaiton] = std::make_shared<pair_t>(std::make_pair(key, value_t()));
            size++;
        }
        if (static_cast<double>(size) / elements.size() >= max_load_factor_) {
            //需要扩容
            size_level ++;
            std::vector<pair_pointer> temp;
            temp.resize(primes_[size_level]);
            //数据搬运
            for (auto &v:elements){
                if (v ==nullptr)
                    continue;
                size_t locaiton = hash_location(v->first);
                temp[locaiton]=v;
            }
            elements = std::move(temp);
        }
        return elements[locaiton]->second;
    }
private:
    std::vector<pair_pointer> elements;
    size_t size;
    int size_level;
    double max_load_factor_=0.75;
    hash hasher;
    size_t hash_location(const key_t &key){
        size_t locaiton = hasher(key) % elements.size();
        //开放式寻址
        while (elements[locaiton] != nullptr && elements[locaiton]->first != key) {
            locaiton++;
        }
        return locaiton % elements.size();
    }
};

template <typename key_t, typename value_t, typename hash>
const size_t hash_map<key_t, value_t, hash>::primes_[] = {7, 17, 29, 53, 101, 211, 401, 809, 1601, 3203};  // . ..

#endif /* hash_map_hpp */
