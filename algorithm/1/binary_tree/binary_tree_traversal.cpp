//递归方法


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    public:
        vector<int> preorderTraversal(TreeNode* root) {

            vector<int> res;
            tree(root, res); //递归方法

            return res; //Happy AC
        }

        //前序遍历
        void tree(TreeNode *root, vector<int> &res)
        {
            if(root == nullptr)
                return;
            res.push_back(root->val);
            tree(root->left, res);
            tree(root->right, res);
        }

        //中序遍历
        void tree(TreeNode *root, vector<int> &res)
        {
            if(root == nullptr)
                return;
            tree(root->left, res);
            res.push_back(root->val);
            tree(root->right, res);
        }

        //后序遍历
        void tree(TreeNode *root, vector<int> &res)
        {
            if(root == nullptr)
                return;
            tree(root->left, res);
            tree(root->right, res);
            res.push_back(root->val);
        }

};
