// Game, BUPT Newbie 2013
#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>

const int N = 1000 + 5;

struct Node {
    Node () {}
    Node (int x, int y, int value): x (x), y (y), value (value) {}
    int x, y, value;
    bool operator < (const Node &other) const {
        return x < other.x || x == other.x && y < other.y;
    }
} total[N * N];

int n;

bool check (Node node, Node prev, Node next) {
    return node.x >= prev.x && node.x <= next.x && node.y >= prev.y && node.y <= next.y;
}

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        // initialise ();
        scanf ("%d", &n);
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= n; ++ j) {
                int value;
                scanf ("%d", &value);
                total[value] = Node (i, j, value);
            }
        }
        std::set <Node> set;
        std::vector <Node> nodes;
        set.insert (Node (0, 0, 0));
        set.insert (Node (n + 1, n + 1, 0));
        for (int i = n * n; i >= 1; -- i) {
            std::set <Node>::iterator iter = set.lower_bound (total[i]);
            Node next = *iter;
            Node prev = *(-- iter);
            if (check (total[i], prev, next)) {
                nodes.push_back (total[i]);
                set.insert (total[i]);
            }
        }
        std::sort (nodes.begin(), nodes.end());
        for (int i = 0; i < nodes.size(); ++ i) {
            printf ("%d%c", nodes[i].value, i + 1 == nodes.size() ? '\n' : ' ');
        }
    }
    return 0;
}
