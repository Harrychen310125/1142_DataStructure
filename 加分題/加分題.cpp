class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {

        
        //如果兩個節點都沒有資料代表目前這個位置是一樣的
        if (p == nullptr && q == nullptr) {
            return true;
        }

        
        //如果只有其中一邊是空的代表樹的結構不一樣
        if (p == nullptr || q == nullptr) {
            return false;
        }

        
        //如果兩個節點的值不同代表不是同一棵樹
        if (p->val != q->val) {
            return false;
        }

        //繼續比較左子樹和右子樹
        //左右兩邊都相同才會回傳 true
        return isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }
};
