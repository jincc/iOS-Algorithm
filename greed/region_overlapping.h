//
//  region_overlapping.h
//  greed
//
//  Created by junl on 2019/9/10.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef region_overlapping_hpp
#define region_overlapping_hpp

#include <stdio.h>
#include <vector>
/*
 假设我们有N个区间，区间的起始断点和结束断点分别是[l1,r1],[l2,r2],......[ln,rn].
 我们从这N个区间选出一部分区间，这部分区间两两不能相交，（端点相交不算相交），最多能选出多少个区间？
 */

int region_overlapping(vector<vector<int>> areas){
    /*
     我们把所有区域里面，最左边的点记为lmin,最右边的点记为rmax.整个大区间就为[lmin,rmax].
     题目可以转换为：
     在[lmin,rmax]中寻找一部分区间，要求它们两两不能相交，最多能选出多少个空间？
     
     限制值: 在大区间[lmin,rmax]里
     期望值：满足要求的区域数量
     贪心思想: 在贡献相同期望值（符合要求的区间数）时，我们选择范围更小的子区间，这样意味着后面可以由更多的符合要求的子区间.
     */
    int count=0;
    sort(areas.begin(), areas.end(), [](vector<int> &l,vector<int>&r){
        return l[0] < r[0];
    });
    int lmin=areas[0][0];
    for (int i=0; i<areas.size();i++) {
        //左边节点跟前面覆盖的区域不重合
        if (areas[i][0] < lmin) {
            continue;
        }
        //右边希望竟可能的小，这样可以使覆盖的区间竟可能大.
        if (i+1 == areas.size() || areas[i][1] <= areas[i+1][1]) {
            count++;
            lmin = areas[i][1];
            printf("[%i,%i], ",areas[i][0],areas[i][1]);
        }
    }
    return count;
}

#endif /* region_overlapping_hpp */
