/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    #define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)
    typedef pair<UndirectedGraphNode*, UndirectedGraphNode*> Pair;
    
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *root) {
        if (root == NULL) {
            return NULL;
        }
        set<int> built;
        map<int, UndirectedGraphNode*> old_to_new;
        
        UndirectedGraphNode *new_root = new UndirectedGraphNode(root->label);
        built.insert(root->label);
        old_to_new[root->label] = new_root;
        
        queue<Pair> node_queue;
        node_queue.push(make_pair(new_root, root));
        while (!node_queue.empty()) {
            UndirectedGraphNode *node = node_queue.front().first;
            UndirectedGraphNode *src = node_queue.front().second;
            node_queue.pop();
            foreach(iter, src->neighbors) {
                UndirectedGraphNode *to = *iter;
                if (built.find(to->label) == built.end()) {
                    UndirectedGraphNode *new_node = new UndirectedGraphNode(to->label);
                    built.insert(to->label);
                    old_to_new[to->label] = new_node;
                    node_queue.push(make_pair(new_node, to));
                }
                node->neighbors.push_back(old_to_new[to->label]);
            }
        }
        return new_root;
    }
};
