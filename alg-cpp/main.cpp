//
//  main.cpp
//  alg-cpp
//
//  Created by junl on 2019/7/17.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

std::string FilterRepeatString(std::string &s){
    if (s.empty()) return s;
    s+='%';
    std::string result;
    int i =0;
    int j =0;
    while (j<s.length()) {
        if (s[i] == s[j]) {
            j++;
        }else{
            int count = j-i;
            if (count == 1) {
                result+=s[i];
            }else{
                result+=s[i];
                result += std::to_string(count);
            }
            i=j;
            j++;
        }
    }
    return result;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::string s{"aabccccaab"};
    std::cout << FilterRepeatString(s) << std::endl;
    return 0;
}
