//
//  iterator.h
//  tiny_stl
//
//  Created by junl on 2020/11/12.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef iterator_h
#define iterator_h

#include <stdio.h>
#include "type_traits.h"
namespace tiny{
    //五种迭代器类型
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};
    
    // iterator 模板
    template <class Category, class T, class Distance = ptrdiff_t,
    class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef Category                             iterator_category;
        typedef T                                    value_type;
        typedef Pointer                              pointer;
        typedef Reference                            reference;
        typedef Distance                             difference_type;
    };
    
    // iterator traits
    template <class T>
    struct has_iterator_cat
    {
    private:
        struct two { char a; char b; };
        template <class U> static two test(...);
        template <class U> static char test(typename U::iterator_category* = 0);
    public:
        static const bool value = sizeof(test<T>(0)) == sizeof(char);
    };
    
    template <class Iterator, bool>
    struct iterator_traits_impl {};
    
    template <class Iterator>
    struct iterator_traits_impl<Iterator, true>
    {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
        typedef typename Iterator::difference_type   difference_type;
    };
    
    template <class Iterator, bool>
    struct iterator_traits_helper {};
    
    template <class Iterator>
    struct iterator_traits_helper<Iterator, true>
    : public iterator_traits_impl<Iterator,
    std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
    std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>
    {
    };
    
    // 萃取迭代器的特性
    template <class Iterator>
    struct iterator_traits
    : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {};
    
    // 针对原生指针的偏特化版本
    template <class T>
    struct iterator_traits<T*>
    {
        typedef random_access_iterator_tag           iterator_category;
        typedef T                                    value_type;
        typedef T*                                   pointer;
        typedef T&                                   reference;
        typedef ptrdiff_t                            difference_type;
    };
    
    template <class T>
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag           iterator_category;
        typedef T                                    value_type;
        typedef const T*                             pointer;
        typedef const T&                             reference;
        typedef ptrdiff_t                            difference_type;
    };
    
    template <class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
    struct has_iterator_cat_of
    : public m_bool_constant<std::is_convertible<
    typename iterator_traits<T>::iterator_category, U>::value>
    {
    };
    
    // 萃取某种迭代器
    template <class T, class U>
    struct has_iterator_cat_of<T, U, false> : public m_false_type {};
    
    template <class Iter>
    struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag> {};
    
    template <class Iter>
    struct is_output_iterator : public has_iterator_cat_of<Iter, output_iterator_tag> {};
    
    template <class Iter>
    struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag> {};
    
    template <class Iter>
    struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};
    
    template <class Iter>
    struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag> {};
    
    template <class Iterator>
    struct is_iterator :
    public m_bool_constant<is_input_iterator<Iterator>::value ||
    is_output_iterator<Iterator>::value>
    {
    };
    //获取迭代器类型
    template<class Iterator>
    typename iterator_traits<Iterator>::iterator_category
    getIteratorCategory(){
        typedef typename iterator_traits<Iterator>::iterator_category  category_type;
        return category_type();
    }
    //计算两个迭代器之间的距离
    template<class Iterator>
    typename iterator_traits<Iterator>::difference_type
    distance(Iterator start, Iterator end, input_iterator_tag){
        typename iterator_traits<Iterator>::difference_type n = 0;
        for(; start != end; start++, n++)
            ;
        return n;
    }

    template<class Iterator>
    typename iterator_traits<Iterator>::difference_type
    distance(Iterator start, Iterator end, random_access_iterator_tag){
        return end - start;
    }

    template<class Iterator>
    typename iterator_traits<Iterator>::difference_type
    distance(Iterator start, Iterator end){
        return distance(start, end, getIteratorCategory<Iterator>());
    }
    
    //让迭代器前进n个位置
    template<class Iterator, class Distance>
    void advance(Iterator &start, Distance n, input_iterator_tag){
        while (n--) {
            ++start;
        };
    }
    template<class Iterator, class Distance>
    void advance(Iterator &start, Distance n, bidirectional_iterator_tag){
        if (n > 0){
            while (n--) {
                ++start;
            };
        }else{
            while (n++) {
                ++start;
            };
        }
    }
    template<class Iterator, class Distance>
    void advance(Iterator &start, Distance n, random_access_iterator_tag){
        start += n;
    }
    template<class Iterator, class Distance>
    void advance(Iterator &start, Distance n){
        advance(start, n, getIteratorCategory<Iterator>());
    }
    
    //反向迭代器模板，始终指向正常迭代器的前一个位置
    template<class Iterator>
    class reverse_iterator{
    public:
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef Iterator iterator_type;
        
        reverse_iterator() = default;
        explicit reverse_iterator(iterator_type it):current(it){};
        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter> & rev_it):current(rev_it.current){}
        
        iterator_type
        base() const {return current;}
        
        reference
        operator*() const {
            iterator_type tmp(current);
            --tmp;
            return *tmp;
        }
        
        reverse_iterator
        operator+(difference_type n) const {
            return reverse_iterator(current - n);
        }
        
        reverse_iterator&
        operator++(){
            --current;
            return *this;
        }
        reverse_iterator
        operator++(int){
            reverse_iterator temp(*this);
            --current;
            return temp;
        }
        reverse_iterator&
        operator+=(difference_type n){
            current-=n;
            return *this;
        }
        reverse_iterator
        operator-(difference_type n) const {
            return reverse_iterator(current + n);
        }
        reverse_iterator&
        operator--(){
            ++current;
            return *this;
        }
        reverse_iterator
        operator--(int){
            reverse_iterator temp(*this);
            ++current;
            return temp;
        }
        reverse_iterator&
        operator-=(difference_type n){
            current+=n;
            return *this;
        }
        pointer
        operator->() const {
            return &operator*();
        }
        reference
        operator[](difference_type n) const
        {
          return *(*this + n);
        }
    private:
        iterator_type current;
    };
    template <class Iterator1, class Iterator2>
      bool operator== (const reverse_iterator<Iterator1>& lhs,
                       const reverse_iterator<Iterator2>& rhs){
          return lhs.base() == rhs.base();
      }

    template <class Iterator1, class Iterator2>
      bool operator!= (const reverse_iterator<Iterator1>& lhs,
                       const reverse_iterator<Iterator2>& rhs){
          return lhs.base() != rhs.base();
      }

    template <class Iterator1, class Iterator2>
      bool operator<  (const reverse_iterator<Iterator1>& lhs,
                       const reverse_iterator<Iterator2>& rhs){
          return lhs.base() > rhs.base();
      }

    template <class Iterator1, class Iterator2>
      bool operator<= (const reverse_iterator<Iterator1>& lhs,
                       const reverse_iterator<Iterator2>& rhs){
          return lhs.base() >= rhs.base();
      }

    template <class Iterator1, class Iterator2>
      bool operator>  (const reverse_iterator<Iterator1>& lhs,
                       const reverse_iterator<Iterator2>& rhs){
          return lhs.base() < rhs.base();
      }

    template <class Iterator1, class Iterator2>
      bool operator>= (const reverse_iterator<Iterator1>& lhs,
                       const reverse_iterator<Iterator2>& rhs){
          return lhs.base() <= rhs.base();
      }

    template <class Iterator>
    reverse_iterator<Iterator>
    operator+ (typename reverse_iterator<Iterator>::difference_type n,
                                          const reverse_iterator<Iterator>& rev_it){
        return rev_it + n;
    }

    template<class Iterator1, class Iterator2>
    auto operator-(const Iterator1 &lhs, const Iterator2 &rhs) -> decltype(rhs.base() - lhs.base()) {
        return rhs.base() - lhs.base();
    }
}
#endif /* iterator_h */
