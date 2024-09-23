#include <iostream>  
#include <vector>  

using namespace std;

vector<vector<int>> result;
vector<int> path;

/*
void backtracking(参数) {
    if (终止条件) {
        存放结果;
        return;
    }

    for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）) {
        处理节点;
        backtracking(路径，选择列表); // 递归
        回溯，撤销处理结果
    }
}
*/

void backtracking(vector<int>& nums, int startIndex) {
    // 将当前路径添加到结果中，注意这里是在递归的“底部”添加  
    result.push_back(path);
    if (startIndex >= nums.size()) {
        // 如果已经遍历完所有元素，直接返回  
        return;
    }
    for (int i = startIndex; i < nums.size(); ++i) {
        // 做选择  
        path.push_back(nums[i]);
        // 进入下一层决策树  
        backtracking(nums, i + 1);
        // 撤销选择  
        path.pop_back();
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    result.clear();
    path.clear();
    // 从索引0开始构建子集  
    backtracking(nums, 0);
    return result;
}

int main() {
    vector<int> nums = { 1, 2, 3 };
    vector<vector<int>> subsetsResult = subsets(nums);

    // 打印所有子集  
    for (const auto& subset : subsetsResult) {
        cout << "{";
        for (int num : subset) {
            cout << num << (num == subset.back() ? "" : ",");
        }
        cout << "}" << endl;
    }

    return 0;
}