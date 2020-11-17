//
//  type_traits.h
//  tiny_stl
//
//  Created by junl on 2020/11/13.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef type_traits_hpp
#define type_traits_hpp

namespace tiny{
    template<class T, T v>
    struct m_integer_constant{
        static constexpr T value = v;
    };
    template<bool b>
    using m_bool_constant = m_integer_constant<bool, b>;
    
    typedef m_bool_constant<true> m_true_type;
    typedef m_bool_constant<false> m_false_type;
}
#endif /* type_traits_hpp */
