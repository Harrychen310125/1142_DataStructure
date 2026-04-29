#include <iostream>
#include <queue>
#include <vector>
#include <algorithm> // 為了使用 std::max
#include <climits>   // 為了使用 INT_MIN

using namespace std;

// 樹的節點
class TreeNode {
public:
    int value; // 節點的值
    TreeNode* left; // 左子節點
    TreeNode* right; // 右子節點
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {} // 初始化節點
};

// 樹結構
class BinaryTree {
public:
    TreeNode* root;
    BinaryTree() : root(nullptr) {} // 初始化樹

    // 用陣列構建二元樹
    TreeNode* buildTree(vector<int>& arr) {
        if (arr.empty()) return nullptr;

        queue<TreeNode*> q; // 儲存待處理的節點
        root = new TreeNode(arr[0]); // 建立根節點 (陣列第一個元素)
        q.push(root); // 將根節點加入 queue

        size_t i = 1; // 陣列索引
        while (!q.empty()) {
            TreeNode* current = q.front(); // 取出隊列中的節點
            q.pop();

            // 添加左子節點
            if (i < arr.size()) {
                current->left = new TreeNode(arr[i]);
                q.push(current->left); // 將左子節點加入queue
                i++;
            }

            // 添加右子節點
            if (i < arr.size()) {
                current->right = new TreeNode(arr[i]);
                q.push(current->right); // 將右子節點加入queue
                i++;
            }
        }
        return root;
    }

    // 中序遍歷
    void inorderTraversal(TreeNode* node) {
        if (node == nullptr) return; // 如果節點為空,忽略
        inorderTraversal(node->left); // 遍歷左子樹
        cout << node->value << " "; // 訪問當前節點
        inorderTraversal(node->right); // 遍歷右子樹
    }

    // 尋找子樹中的最大值 (新增的函式)
    int findMax(TreeNode* node) {
        if (node == nullptr) {
            return INT_MIN; // 如果節點為空，回傳最小整數值作為防呆
        }
        // 遞迴尋找左、右子樹的最大值，並與當前節點的值做比較
        int maxVal = node->value;
        int leftMax = findMax(node->left);
        int rightMax = findMax(node->right);

        return max(maxVal, max(leftMax, rightMax));
    }
};

int main() {
    BinaryTree tree; // 宣告二元樹

    // 輸入陣列用於構建樹
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7 };
    tree.buildTree(arr); // 建立樹

    // 中序遍歷輸出
    cout << "Inorder Traversal: ";
    tree.inorderTraversal(tree.root);
    cout << endl;

    // 確認根節點存在後，分別計算左子樹與右子樹的最大值
    if (tree.root != nullptr) {
        int leftSubtreeMax = tree.findMax(tree.root->left);
        int rightSubtreeMax = tree.findMax(tree.root->right);

        // 依照題目要求格式輸出
        cout << "Max left subtree value: " << leftSubtreeMax << endl;
        cout << "Max right subtree value: " << rightSubtreeMax << endl;
    }

    return 0;
}
