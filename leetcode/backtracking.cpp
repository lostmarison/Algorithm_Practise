#include <iostream>  
#include <vector>  

using namespace std;

vector<vector<int>> result;
vector<int> path;

/*
void backtracking(����) {
    if (��ֹ����) {
        ��Ž��;
        return;
    }

    for (ѡ�񣺱��㼯����Ԫ�أ����нڵ㺢�ӵ��������Ǽ��ϵĴ�С��) {
        ����ڵ�;
        backtracking(·����ѡ���б�); // �ݹ�
        ���ݣ�����������
    }
}
*/

void backtracking(vector<int>& nums, int startIndex) {
    // ����ǰ·����ӵ�����У�ע���������ڵݹ�ġ��ײ������  
    result.push_back(path);
    if (startIndex >= nums.size()) {
        // ����Ѿ�����������Ԫ�أ�ֱ�ӷ���  
        return;
    }
    for (int i = startIndex; i < nums.size(); ++i) {
        // ��ѡ��  
        path.push_back(nums[i]);
        // ������һ�������  
        backtracking(nums, i + 1);
        // ����ѡ��  
        path.pop_back();
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    result.clear();
    path.clear();
    // ������0��ʼ�����Ӽ�  
    backtracking(nums, 0);
    return result;
}

int main() {
    vector<int> nums = { 1, 2, 3 };
    vector<vector<int>> subsetsResult = subsets(nums);

    // ��ӡ�����Ӽ�  
    for (const auto& subset : subsetsResult) {
        cout << "{";
        for (int num : subset) {
            cout << num << (num == subset.back() ? "" : ",");
        }
        cout << "}" << endl;
    }

    return 0;
}