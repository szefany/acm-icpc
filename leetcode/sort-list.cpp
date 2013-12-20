class Solution {
public:
    ListNode *sortList(ListNode *head) {
        if (head == NULL || head->next == NULL) {
            return head;
        }
        ListNode *tail = head;
        int length = 1;
        while (tail->next != NULL) {
            length ++;
            tail = tail->next;
        }
        int position = rand() % length;
        ListNode *split = head;
        while (position --) {
            split = split->next;
        }
        int value = split->val;

        ListNode *last = NULL;
        for (ListNode *now = head; now != split; ) {
            if (now->val > value) {
                ListNode *next = now->next;
                now->next = NULL;
                tail->next = now;
                tail = now;
                if (now == head) {
                    head = next;
                }
                now = next;
                if (last != NULL) {
                    last->next = now;
                }
            } else {
                last = now;
                now = now->next;
            }
        }
        ListNode *split_front = last;

        for (ListNode *now = split->next, *last = split; now != NULL; ) {
            if (now->val < value) {
                last->next = now->next;
                now->next = head;
                head = now;
                now = last->next;
                if (split_front == NULL) {
                    split_front = head;
                }
            } else {
                last = now;
                now = now->next;
            }
        }

        if (split_front != NULL) {
            split_front->next = NULL;
            head = sortList(head);
            ListNode *last = head;
            for (last = head; last->next != NULL; last = last->next);
            last->next = split;
        }
        if (split != NULL) {
            ListNode *next = sortList(split->next);
            split->next = next;
        }
        return head;
    }
};
