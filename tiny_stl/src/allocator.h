//
//  allocator.h
//  tiny_stl
//
//  Created by junl on 2020/11/9.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef allocator_h
#define allocator_h
#include <cstddef>
#include <type_traits>
#include "util.h"
/*
 template<typename U, typename... Args>
 void construct(U *p, Args&&... args);
 
 template<typename T>
 void destroy(T *p);
 
 template<typename ForwardInterator>
 void destroy(ForwardInterator beg, ForwardInterator end);
 
 template<typename T>
 class allocator{
     typedef T value_type;
     typedef T* pointer;
     typedef T& reference;
     typedef const T* const_pointer;
     typedef const T& const_reference;
     typedef size_t size_type;
     typedef ptrdiff_t difference_type;
     pointer allocate(size_type n);
     void deallocate(pointer p, size_type n);
 
     template<typename U, typename... Args>
     void construct(U *p, Args&&... args);
 
     template<typename U>
     void destroy(U *p);
 
     pointer address(reference __x) const noexcept;
     const_pointer address(const_reference __x) const noexcept;
 };
 */


namespace tiny{
    template<typename U, typename... Args>
    void construct(U *p, Args&&... args){
        //通过定位new表达式调用构造函数
        ::new ((void *)p) U(tiny::forward<Args>(args)...);
    }
    
    template<typename T>
    void _destroy_one(T* p, std::true_type){}
    
    template<typename T>
    void _destroy_one(T* p, std::false_type){
        if (!p) return;
        p->~T();
    }
    template<typename T>
    void destroy(T *p){
        _destroy_one(p, std::is_trivially_destructible<T>());
    }
    
    template<typename ForwardInterator>
    void _destroy_cat(ForwardInterator, ForwardInterator, std::true_type){}
    
    template<typename ForwardInterator>
    void _destroy_cat(ForwardInterator beg, ForwardInterator end, std::false_type){
        for (; beg != end; beg++) {
            destroy(&*beg);
        }
    }
    template<typename ForwardInterator>
    void destroy(ForwardInterator beg, ForwardInterator end){
        _destroy_cat(beg, end, std::is_trivially_destructible<typename ForwardInterator::value_type>{});
    }
    template<typename T>
    class allocator{
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef const T* const_pointer;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        /*
         Allocate block of storage
         Attempts to allocate a block of storage with a size large enough to contain n elements of member type value_type, and returns a pointer to the first element.
         The storage is aligned appropriately for objects of type value_type, but they are not constructed.
         In the standard default allocator, the block of storage is allocated using ::operator new one or more times, and throws bad_alloc if it cannot allocate the total amount of storage requested.
         */
        pointer allocate(size_type n){
            if (n == 0)
                return nullptr;
            return static_cast<pointer>(::operator new[](sizeof(T) * n));
        }
        /*
         释放先前由成员分配分配但尚未释放的存储块。
         调用此成员函数不会销毁数组中的元素。
         在默认分配器中，使用:: operator delete释放存储块。
         @Parameters p
         Pointer to a block of storage previously allocated with allocator::allocate.
         @Parameters n
         Number of elements allocated on the call to allocator::allocate for this block of storage.
         */
        void deallocate(pointer p, size_type n){
            if (!p) return;
            ::operator delete[](p, sizeof(T) * n);
        }
        
        /*
         在指针p所指向的位置构造对象.
         该函数通过将其参数转发给适当的构造函数来就地构造U类型的对象，就像使用了以下代码一样：
         ::new ((void*)p) U (forward<Args>(args)...);
         */
        template<typename U, typename... Args>
        void construct(U *p, Args&&... args){
            //通过定位new表达式调用构造函数
            tiny::construct(p, args...);
        }
        /*
         销毁指针p指向的对象
         该方法会调用U的析构函数, 就像下面这样:
         p->~U();
         */
        template<typename U>
        void destroy(U *p){
            tiny::destroy(p);
        }
        pointer address(reference __x) const noexcept {
            return &__x;
        }
        const_pointer address(const_reference __x) const noexcept {
            return &__x;
        }
    };
};

#endif /* allocator_h */
