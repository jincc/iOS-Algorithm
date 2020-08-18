//
//  main.cpp
//  string
//
//  Created by junlongj on 2019/7/22.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "matching.h"
#include "replaceSpace.h"
#include "Permutation.h"
#include "FirstNotRepeatingChar.h"
#include "ReverseSentence.h"
#include "StrToInt.h"
#include "match.h"
#include "longestCommonPrefix.h"
#include "strStr.h"
#include "addBinary.h"
#include "lengthOfLastWord.h"
#include "lengthOfLongestSubstring.h"
#include "longestPalindrome.h"
#include "zigzag_conversion.h"
#include "string_to_integer_atoi.h"
#include "integer_to_roman.h"
#include "removeRepeatChar.h"
#include <string.h>


typedef struct context_t{
    char *s;
    char *p;
    int slen;
    int plen;
}context_t;
bool bt(context_t *ctx, int sidx, int pidx);
bool isMatch(char * s, char * p){
    if (s == NULL || p == NULL)
        return false;
    context_t context = {s, p, static_cast<int>(strlen(s)), static_cast<int>(strlen(p))};
    return bt(&context, 0, 0);
}

bool bt(context_t *ctx, int sidx, int pidx){
    if (pidx == ctx->plen){
        return sidx == ctx->slen;
    }
    char pc = ctx->p[pidx];
    if (pidx+1 < ctx->plen && ctx->p[pidx+1] == '*'){
        if (sidx < ctx->plen && (ctx->p[pidx] == ctx->s[sidx]  || ctx->p[pidx] == '.'))
            return bt(ctx, sidx+1, pidx) || bt(ctx, sidx, pidx+2);
        else
            return bt(ctx, sidx, pidx+2);
    }else if (ctx->p[pidx] == ctx->s[sidx] || ctx->p[pidx] == '.'){
        return bt(ctx, sidx+1, pidx+1);
    }else{
        return false;
    }
}

class Change {
public:
    int countChanges(vector<string> dic, int n, string s, string t) {
        // write code here
        if (dic.empty() || s.empty() || t.empty())
            return 0;
        map<string, bool> m;
        for(string &s: dic)
            m[s] = true;
        countChanges(dic,m, n, 0, s, t);
        if (result == INT_MAX)
            return -1;
        return result;
    }
    void countChanges(vector<string> dic,map<string, bool> &m, int n, int cnt, string s, string t){
        if (s == t){
            result = min(result, cnt);
            return;
        }
        for(int i=0 ;i < s.length();i++){
            if (s[i] != t[i]){
                char c = s[i];
                s[i] = t[i];
                if (m.count(s) != 0 ){
                    countChanges(dic,m, n,cnt+1, s, t);
                }
                s[i] = c;
            }
        }
    }
private:
    int result = INT_MAX;
};

class Solution2 {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        if (s1.empty() || s2.empty() || n1 <= 0 || n2 <= 0)
            return 0;
        
        string S1 = repeat(s1, n1);
        string S2 = repeat(s2, n2);
        return count(S1, S2);
    }
    int count(string &S1, string &S2){
        string S = S2;
        int i = 0;
        if (substr(S1, S, i) == false)
            return 0;
        int result = 1, preIdx = i;
        while(substr(S1, S + S, i)){
            result += result;
            S += S;
            preIdx = i;
        }
        //还剩S1 =  S + xx
        string S3 = S1.substr(preIdx,S1.length() - preIdx);
        return result + count(S3, S2);
    }
    string repeat(string &s, int n1){
        string result;
        for(int i=0; i < n1; i++){
            result += s;
        }
        return result;
    }
    //s2是否存在s1中
    bool substr(string &s1, string s2, int &idx){
        int i, j;
        for(i=j=0; i < s1.length(); i++){
            if (j == s2.length()){
                idx = i;
                return true;
            }
            else if (s1[i] == s2[j])
                j++;
        }
        idx = i;
        return j == s2.length();
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace std;
    string a = "Hello, World!\n";
    string b = "Wo";
    cout << "BF: " << BF_matching(a, b) << endl;
    cout << "RK: " << RK_matching(a, b) << endl;
    
    codinginterviews::test_replaceSpace();
    codinginterviews::test_Permutation();
    codinginterviews::test_FirstNotRepeatingChar();
    codinginterviews::test_ReverseSentence();
    codinginterviews::test_StrToInt();
    codinginterviews::test_match();
    leetcode::test_addBinary();
    leetcode::test_longestPalindrome();
    leetcode::test_convert();
    leetcode::test_myAtoi();
    codinginterviews::test_removeRepeatChar();
    
    char s1[] = "ab";
    char s2[] = ".*";
    bool v = isMatch(s1, s2);
    
    Change so;
    vector<string> vec{"vvz","bbaa","f","bbba","bbaa","baoa","btoa","bbba","dcki","bbbb","ge","atoj","baaa","btoj","ae"};
    int v2 = so.countChanges(vec, 15, "atoj", "bbbb");
    
    Solution2 so2;
    int v23 = so2.getMaxRepetitions("acb", 4, "ab", 2);
    return 0;
}
