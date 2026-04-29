#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 樹的節點 (把它想像成一個個箱子，裡面可以裝數字，還可以綁繩子連到左邊和右邊的箱子)
class TreeNode {
public:
    int value;       // 箱子裡裝的數字
    TreeNode* left;  // 連到左邊的箱子
    TreeNode* right; // 連到右邊的箱子

    // 剛建立新箱子時，先把數字放進去，左右兩邊還沒連東西 (設為空 nullptr)
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// 樹的整體結構 (負責管理所有的箱子)
class BinaryTree {
public:
    TreeNode* root;  // 樹的源頭 (最上面的第一個箱子)
    BinaryTree() : root(nullptr) {} // 一開始樹是空的

    // 把一排數字 (陣列) 按照「從上到下、從左到右」的順序掛到樹上
    TreeNode* buildTree(vector<int>& arr) {
        if (arr.empty()) return nullptr; // 如果沒有數字就不用建了

        queue<TreeNode*> q; // 用來排隊的隊伍，記錄接下來要幫誰接上左右箱子
        root = new TreeNode(arr[0]); // 拿第一個數字當最上面的箱子
        q.push(root); // 讓最上面的箱子排隊

        size_t i = 1; // 從第二個數字開始準備接上去
        while (!q.empty()) {
            TreeNode* current = q.front(); // 叫排在最前面的人出來
            q.pop(); // 出列

            // 如果還有數字，就幫他接上「左邊」的箱子
            if (i < arr.size()) {
                current->left = new TreeNode(arr[i]);
                q.push(current->left); // 左邊的新箱子也去排隊
                i++;
            }

            // 如果還有數字，就幫他接上「右邊」的箱子
            if (i < arr.size()) {
                current->right = new TreeNode(arr[i]);
                q.push(current->right); // 右邊的新箱子也去排隊
                i++;
            }
        }
        return root;
    }

    // ★ 中序遍歷 (Inorder) ★
    // 口訣：先左邊 -> 再自己 -> 後右邊
    void inorderTraversal(TreeNode* node) {
        if (node == nullptr) return; // 如果走到空的地方，就退回去

        inorderTraversal(node->left); // 步驟 1：一直往左邊走到底
        cout << node->value << " ";   // 步驟 2：印出自己的數字
        inorderTraversal(node->right);// 步驟 3：再去右邊走走
    }

    // ★ 後序遍歷 (Postorder) ★
    // 口訣：先左邊 -> 再右邊 -> 最後才自己
    void postorderTraversal(TreeNode* node) {
        if (node == nullptr) return; // 如果走到空的地方，就退回去

        postorderTraversal(node->left);  // 步驟 1：一直往左邊走到底
        postorderTraversal(node->right); // 步驟 2：再去右邊走到底
        cout << node->value << " ";      // 步驟 3：左右兩邊都處理完了，最後才印出自己的數字
    }
};

int main() {
    BinaryTree tree; // 準備一棵樹

    // 我們要掛到樹上的數字陣列
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7 };
    tree.buildTree(arr); // 把陣列變成樹的形狀

    // 測試 1：中序遍歷輸出
    cout << "Inorder Traversal:   ";
    tree.inorderTraversal(tree.root);
    cout << endl; // 換行

    // 測試 2：後序遍歷輸出
    cout << "Postorder Traversal: ";
    tree.postorderTraversal(tree.root);
    cout << endl; // 換行

    return 0;
}
