//
//  hanoiProblem.h
//  stack+queue
//
//  Created by junl on 2019/10/17.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef hanoiProblem_hpp
#define hanoiProblem_hpp

#include <stdio.h>
#include <string>
/*
 用栈来求解汉诺塔问题
 
 汉诺塔的问题比较金典，这里修改一下游戏规则：现在z限制不能直接从最左侧的塔直接移动到最右侧，或者最右侧的塔直接移动到最左侧，
 而是必须经过中间。求当塔有N层的时候，打印最优移动过程和最优移动步数。
 */

class hanoiProblem {
public:
    int solve(int n){
        if (n < 1) {
            return 0;
        }
        std::string left = "left";
        std::string center = "center";
        std::string right = "right";
        return  solve(n, left, center,right,left,right);
    }
private:
    
    /**
     @param n <#n description#>
     @param left 左柱子的标示
     @param center 中间柱子的标示
     @param right 右柱子的标示
     @param from 将from这个柱子上的n-1个塔移动到to柱子上去
     @param to 将from这个柱子上的n-1个塔移动到to柱子上去
     */
    int solve(int n, std::string &left, std::string &center, std::string &right, std::string &from, std::string &to){
        if (n == 1) {
            //说明现在只剩下最上层的塔需要移动
            if (from == center || to == center) {
                printf("move 1 from %s to %s\n",from.c_str(),to.c_str());
                return 1;
            }else{
                printf("move 1 from %s to center\n",from.c_str());
                printf("move 1 from center to %s\n",to.c_str());
                return 2;
            }
        }
        
        //多层塔的情况
        if (from == center || to == center) {
            //就是说这种情况，我们想要把左边或者右边柱子上的塔移动到中间柱子上去.
            //或者说，我们想要把中间柱子上的塔移动到左边或者右边上.
            std::string other = from == left ? right:left;
            int part1 = solve(n-1, left, center, right, from, other);
            int part2 = 1;
            printf("move %i from %s to %s\n", n, from.c_str(), to.c_str());
            int part3 = solve(n, left, center, right, other, to);
            return part1 + part2 + part3;
        }else{
            //就是说我们向要把最左边的柱子移动到最右边去，或者是最右边的柱子移动到最左边去.
            int part1 = solve(n-1, left, center, right, from, to);
            printf("move %i from %s to center\n",n, from.c_str());
            int part2 = 1;
            int part3 = solve(n-1, left, center, right, to, from);
            
            int part4 = 1;
            printf("move %i from center to %s\n", n, to.c_str());
            int part5 = solve(n-1, left, center, right, from, to);
            
            return part1 + part2 + part3 + part4 + part5;
        }
    }
};

class hanoiProblem_stk {
public:
    enum Action{
        NONE = 0,
        LToM = 1,
        MToL,
        MToR,
        RToM
    };
    Action record[1];
    int solve(int n){
        //  小压大原则
        //  相邻不可逆
        
        std::stack<int> ls;
        std::stack<int> ms;
        std::stack<int> rs;
        ls.push(INT_MAX);ms.push(INT_MAX);rs.push(INT_MAX);
        for (int i=n; i>0; i--) {
            ls.push(i);
        }
        int count = 0;
        std::string left = "left";
        std::string center = "center";
        std::string right = "right";
        while (rs.size() != n+1) {
            count += step(LToM, MToL, ls, ms, left, center);
            count += step(MToL, LToM, ms, ls, center, left);
            count += step(MToR, RToM, ms, rs, center, right);
            count += step(RToM, MToR, rs, ms, right, center);
        }
        return count;
    }
    int step(Action ctOp, Action notOp,std::stack<int> &from,std::stack<int> &to,std::string& fromsysmobl, std::string &tosysmobl){
        if (record[0] != notOp && from.top() < to.top()) {
            to.push(from.top());
            from.pop();
            printf("move %i from %s to %s\n",to.top(),fromsysmobl.c_str(),tosysmobl.c_str());
            record[0] = ctOp;
            return 1;
        }
        return 0;
    }
};



void test_hanoiProblem(){
    std::cout << "---------test_hanoiProblem----------" << std::endl;
    class hanoiProblem so;
    std::cout << so.solve(3) << std::endl;
    
    class hanoiProblem_stk so2;
    std::cout << so2.solve(3) << std::endl;
    
}
#endif /* hanoiProblem_hpp */
