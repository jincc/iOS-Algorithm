//
//  validateStackSequences.h
//  stack+queue
//
//  Created by junl on 2020/5/15.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef validateStackSequences_h
#define validateStackSequences_h
#include <stack>
namespace codinginterviews{
class ValidateStackSequences {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        if (pushed.empty() && popped.empty()) return true;

        std::stack<int> stk;
        int i, j;
        i = 0; j = 0;
        while(j < popped.size()){
            if (stk.empty() || stk.top() != popped[j]){
                if (i == pushed.size())
                    return false;
                stk.push(pushed[i++]);
            }else{
                stk.pop();
                j++;
            }
        }
        return stk.empty();
    }
};
}
void test_validateStackSequences(){
    vector<int> pushed{1,2,3,4,5};
    vector<int> poped{4,5,3,2,1};
    codinginterviews::ValidateStackSequences so;
    std::cout << "validateStackSequences: " << so.validateStackSequences(pushed, poped) << std::endl;
}

#endif /* validateStackSequences_h */
