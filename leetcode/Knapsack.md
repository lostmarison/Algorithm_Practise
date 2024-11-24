```java
public class Knapsack {
    /**
     * 使用动态规划解决0-1背包问题，找出能够放入背包的最大价值。
     *
     * @param weight  一个整数数组，表示每个物品的重量
     * @param value   一个整数数组，与weight数组相对应，表示每个物品的价值
     * @param bagSize 一个整数，表示背包的最大容量
     * @return 一个整数，表示能够放入背包的最大价值
     */
    public int getMaxValue(int[] weight, int[] value, int bagSize) {
        int n = weight.length; // 物品的数量
        // dp[i][j] 表示使用前 i 个物品装入包容量为 j 时能够获得的最大价值
        int[][] dp = new int[n + 1][bagSize + 1];
        for (int i = 1; i <= n; i++) { // 遍历每个物品
            int w = weight[i - 1]; // 当前物品的重量
            int v = value[i - 1];  // 当前物品的价值
            for (int j = 0; j <= bagSize; j++) { // 遍历每个可能的背包容量
                if (w > j) { // 如果当前物品的重量大于当前的背包容量，则不能放入背包
                    dp[i][j] = dp[i - 1][j]; // 最大价值等于不使用当前物品时的最大价值
                } else {
                    // 否则，选择放入或不放入当前物品，取两者中的较大值
                    // dp[i - 1][j] 表示不放入当前物品的最大价值
                    // v + dp[i - 1][j - w] 表示放入当前物品后的最大价值（当前物品价值加上剩余容量时的最大价值）
                    dp[i][j] = Math.max(dp[i - 1][j], v + dp[i - 1][j - w]);
                }
            }
        }
        return dp[n][bagSize]; // 返回使用所有物品，并且背包容量为bagSize时的最大价值
    }

    public static void main(String[] args) {
        Knapsack test = new Knapsack();
        int[] weight = {1, 3, 4}; // 物品重量数组
        int[] value = {15, 20, 36}; // 与weight数组相对应的物品价值数组
        int bagSize = 4; // 背包的最大容量
        System.out.print(test.getMaxValue(weight, value, bagSize)); // 输出能够放入背包的最大价值
    }
}
```
