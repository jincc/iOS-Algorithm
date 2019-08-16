//
//  illegalParameterValue.hpp
//  ALG-DS
//
//  Created by junl on 2019/4/22.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef illegalParameterValue_hpp
#define illegalParameterValue_hpp
#include <iostream>
#include <string>

class illegalParameterValue {
public:
    illegalParameterValue(): message("Illegal parameter value"){}
    illegalParameterValue(const std::string& theMessage)  {message = theMessage;}
    void outputMessage() {std::cout << message << std::endl;}
private:
    std::string message;
};

class stackEmpty {
    
public:
    
};


#endif /* illegalParameterValue_hpp */
