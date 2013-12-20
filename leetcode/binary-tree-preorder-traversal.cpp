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
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> result;
        if (root == NULL) {
            return result;
        }
        
        int node_count = 1;
        queue<TreeNode*> node_queue;
        node_queue.push(root);
        while (!node_queue.empty()) {
            TreeNode *node = node_queue.front();
            node_queue.pop();
            if (node->left != NULL) {
                node_queue.push(node->left);
                node_count ++;
            }
            if (node->right != NULL) {
                node_queue.push(node->right);
                node_count ++;
            }
        }
        
        TreeNode **node_stack = new TreeNode* [node_count];
        int *period = new int [node_count];
        node_stack[0] = root;
        period[0] = 0;
        
        int length = 0;
        while (length >= 0) {
            TreeNode *node = node_stack[length];
            if (period[length] == 0) {
                result.push_back(node->val);
                period[length] = 1;
            }
            if (period[length] == 1) {
                period[length] = 2;
                if (node->left != NULL) {
                    length ++;
                    node_stack[length] = node->left;
                    period[length] = 0;
                    continue;
                }
            }
            if (period[length] == 2) {
                period[length] = 3;
                if (node->right != NULL) {
                    length ++;
                    node_stack[length] = node->right;
                    period[length] = 0;
                    continue;
                }
            }
            length --;
        }
        return result;
    }
};
