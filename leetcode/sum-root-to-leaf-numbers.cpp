/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void dfs(TreeNode *root, int current, int& answer) {
        current = current * 10 + root->val;
        if (root->left == NULL && root->right == NULL) {
            answer += current;
        } else {
            if (root->left != NULL) {
                dfs(root->left, current, answer);
            }
            if (root->right != NULL) {
                dfs(root->right, current, answer);
            }
        }
    }
    
    int sumNumbers(TreeNode *root) {
        int answer = 0;
        if (root != NULL) {
            dfs(root, 0, answer);
        }
        return answer;
    }
};
