// Ghost, BUPT Newbie 2013
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cassert>

const int N = 100000 + 5;

struct Node {
    int a, b;
    void input () {
        scanf ("%d%d", &a, &b);
    }
    bool operator < (const Node &other) const {
        return (long long)b * other.a < (long long)a * other.b;
    }
} elements[N];

int rank[N], query[N];
double answer[N];
int n, m;

bool cmp_1 (int x, int y) {
    return query[x] < query[y];
}

bool cmp_2 (Node p, Node q) {
    return p.a < q.a;
}

std::priority_queue <Node> queue;

int main () {
    while (scanf ("%d%d", &n, &m) != EOF) {
#define clr(x) memset ((x), 0, sizeof (x))
        clr (elements), clr (rank), clr (query), clr (answer);
        for (int i = 0; i < n; ++ i) {
            elements[i].input ();
        }
        for (int i = 0; i < m; ++ i) {
            scanf ("%d", &query[i]);
            rank[i] = i;
        }
        std::sort (rank, rank + m, cmp_1);
        std::sort (elements, elements + n, cmp_2);
        while (!queue.empty()) {
            queue.pop();
        }
        for (int i = 0, j = 0; i < m; ++ i) {
            int u = rank[i], x = query[u];
            while (j < n && elements[j].a <= x) {
                queue.push (elements[j]);
                j ++;
            }
            if (queue.empty()) {
                answer[u] = 0;
            } else {
                int a = queue.top().a, b = queue.top().b;
                answer[u] = (double)x * b / a;
            }
        }
        for (int i = 0; i < m; ++ i) {
            printf ("%.3f\n", answer[i]);
        }
    }
    return 0;
}
