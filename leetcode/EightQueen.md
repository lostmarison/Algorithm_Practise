```c++
class Solution {
private:
    vector<vector<string>> results;
    vector<string> board;

    // 检查在(row, col)位置放置皇后是否安全
    bool isValid(int row, int col, int n) {
        // 一行一行放置，保证每一行只有一个皇后
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q')
                return false; // 检查列
            // 检查两个对角线
            if (col - (row - i) >= 0 && board[i][col - (row - i)] == 'Q')
                return false;
            if (col + (row - i) < n && board[i][col + (row - i)] == 'Q')
                return false;
        }
        return true;
    }

    // 递归函数来放置皇后
    void backtracking(int row, int n) {
        if (row == n) {
            // 所有皇后都已成功放置，将当前棋盘状态添加到结果中
            results.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (isValid(row, col, n)) {
                board[row][col] = 'Q';    // 放置皇后
                backtracking(row + 1, n); // 递归放置下一个皇后
                board[row][col] = '.';    // 回溯，移除皇后
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        // 初始化棋盘，所有位置都是'.'
        board.resize(n, string(n, '.'));
        backtracking(0, n); // 从第一行开始放置皇后
        return results;
    }
};
```
