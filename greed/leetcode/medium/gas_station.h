//
//  gas_station.h
//  greed
//
//  Created by junl on 2019/9/11.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef gas_station_hpp
#define gas_station_hpp

#include <stdio.h>
#include <vector>
#include <numeric>
/*
 134.加油站
 在一条环路上有 N 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
 
 你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。
 
 如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1。
 
 说明:
 
 如果题目有解，该答案即为唯一答案。
 输入数组均为非空数组，且长度相同。
 输入数组中的元素均为非负数。
 示例 1:
 
 输入:
 gas  = [1,2,3,4,5]
 cost = [3,4,5,1,2]
 
 输出: 3
 
 解释:
 从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
 开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
 开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
 开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
 开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
 开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
 因此，3 可为起始索引。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/gas-station
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    using namespace std;
    /*
     思路：
     当前的油量减去开往下一站要消耗的油量之差，即ctgas + gas[i] - cost[i],
     如果差大于零，那么可以开往下一站。
     如果差小于零，那么我们想方法增加ctgas的值，即考虑从前面一个站出发，直到有足够的油可以开往下一站.
     */
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int ctgas=0;
        int start=gas.size();
        int ctlocation=0;
        while (start != ctlocation) {
            if (ctgas + gas[ctlocation] - cost[ctlocation] >= 0) {
                ctgas += gas[ctlocation] - cost[ctlocation];
                ctlocation++;
            }else{
                start--;
                ctgas+=gas[start]-cost[start];
            }
        }
        return ctgas>=0 ? start%gas.size() : -1;
    }
    
    /*
     1.如果总的油量小于总距离那么一定不能开往目的地.反之，一定可以开到目的地.
     2.我们从0个站点出发，如果到了第i个站点，发现油不够了，那么证明这一段路的总油量小于总距离，
     而这一段路之间，从任何站点出发，到i站点剩余油量都会小于0.
     3.那么后面的路程，一定是总距离小于总油量，即答案在后半截路段.我们从第i个站点重新出发，一直重复这个流程。
     */
    int canCompleteCircuit2(vector<int>& gas, vector<int>& cost){
        if (accumulate(gas.begin(), gas.end(), 0) < accumulate(cost.begin(), cost.end(), 0)) {
            return -1;
        }
        
        int start=0;
        int ctgas=0;
        for (int i=0; i<gas.size(); i++) {
            ctgas += gas[i] - cost[i];
            if (ctgas < 0) {
                //如果从start位置出发，到i个站点，油不够的话，那么证明这一段路的总油量小于总距离.
                start=i+1;
                ctgas=0;
            }
        }
        return start;
    }
}
#endif /* gas_station_hpp */
