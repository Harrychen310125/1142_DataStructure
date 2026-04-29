#include <iostream>//輸入輸出
#include <queue>//queue做層序
#include <vector>//vector存資料

using namespace std;

//節點
class TreeNode {
public:
    int value;//存數字
    TreeNode* left;//左子
    TreeNode* right;//右子
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}//建構子
};

//二元樹
class BinaryTree {
public:
    TreeNode* root;//根節點
    BinaryTree() : root(nullptr) {}//一開始是空的

    //用陣列建樹(層序)
    TreeNode* buildTree(vector<int>& arr) {
        if (arr.empty()) return nullptr;//沒資料直接回傳
        
        queue<TreeNode*> q;//queue存節點
        root = new TreeNode(arr[0]);//第一個當root
        q.push(root);//放進queue

        size_t i = 1;//從第二個開始
        while (!q.empty()) {//queue還有就繼續
            TreeNode* current = q.front();//拿最前面
            q.pop();//移掉
            
            if (i < arr.size()) {//還有就接左
                current->left = new TreeNode(arr[i]);//建左
                q.push(current->left);//放進queue
                i++;//往下一個
            }
            if (i < arr.size()) {//還有就接右
                current->right = new TreeNode(arr[i]);//建右
                q.push(current->right);//放進queue
                i++;//往下一個
            }
        }
        return root;//回傳root
    }

    //中序:左中右
    void inorderTraversal(TreeNode* node) {
        if (node == nullptr) return;//空就停 
        inorderTraversal(node->left);//先左 
        cout << node->value << " ";//印自己 
        inorderTraversal(node->right);//再右 
    }

    //找最大值(遞迴)
    int findMax(TreeNode* node) {
        if (node == nullptr) {//如果是空
            return 0;//回傳0(假設都是正數)
        }

        int currentMax = node->value;//先當作最大
        
        int leftMax = findMax(node->left);//去左邊找
        
        int rightMax = findMax(node->right);//去右邊找
        
        if (leftMax > currentMax) {//比左邊
            currentMax = leftMax;//更新
        }
        if (rightMax > currentMax) {//比右邊
            currentMax = rightMax;//更新
        }
        
        return currentMax;//回傳最大
    }
};

int main() {
    BinaryTree tree;//建立樹 
    
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7 };//資料
    tree.buildTree(arr);//建樹 
    
    cout << "Inorder Traversal: ";//提示
    tree.inorderTraversal(tree.root);//中序
    cout << endl;//換行

    if (tree.root != nullptr) {//確保有資料
        int leftSubtreeMax = tree.findMax(tree.root->left);//左子樹最大
        
        int rightSubtreeMax = tree.findMax(tree.root->right);//右子樹最大
        
        cout << "Max left subtree value: " << leftSubtreeMax << endl;//印左
        
        cout << "Max right subtree value: " << rightSubtreeMax << endl;//印右
    }

    return 0;
}
