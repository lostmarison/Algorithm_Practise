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

![image](https://github.com/user-attachments/assets/62c6134a-e837-4d99-b491-3614b7a825d7)
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
            if (j < weight[i]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], value[i] + dp[i - 1][j - weight[i]]);
            }
        }
    }
    return dp[n - 1][bagsize];
}
```
