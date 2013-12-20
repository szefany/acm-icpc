/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:    
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (head == NULL) {
            return NULL;
        }
        RandomListNode *new_head = new RandomListNode(head->label);
        
        set<RandomListNode*> built;
        map<RandomListNode*, RandomListNode*> old_to_new, new_to_old;
        queue<RandomListNode*> node_queue;
        node_queue.push(new_head);
        built.insert(head);
        old_to_new[head] = new_head;
        new_to_old[new_head] = head;
        
        while (!node_queue.empty()) {
            RandomListNode *node = node_queue.front();
            RandomListNode *src_node = new_to_old[node];
            node_queue.pop();
            if (src_node->next != NULL) {
                if (built.find(src_node->next) == built.end()) {
                    RandomListNode *new_node = new RandomListNode(src_node->next->label);
                    new_to_old[new_node] = src_node->next;
                    old_to_new[src_node->next] = new_node;
                    built.insert(src_node->next);
                    node_queue.push(new_node);
                }
                node->next = old_to_new[src_node->next];
            }
            if (src_node->random != NULL) {
                if (built.find(src_node->random) == built.end()) {
                    RandomListNode *new_node = new RandomListNode(src_node->random->label);
                    new_to_old[new_node] = src_node->random;
                    old_to_new[src_node->random] = new_node;
                    built.insert(src_node->random);
                    node_queue.push(new_node);
                }
                node->random = old_to_new[src_node->random];
            }
        }
        return new_head;
    }
};
