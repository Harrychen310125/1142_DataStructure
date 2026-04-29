#include <iostream>//輸入輸出
#include <queue>//queue用來做層序
#include <vector>//vector存資料

using namespace std;

//節點
class TreeNode {
public:
    int value;//存值
    TreeNode* left;//左子
    TreeNode* right;//右子

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}//建構子
};

//二元樹
class BinaryTree {
public:
    TreeNode* root;//建立root

    BinaryTree() : root(nullptr) {}//一開始空樹

    //用陣列建樹（層序）
    TreeNode* buildTree(vector<int>& arr) {
        if (arr.empty()) return nullptr;//沒資料直接回傳

        queue<TreeNode*> q;//queue存節點
        root = new TreeNode(arr[0]);//第一個當root
        q.push(root);//放進queue

        size_t i = 1;//從第二個開始
        while (!q.empty()) {//只要queue還有
            TreeNode* cur = q.front();//拿最前面
            q.pop();//移除

            if (i < arr.size()) {//還有資料就接左
                cur->left = new TreeNode(arr[i]);//建左節點
                q.push(cur->left);//放進queue
                i++;//index往後
            }

            if (i < arr.size()) {//還有資料就接右
                cur->right = new TreeNode(arr[i]);//建立右節點
                q.push(cur->right);//放進queue
                i++;//index往後
            }
        }
        return root;//回傳root
    }

    //中序：左 中 右
    void inorderTraversal(TreeNode* node) {
        if (!node) return;//空就結束

        inorderTraversal(node->left);//先左
        cout << node->value << " ";//印自己
        inorderTraversal(node->right);//再右
    }

    //後序:左右中
    void postorderTraversal(TreeNode* node) {
        if (!node) return;//空就結束

        postorderTraversal(node->left);//先左
        postorderTraversal(node->right);//再右
        cout << node->value << " ";//最後自己
    }
};

int main() {
    BinaryTree tree;//建立tree

    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};//資料
    tree.buildTree(arr);//建樹

    cout << "Inorder Traversal:   ";//提示Inorder
    tree.inorderTraversal(tree.root);//中序
    cout << endl;//換行

    cout << "Postorder Traversal: ";//提示postorder
    tree.postorderTraversal(tree.root);//後序
    cout << endl;//換行

    return 0;//結束
}
