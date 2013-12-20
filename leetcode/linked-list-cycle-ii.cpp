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
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL) {
            return NULL;
        }
        ListNode *slow = head;
        ListNode *fast = head;
        ListNode *meet;
        while (true) {
            if (fast->next == NULL || fast->next->next == NULL) {
                return NULL;
            }
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast) {
                meet = slow;
                break;
            }
        }
        slow = head;
        fast = meet;
        while (true) {
            if (slow == fast) {
                return fast;
            }
            slow = slow->next;
            fast = fast->next;
        }
    }
};
