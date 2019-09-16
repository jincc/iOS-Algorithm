# 贪心算法

当我们看到这类题目时，首先要联想到贪心：针对一组数据，我们定义了期望值，限制值，希望从中选出几个数据，在满足限制值的条件下，期望值最大.

关键点就在于：每次在选择当前情况下，如果对期望值贡献一样的情况下，我们使用选择那个对期望值贡献最多的那个.


比如0,1背包问题. <font size=5 color=red>限制值</font>就是w kg, <font size=5 color=red>期望值</font>就是背包里所有物品的总价值最大，而<font size=5 color=red>贪心思想</font>每次向背包里放1kg物品时，我们始终选择那个最贵的.


# [分糖果](./greed/shared_the_sweets.h)

# [纸币找零](./greed/coin_dispenser.h)

# [区间覆盖](./greed/region_overlapping.h)


# leetcode
| &emsp;题号&emsp; | 题目链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| 答案链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| &emsp;难度&emsp;  | &emsp;完成度&emsp;  |
| :--: | :--: | :----------------------------------------------------------- | :-----------------------------------------------------------  | :------: |
|  55  | [跳跃游戏](https://leetcode-cn.com/problems/jump-game/) | [jump_game](./greed/leetcode/medium/jump_game.h) | <font color=orange> medium </font>  | ✅ |
|  134  | [加油站](https://leetcode-cn.com/problems/gas-station/) | [gas_station](./greed/leetcode/medium/gas_station.h) | <font color=orange> medium </font>  | ✅ |
|  455  | [分发饼干](https://leetcode-cn.com/problems/assign-cookies/description/) | -- | ✨ | ❌ |
|  860  | [柠檬水找零](https://leetcode-cn.com/problems/lemonade-change/description/) | -- | ✨ | ❌ |
|  874  | [模拟行走机器人](https://leetcode-cn.com/problems/walking-robot-simulation/description/) | -- | ✨ | ❌ |