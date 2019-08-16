//
//  matching.h
//  string
//
//  Created by junlongj on 2019/7/22.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef matching_h
#define matching_h

#include <string>
#include <vector>
/*
 字符串匹配算法:
 
 BF算法:Brute Force的缩写，暴力匹配算法。思想很简单：
 在主串里，从起始位置分别是0,1,2....n-m且长度为m的n-m+1个子串，分别和substr自己字符匹配.这种算法在实际场景中比较常用，主要原因有二:
    1. 实际场景中，模式串和主串不会太长，并且只要中途没匹配到就会停止，所以比理想o(n*m)要高很多.
    2. 匹配算法思想简单，代码实现也非常简单。满足Keep is Simple and Stupid原则。
 
 */
size_t BF_matching(std::string &str, std::string &substr){
    size_t len = str.size();
    size_t len2 = substr.size();
    if (len == 0 || len2 == 0 || len < len2){
        return -1;
    }
    
    for (int i=0; i<len2-len+1; i++) {
        int k=0;
        while (k<len2 && substr[k] == str[i+k]) {k++;}
        if (k == len2) {
            return i;
        }
    }
    return -1;
}

/*
 RK算法是BF算法的升级版，它还是利用主串的n-m+1的所有子串和模式串进行匹配，不过不是字符匹配，而是hash匹配，
 所以理想情况下，时间复杂度为o(n). 关键点在于hash函数的设计，如果hash函数设计的不好，那么RK算法的复杂度就会退化为o(n*m)
 这里我们先简单把hash函数设计为所以字符之和.当冲突以后，我们在进行原字符匹配。
 */
size_t RK_matching(std::string &str, std::string &substr){
    size_t len = str.size();
    size_t len2 = substr.size();
    if (len == 0 || len2 == 0 || len < len2){
        return -1;
    }
    
    //计算所以子串的hash值
    int hash = 0; //子串的hash
    int hash2 = 0; //匹配传的hash
    for (int j=0; j<len2; j++) {
        hash += str[j];
        hash2 += substr[j];
    }
    if (hash == hash2) {
        return 0;
    }
    for (int i=1; i<=len-len2; i++) {
        //子串之间的hash算法是有一定关联的。
        hash+=str[i+len2-1]-str[i-1];
        if (hash2 != hash)
            continue;
        //哈希相等，进行子串匹配
        int k=0;
        while (k<len2 && substr[k] == str[i+k]) {k++;}
        if (k == len2) {
            return i;
        }
    }
    
    
    return -1;
}

#endif /* matching_h */
