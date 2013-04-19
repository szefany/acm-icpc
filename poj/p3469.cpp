#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 20000 + 1;
const int M = 1000000;
const int INF = 1 << 30;

struct Edge {
    int to, flow, capa, next;
    Edge() {}
    Edge(int v, int f, int c, int n): to(v), flow(f), capa(c), next(n) {}
} g[M];
int first[N], arc[N], edge_count;

int n, m, vs, vt;

void add_edge(int u, int v, int c) {
    edge_count ++;
    g[edge_count] = Edge(v, 0, c, first[u]), first[u] = edge_count;
    g[M - edge_count] = Edge(u, 0, 0, first[v]), first[v] = M - edge_count;
}

int queue[N], label[N];
bool bfs() {
    for (int i = 0; i <= vt; ++ i) {
        label[i] = 0;
    }
    queue[0] = vs;
    label[vs] = 1;
    for (int head = 0, tail = 0; head <= tail; ++ head) {
        int u = queue[head];
        for (int iter = first[u]; iter; iter = g[iter].next) {
            int v = g[iter].to;
            if (label[v] == 0 && g[iter].flow < g[iter].capa) {
                label[v] = label[u] + 1;
                queue[++ tail] = v;
                if (v == vt) {
                    return true;
                }
            }
        }
    }
    return false;
}

int dfs(int u, int limit) {
    if (u == vt) {
        return limit;
    }
    int delta = 0;
    for (int &iter = arc[u]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        if (label[v] == label[u] + 1 && g[iter].flow < g[iter].capa) {
            int r = dfs(v, std::min(limit - delta, g[iter].capa - g[iter].flow));
            delta += r;
            g[iter].flow += r;
            g[M - iter].flow -= r;
            if (delta == limit) {
                break;
            }
        }
    }
    return delta;
}

int main() {
    scanf("%d%d", &n, &m);
    vs = n;
    vt = n + 1;
    for (int i = 0; i < n; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(vs, i, a);
        add_edge(i, vt, b);
    }
    while (m --) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u --, v --;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    int answer = 0;
    while (bfs()) {
        for (int i = 0; i <= vt; ++ i) {
            arc[i] = first[i];
        }
        answer += dfs(vs, INF);
    }
    printf("%d\n", answer);
    return 0;
}
