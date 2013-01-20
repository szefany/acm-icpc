// POJ 3436, ACM Computer Factory
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 500;
const int M = 100000;
const int INF = 1 << 25;

struct Graph {
    Graph () {}
    Graph (int u, int v, int c, int f, int n): from(u), to(v), capa(c), flow(f), next(n) {}
    int from, to, capa, flow, next;
} g[M];
int first[N], arc[N], edgeCount;

int input_features[N][15], output_features[N][15];
int n, f, vs, vt;

void addEdge (int u, int v, int c) {
    edgeCount ++;
    g[edgeCount] = Graph (u, v, c, 0, first[u]), first[u] = edgeCount;
    g[M - edgeCount] = Graph (v, u, 0, 0, first[v]), first[v] = M - edgeCount;
}

int links[N], queue[N];
bool bfs () {
    memset (links, 0, sizeof (links));
    links[vs] = 1, queue[1] = vs;
    for (int head = 1, tail = 1; head <= tail; ++ head) {
        int u = queue[head];
        for (int iter = first[u]; iter != 0; iter = g[iter].next) {
            int v = g[iter].to;
            if (links[v] == 0 && g[iter].flow < g[iter].capa) {
                links[v] = links[u] + 1;
                queue[++ tail] = v;
            }
        }
    }
    return links[vt] != 0;
}

int dfs (int u, int d) {
    if (u == vt) return d;
    int delta = 0;
    for (int &iter = arc[u]; iter != 0; iter = g[iter].next) {
        int v = g[iter].to;
        if (links[v] == links[u] + 1 && g[iter].flow < g[iter].capa) {
            int r = dfs (v, min (g[iter].capa - g[iter].flow, d - delta));
            delta += r;
            g[iter].flow += r;
            g[M - iter].flow -= r;
            if (delta == d) return d;
        }
    }
    return delta;
}

int main () {
    scanf ("%d%d", &f, &n);
    for (int i = 1; i <= n; ++ i) {
        int x;
        scanf ("%d", &x);
        addEdge (i, i + n, x);
        for (int j = 1; j <= f; ++ j) {
            scanf ("%d", &input_features[i][j]);
        }
        for (int j = 1; j <= f; ++ j) {
            scanf ("%d", &output_features[i][j]);
        }
    }
    vs = n + n + 1, vt = n + n + 2;
    for (int i = 1; i <= n; ++ i) {
        bool source = true, dest = true;
        for (int j = 1; j <= f; ++ j) {
            if (input_features[i][j] == 1) {
                source = false;
            }
            if (output_features[i][j] == 0) {
                dest = false;
            }
        }
        if (source) {
            addEdge (vs, i, INF);
        }
        if (dest) {
            addEdge (i + n, vt, INF);
        }
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            if (i == j) continue;
            bool flag = true;
            for (int k = 1; k <= f && flag; ++ k) {
                if ((output_features[i][k] ^ 1) == input_features[j][k]) {
                    flag = false;
                }
            }
            if (flag) {
                addEdge (i + n, j, INF);
            }
        }
    }
    int flow = 0;
    while (bfs ()) {
        memcpy (arc, first, sizeof (first));
        flow += dfs (vs, INF);
    }
    int edges = 0;
    for (int iter = 1; iter <= edgeCount; ++ iter) {
        if (g[iter].from <= n + n && g[iter].to <= n + n && g[iter].flow > 0 && g[iter].from + n != g[iter].to) {
            edges ++;
        }
    }
    printf ("%d %d\n", flow, edges);
    for (int iter = 1; iter <= edgeCount; ++ iter) {
        if (g[iter].from <= n + n && g[iter].to <= n + n && g[iter].flow > 0 && g[iter].from + n != g[iter].to) {
            int u = g[iter].from > n ? g[iter].from - n : g[iter].from;
            int v = g[iter].to > n ? g[iter].to - n : g[iter].to;
            printf ("%d %d %d\n", u, v, g[iter].flow);
        }
    }
    return 0;
}
