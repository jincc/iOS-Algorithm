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
#include <string>
#include <stack>
using namespace std;
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
class Solution {
public:
    static bool Compare(const vector<int> &l, const vector<int> &r){
        return l[0] > r[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        vector<vector<int>> res;
        if (people.empty() || people[0].size() != 2){
            return res;
        }
        sort(people.begin(), people.end(), Compare);

        for (int i = 1; i < people.size(); i++){
            for(int j=0;j<i;j++){
                if (people[i][0] == people[j][0]){
                    if (people[i][1] < people[j][1]){
                        int cnt = people[i][1];
                        vector<int> r = people[i];
                        people.erase(people.begin() + i);
                        people.insert(people.begin() + cnt, r);
                        break;
                    }
                }else{
                    int cnt = people[i][1];
                    vector<int> r = people[i];
                    people.erase(people.begin() + i);
                    people.insert(people.begin() + cnt, r);
                    break;
                }
            }
        }
        return people;
    }
};
class Solution2 {
public:
    bool canPartition(vector<int>& nums) {
      int sum = 0;
      for (auto &i : nums){
          sum+=i;
      }
      if (sum & 0x1){
          return false;
      }
      int v = sum / 2;
      int idx = -1;
      helper2(nums, idx, v);
      return st;
    }
    void helper2(vector<int &> &nums,int idx, int sum){
        if (sum == 0){
            st = true;
            return;
        }
    
        for(int i=idx+1; i < nums.size();i++){
            if(sum > nums[i]){
                helper2(nums, i, sum - nums[i]);
                helper2(nums, i, sum);
            }
        }
    }
    bool st;
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::string s{"aabccccaab"};
    std::cout << FilterRepeatString(s) << std::endl;
    Solution so;
//    string s2 = "3[a2[c]]";//"3[a2[c]]"
//    s2 = so.decodeString(s2);
    vector<vector<int>> r;
    r.insert(r.begin()+2, {1});
//    r.push_back({7,0});
//    r.push_back({4,4});
//    r.push_back({7,1});
//    r.push_back({5,0});
//    r.push_back({6,1});
//    r.push_back({5,2});
//    so.reconstructQueue(r);
    return 0;
}
