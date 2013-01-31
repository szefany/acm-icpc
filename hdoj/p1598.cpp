// HDOJ 1598, find the most comfortable road
#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

const int N = 205;
const int M = 1005;

struct Graph {
    int from, to, weight;
    Graph () {}
    Graph (int u, int v, int w): from(u), to(v), weight(w) {}
};

Graph edges[M];
int ancestor[N];
int n, m;

bool cmp (Graph a, Graph b) {
    return a.weight < b.weight;
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

int main () {
    while (scanf ("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= m; ++ i) {
            int u, v, w;
            scanf ("%d%d%d", &u, &v, &w);
            edges[i] = Graph (u, v, w);
        }
        sort (edges + 1, edges + m + 1, cmp);
        int q;
        scanf ("%d", &q);
        while (q --) {
            int vs, vt;
            scanf ("%d%d", &vs, &vt);
            int ans = INT_MAX;
            for (int i = 1; i <= m; ++ i) {
                for (int j = 1; j <= n; ++ j) {
                    ancestor[j] = j;
                }
                int temp;
                bool flag = false;
                for (int j = i; j <= m; ++ j) {
                    int u = edges[j].from, du = find (u);
                    int v = edges[j].to, dv = find (v);
                    if (du != dv) {
                        ancestor[du] = dv;
                        if (find (vs) == find (vt)) {
                            temp = edges[j].weight - edges[i].weight;
                            flag = true;
                            break;
                        }
                    }
                }
                if (flag) {
                    ans = min (ans, temp);
                }
            }
            printf ("%d\n", ans == INT_MAX ? -1 : ans);
        }
    }
    return 0;
}
