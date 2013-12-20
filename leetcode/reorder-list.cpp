/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode *head) {
        if (head == NULL) {
            return;
        }
        
        vector<ListNode*> nodes;
        for (ListNode *now = head; now != NULL; now = now->next) {
            nodes.push_back(now);
        }
        int n = nodes.size();
        int middle = (n - 1) >> 1;
        for (int i = 0; i < middle; ++ i) {
            nodes[i]->next = nodes[n - i - 1];
            nodes[n - i - 1]->next = nodes[i + 1];
        }
        if (n % 2 == 0) {
            nodes[middle]->next = nodes[middle + 1];
            nodes[middle + 1]->next = NULL;
        } else {
            nodes[middle]->next = NULL;
        }
        head = nodes[0];
    }
};
