class Solution {
public:
    ListNode *insertionSortList(ListNode *head) {
        for (ListNode *now = head, *prev_now = NULL; now != NULL; prev_now = now, now = now->next) {
            ListNode *target = now;
            ListNode *prev_target = prev_now;
            for (ListNode *node = now->next, *prev = now; node != NULL; prev = node, node = node->next) {
                if (node->val < target->val) {
                    target = node;
                    prev_target = prev;
                }
            }
            if (target != now) {
                // swap(now, target)
                if (prev_now != NULL) {
                    prev_now->next = target;
                } else {
                    head = target;
                }
                prev_target->next = now;
                ListNode *temp = now->next;
                now->next = target->next;
                target->next = temp;
                now = target;
            }
        }
        return head;
    }
};
