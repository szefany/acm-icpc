// SGU 525, Revolutionary Roads
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1005;
const int M = 40000;

struct Graph {
    Graph () {}
    Graph (int u, int v, int n): from(u), to(v), next(n) {}
    int from, to, next;
} g[3][M];
int first[3][N], edgeCount[3];

void addEdge (int u, int v, int t) {
    edgeCount[t] ++;
    g[t][edgeCount[t]] = Graph (u, v, first[t][u]), first[t][u] = edgeCount[t];
}

int n, m, ans;
int rank[N], counter, color[N], colors, amount[N];
int roads[M], length;
bool reach[N][N];
int vis[N];

void dfs1 (int u) {
    vis[u] = 1;
    for (int iter = first[0][u]; iter != 0; iter = g[0][iter].next) {
        int v = g[0][iter].to;
        if (!vis[v]) dfs1 (v);
    }
    rank[++ counter] = u;
}

void dfs2 (int u) {
    vis[u] = 1;
    color[u] = colors;
    for (int iter = first[1][u]; iter != 0; iter = g[1][iter].next) {
        int v = g[1][iter].to;
        if (!vis[v]) dfs2 (v);
    }
}

void dfs (int u, int root) {
    vis[u] = root;
    reach[root][u] = true;
    for (int iter = first[2][u]; iter != 0; iter = g[2][iter].next) {
        int v = g[2][iter].to;
        if (vis[v] != root) dfs (v, root);
    }
}

void update (int u, int key) {
    if (key > ans) {
        ans = key;
        length = 1;
        roads[1] = u;
    } else if (key == ans) {
        roads[++ length] = u;
    }
}

int main () {
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= m; ++ i) {
        int u, v;
        scanf ("%d%d", &u, &v);
        addEdge (u, v, 0);
        addEdge (v, u, 1);
    }
    for (int i = 1; i <= n; ++ i) {
        if (!vis[i]) dfs1 (i);
    }
    memset (vis, 0, sizeof (vis));
    for (int i = n; i >= 1; -- i) {
        int u = rank[i];
        if (!vis[u]) {
            colors ++;
            dfs2 (u);
        }
    }
    for (int i = 1; i <= n; ++ i) {
        amount[color[i]] ++;
    }
    for (int i = 1; i <= m; ++ i) {
        int u = color[g[0][i].from];
        int v = color[g[0][i].to];
        if (u != v) addEdge (u, v, 2);
    }
    memset (vis, 0, sizeof (vis));
    int total = colors;
    for (int i = 1; i <= total; ++ i) {
        dfs (i, i);
    }
    ans = 1;
    for (int iter = 1; iter <= m; ++ iter) {
        int u = color[g[0][iter].from];
        int v = color[g[0][iter].to];
        if (u == v) {
            update (iter, amount[u]);
        } else {
            int temp = amount[u] + amount[v];
            for (int i = 1; i <= total; ++ i) {
                if (i == u || i == v) continue;
                if (reach[u][i] && reach[i][v]) {
                    temp += amount[i];
                }
            }
            update (iter, temp);
        }
    }
    printf ("%d\n%d\n", ans, length);
    for (int i = 1; i <= length; ++ i) {
        printf ("%d%c", roads[i], i == length ? '\n' : ' ');
    }
    return 0;
}
