//
//  sampleBrowser.h
//  stack+queue
//
//  Created by junl on 2019/7/18.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef sampleBrowser_hpp
#define sampleBrowser_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include "stack.h"
class sampleBrowser {
public:
    void open(const std::string &url){
        aStack.push(url);
    }
    void goBack(){
        std::string &url = aStack.pop();
        bStack.push(url);
    }
    void goForward(){
        std::string &url = bStack.pop();
        aStack.push(url);
    }
    void checkCurrentPage(){
        std::cout << "checkCurrentPage : " << aStack.topElement() << std::endl;
    }
    
private:
    stack<std::string> aStack;
    stack<std::string> bStack;
};

#endif /* sampleBrowser_hpp */
