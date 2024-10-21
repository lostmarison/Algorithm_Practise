```c++
// 前序遍历
class Solution {
public:
    void preorder(TreeNode* root, vector<int>& result) {
        if (!root) {
            return;
        }
        result.push_back(root->val); // 根
        preorder(root->left, result); //左子树
        preorder(root->right, result); //右子树
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        preorder(root, result);
        return result;
    }
};

// 中序遍历
class Solution {
public:
    void inorder(TreeNode* root, vector<int>& result) {
        if (!root) {
            return;
        }
        inorder(root->left, result); // 左子树
        result.push_back(root->val); // 根
        inorder(root->right, result); // 右子树
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorder(root, result);
        return result;
    }
};

// 后序遍历
class Solution {
public:
    void postorder(TreeNode* root, vector<int>& result) {
        if (!root) {
            return;
        }
        postorder(root->left, result); // 左子树
        postorder(root->right, result); // 右子树
        result.push_back(root->val); // 根
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        postorder(root, result);
        return result;
    }
};

// 层序遍历
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) { // 如果根结点为空
            return result;
        }
        queue<TreeNode*> q; // 定义队列
        q.push(root); // 根结点入队

        while (!q.empty()) {
            vector<int> temp;
            int levelSize = q.size(); // 当前层的结点数
            for (int i = 1; i <= levelSize; ++i) {
                TreeNode* node = q.front(); // 记录队头元素
                q.pop();              // 队头元素出队
                temp.push_back(node->val); // 将当前结点值加入当前层的临时存储

                // 将当前结点的左右孩子（如果存在）加入队列
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            result.push_back(temp); // 将当前层的节点值列表加入结果
        }
        return result;
    }
};
```
