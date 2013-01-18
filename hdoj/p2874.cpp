// HDOJ 2874, Connections between cities
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 10005;
const int M = 20005;
const int Q = 1000005;

struct Graph {
    Graph () {}
    Graph (int v, int w, int n): to(v), weight(w), next(n) {}
    int to, weight, next;
} g[M];
int first[N], edgeCount;

typedef pair<int, int> Pair;
vector<Pair> querys[N];
bool visit[N];
int ans[Q], ancestor[N], root[N], values[N];
int n, m, q;

void init () {
#define clr(x) memset ((x), 0, sizeof (x))
    clr (first), clr (visit), clr (values), clr (root);
    edgeCount = 0;
    for (int i = 1; i <= n; ++ i) {
        querys[i].clear();
    }
}

void addEdge (int u, int v, int w) {
    edgeCount ++;
    g[edgeCount] = Graph (v, w, first[u]), first[u] = edgeCount;
}

int find (int u) {
    int root = u;
    while (root != ancestor[root]) {
        root = ancestor[root];
    }
    while (u != root) {
        int temp = ancestor[u];
        ancestor[u] = root;
        u = temp;
    }
    return root;
}

void joint (int u, int v) {
    u = find (u);
    v = find (v);
    ancestor[v] = u;
}

void tarjan (int u, int f) {
    for (int iter = first[u]; iter != 0; iter = g[iter].next) {
        int v = g[iter].to;
        if (v != f) {
            tarjan (v, u);
            joint (u, v);
        }
    }
    visit[u] = true;
    for (int i = 0; i < querys[u].size(); ++ i) {
        int v = querys[u][i].first;
        if (visit[v]) {
            int lca = find (v);
            ans[querys[u][i].second] = values[u] + values[v] - 2 * values[lca];
        }
    }
}

void dfs (int u, int f, int r, int weight) {
    root[u] = r;
    visit[u] = true;
    values[u] = f == -1 ? 0 : values[f] + weight;
    for (int iter = first[u]; iter != 0; iter = g[iter].next) {
        int v = g[iter].to;
        if (v != f) {
            dfs (v, u, r, g[iter].weight);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf ("%d%d%d", &n, &m, &q) != EOF) {
        init();
        while (m --) {
            int u, v, w;
            scanf ("%d%d%d", &u, &v, &w);
            addEdge (u, v, w);
            addEdge (v, u, w);
        }
        memset (visit, 0, sizeof (visit));
        for (int i = 1; i <= n; ++ i) {
            ancestor[i] = i;
            if (!visit[i]) {
                dfs (i, -1, i, 0);
            }
        }
        for (int i = 1; i <= q; ++ i) {
            int u, v;
            scanf ("%d%d", &u, &v);
            if (root[u] != root[v]) {
                ans[i] = -1;
                continue;
            }
            querys[u].push_back (make_pair (v, i));
            querys[v].push_back (make_pair (u, i));
        }
        memset (visit, 0, sizeof (visit));
        for (int i = 1; i <= n; ++ i) {
            if (root[i] == i) {
                tarjan (i, -1);
            }
        }
        for (int i = 1; i <= q; ++ i) {
            if (ans[i] == -1) {
                puts ("Not connected");
            }
            else {
                printf ("%d\n", ans[i]);
            }
        }
    }
    return 0;
}
