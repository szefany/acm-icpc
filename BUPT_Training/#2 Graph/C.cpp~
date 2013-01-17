#include <iostream>
#include <cstdio>
#include <cstring>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 300005;
const int M = 400005;

struct Graph {
    Graph () {}
    Graph (int u, int v, int w): from(u), to(v), weight(w) {}
    int from, to, weight;
} edges[M];

typedef pair<int, int> Pair;
vector<Pair> neighbors[N];
bool inTree[M];
int state[M];
int n, m;

bool cmp (int x, int y) {
    return edges[x].weight < edges[y].weight;
}

int ancestor[N];
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

int rank[M];
void kruskal () {
    for (int i = 1; i <= n; ++ i) {
        ancestor[i] = i;
    }
    for (int i = 1; i <= m; ++ i) {
        rank[i] = i;
    }
    sort (rank + 1, rank + m + 1, cmp);
    for (int i = 1, counter = 1; counter < n; ++ i) {
        int iter = rank[i];
        int u = edges[iter].from, du = find (u);
        int v = edges[iter].to, dv = find (v);
        if (du != dv) {
            inTree[iter] = true;
            ancestor[du] = dv;
            state[iter] = 2;
            counter ++;
            neighbors[u].push_back (make_pair (v, iter));
            neighbors[v].push_back (make_pair (u, iter));
        }
    }
}

bool visit[N];
int links[N];
void build_tree (int u, int f, int edge) {
    visit[u] = true;
    links[u] = edge;
    for (int i = 0; i < neighbors[u].size(); ++ i) {
        int v = neighbors[u][i].first;
        if (!visit[v]) {
            build_tree (v, u, neighbors[u][i].second);
        }
    }
}

int depth[N], pos[N], top[N], size[N], father[N], son[N], son_weight[N];
int values[N * 2];
struct Tree {
    int l, r, lch, rch, key;
} T[N * 2];
int root, nodeCount;
#define L (T[u].lch)
#define R (T[u].rch)

void build (int &u, int l, int r) {
    u = ++ nodeCount;
    T[u].l = l, T[u].r = r;
    if (l == r) {
        T[u].key = values[l];
        return;
    }
    build (L, l, l + r >> 1);
    build (R, (l + r >> 1) + 1, r);
    T[u].key = max (T[L].key, T[R].key);
}

int findMax (int u, int l, int r) {
    if (l <= T[u].l && r >= T[u].r) {
        return T[u].key;
    }
    if (r < T[R].l) return findMax (L, l, r);
    if (l > T[L].r) return findMax (R, l, r);
    return max (findMax (L, l, r), findMax (R, l, r));
}

void dfs1 (int u, int f) {
    depth[u] = f == -1 ? 0 : depth[f] + 1;
    father[u] = f;
    size[u] = 1;
    int &pivot = son[u];
    for (int i = 0; i < neighbors[u].size(); ++ i) {
        int v = neighbors[u][i].first;
        if (v != f) {
            dfs1 (v, u);
            size[u] += size[v];
            if (pivot == 0 || size[v] > size[pivot]) {
                pivot = v;
                son_weight[u] = edges[neighbors[u][i].second].weight;
            }
        }
    }
}

void dfs2 (int u, int Top, int value) {
    pos[u] = ++ nodeCount;
    values[nodeCount] = value;
    top[u] = Top;
    if (son[u]) {
        dfs2 (son[u], Top, son_weight[u]);
    }
    for (int i = 0; i < neighbors[u].size(); ++ i) {
        int v = neighbors[u][i].first;
        if (v != father[u] && v != son[u]) {
            dfs2 (v, v, edges[neighbors[u][i].second].weight);
        }
    }
}

void link_cut () {
    dfs1 (1, -1);
    nodeCount = 0, dfs2 (1, 1, -1);
    nodeCount = 0, build (root, 1, n);
}

int query (int u, int v) {
    int du = top[u], dv = top[v];
    int result = 0;
    while (du != dv) {
        if (depth[du] < depth[dv]) {
            swap (u, v);
            swap (du, dv);
        }
        int temp = findMax (root, pos[du], pos[u]);
        result = max (result, temp);
        u = father[du];
        du = top[u];
    }
    if (u != v) {
        if (depth[u] < depth[v]) {
            swap (u, v);
        }
        int temp = findMax (root, pos[son[v]], pos[u]);
        result = max (result, temp);
    }
    return result;
}

int main () {
    freopen ("input.txt", "r", stdin);
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= m; ++ i) {
        int u, v, w;
        scanf ("%d%d%d", &u, &v, &w);
        edges[i] = Graph (u, v, w);
    }
    kruskal ();
    build_tree (1, -1, -1);
    link_cut ();
    for (int i = 1; i <= n; ++ i) {
        ancestor[i] = i;
    }
    deque<int> queue;
    for (int i = 1; i <= m; ++ i) {
        int iter = rank[i];
        if (inTree[iter]) continue;
        int u = edges[iter].from, du = find (u);
        int v = edges[iter].to, dv = find (v);
        int w = edges[iter].weight;
        int weight = query (u, v);
        if (w > weight) continue;
        state[iter] = 1;
        for (u = du, v = dv; u != v; ) {
            if (depth[u] < depth[v]) {
                swap (u, v);
            }
            queue.push_back (u);
            if (edges[links[u]].weight == w) {
                state[links[u]] = 1;
            }
            u = find (father[u]);
        }
        while (!queue.empty()) {
            int x = queue.front();
            queue.pop_front();
            ancestor[x] = u;
        }
    }
    for (int i = 1; i <= m; ++ i) {
        if (state[i] == 2) puts ("any");
        else if (state[i] == 1) puts ("at least one");
        else puts ("none");
    }
    return 0;
}
