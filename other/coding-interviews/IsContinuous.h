//
//  IsContinuous.h
//  other
//
//  Created by junl on 2019/8/5.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef IsContinuous_hpp
#define IsContinuous_hpp

#include <stdio.h>
#include <vector>
/*
 剑指Offer（四十五）：扑克牌顺子
 LL今天心情特别好,因为他去买了一副扑克牌,发现里面居然有2个大王,2个小王(一副牌原本是54张^_^)...他随机从中抽出了5张牌,想测测自己的手气,看看能不能抽到顺子,如果抽到的话,他决定去买体育彩票,嘿嘿！！“红心A,黑桃3,小王,大王,方片5”,“Oh My God!”不是顺子.....LL不高兴了,他想了想,决定大\小 王可以看成任何数字,并且A看作1,J为11,Q为12,K为13。上面的5张牌就可以变成“1,2,3,4,5”(大小王分别看作2和4),“So Lucky!”。LL决定去买体育彩票啦。 现在,要求你使用这幅牌模拟上面的过程,然后告诉我们LL的运气如何， 如果牌能组成顺子就输出true，否则就输出false。为了方便起见,你可以认为大小王是0。

 https://www.nowcoder.com/practice/762836f4d43d43ca9deb273b3de8e1f4?tpId=13&tqId=11198&tPage=3&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    bool IsContinuous( std::vector<int> numbers ) {
        std::sort(numbers.begin(), numbers.end());
        int zerocount = 0;
        int lastnumber= -1;
        for (int i=0; i<numbers.size(); i++) {
            if (numbers[i] == 0) {
                zerocount++;
                continue;
            }
            
            if (lastnumber != -1 && numbers[i]-lastnumber != 1) {
                if (numbers[i] == lastnumber) {
                    return false;
                }
                int count = numbers[i]-lastnumber-1;
                zerocount-=count;
                if (zerocount < 0 ) {
                    return false;
                }
            }
            lastnumber = numbers[i];
        }
        return true;
    }
    
    void test_IsContinuous(){
        std::vector<int> a{1,0,0,1,0};
        std::cout << "test_IsContinuous starting......." <<std::endl;
        std::cout <<IsContinuous(a) << std::endl;
    }
}
#endif /* IsContinuous_hpp */
