```c++
定义：
设 dp[i][j] 为在背包容量为 j 时任取下标为 [0 ~ i] 的物品所得的最大价值。

递推关系：
1.一行一行填，在第 i 行时只考虑放不放入下标为 i 的物品：
2.如果不放下标为 i 的物品，剩余下标为 [0 ~ i-1] 的物品可选，背包容量剩余 j，则最大价值为 dp[i-1][j]； 
3.如果可以放入且放入下标为 i 的物品，剩余下标为 [0 ~ i-1] 的物品可选，背包容量剩余 j-weight[i]，则最大价值为 value[i] + dp[i-1][j-weight[i]]； 

*约束条件：
如果背包容量比当前要选择放的物品(下标为i)的重量小，那么就不放入物品 i ，此时最大价值为 dp[i-1][j]；
如果背包容量比当前要选择放的物品的重量大，那么可以选择放入或者不放入，为了使价值最大，需要比较两种情况，此时最大价值为：
max(dp[i-1][j],dp[i-1][j-weight[i]])

初始化：
1. dp[i][0] 表示背包容量为 0 时 任意放入下标为 [0 ~ i-1] 的物品的最大价值，易知
dp[i][0] = 0。
3. 初始化第 0 行时，当 j >= weight[0] 时的最大价值都为 value[0]，即 dp[0][j] =
value[0]。

价值最大：
返回dp[最后一个物品下标][背包容量]
```

![knapsack1](https://github.com/user-attachments/assets/47302c9f-0154-4b60-988e-ba7ad7411785)
### 初始化
```c++
int n = weight.size(); // 物品个数
    // 初始化
    vector<vector<int>> dp(n, vector<int>(bagsize + 1, 0));
    for (int j = weight[0]; j <= bagsize; ++j) {
        dp[0][j] = value[0];
    }
```

```c++
vector<int> weight = {1, 3, 4}; // 物品重量
vector<int> value = {15, 20, 36}; // 物品价值
int bagsize = 4; // 背包容量

int getMaxValue(vector<int>& weight, vector<int>& value, int bagsize) {
    int n = weight.size(); // 物品个数
    // 初始化
    vector<vector<int>> dp(n, vector<int>(bagsize + 1, 0));
    for (int j = weight[0]; j <= bagsize; ++j) {
        dp[0][j] = value[0];
    }
    // 递推
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= bagsize; ++j) {
            if (j < weight[i]) { // 如果背包容量比当前物品重量小
                dp[i][j] = dp[i - 1][j]; // 选不了当前物品，即在背包容量为 j 时，只能在下标为 [0 ~ i-1] 的物品中选物品
            } else { 
                dp[i][j] = max(dp[i - 1][j], value[i] + dp[i - 1][j - weight[i]]);
            }
        }
    }
    return dp[n - 1][bagsize];
}
```
### 优化
![knapsack2](https://github.com/user-attachments/assets/1fbacf8b-a2fd-4a8e-81de-d94d3be97ff3)
```c++
int getMaxValue2(vector<int>& weight, vector<int>& value, int bagsize) {
    int n = weight.size();  // 物品数量
    vector<int> dp(bagsize + 1, 0);
    for (int i = 0; i < n; ++i) {  // 外循环正序遍历物品
        // 内循环倒序遍历
        for (int j = bagsize; j >= weight[i]; --j) {
            dp[j] = max(dp[j], value[i] + dp[j - weight[i]]);
        }
    }
    return dp[bagsize];
}
```

```
问题与解答：
1.为什么内循环采用了逆序遍历？
如果内循环采用正序遍历（与二维dp一样），则当我们先用物品 0 遍历时，会依次填入0 15 30 45 60。这是错误的。由于没有使用二维数组，使得我们每次填最大价值时都基于了前面一列的最大价值：
例如，在判断dp[2]时，dp[1]已经选择了物品 0，但背包还剩余 1 容量，使得在与dp[1]比较时，又一次装入了物品 0，以此类推。

2.为什么二维dp不会出现重复取物品呢？
因为对于二维dp，dp[i][j]是通过上一层dp[i-1][j]计算而来的，使得本层的dp[i][j]不会被覆盖。

3.为什么逆序遍历时不会重复取物品呢？
以所给例子具体为例：
我们初始化了一维数组为全 0 数组，因此在用物品 0 逆序遍历时，我们始终将 dp[value[i]+j-weight[i]] 与 0 比较，保证每次最多装入一个物品。
而在我们用物品 1 遍历时，我们判断出此时能装入物品 1，因此我们比较了 value[1]+dp[3](=35) 与 dp[4](=15)。而这个dp[3]即是由上层“继承”下来的。
```
