// POJ 2987, Firing
#include <iostream>
#include <cstdio>
#include <cstring>

const int N = 10000 + 5;
const int M = 200000;
const long long INF = (1LL) << 50;

struct Edge {
    int to, next;
    long long flow, capa;
    Edge () {}
    Edge (int v, long long f, long long c, int n): to (v), flow (f), capa (c), next (n) {}
} g[M];
int first[N], arc[N], edge_count, vs, vt;

int n, m;
long long sum_profit;

void add_edge (int u, int v, long long c) {
    edge_count ++;
    g[edge_count] = Edge (v, 0, c, first[u]), first[u] = edge_count;
    g[M - edge_count] = Edge (u, 0, 0, first[v]), first[v] = M - edge_count;
}

int label[N], queue[N];
bool bfs () {
    memset (label, 0, sizeof (label));
    label[vs] = 1;
    queue[0] = vs;
    for (int head = 0, tail = 0; head <= tail; ++ head) {
        int u = queue[head];
        for (int iter = first[u]; iter; iter = g[iter].next) {
            int v = g[iter].to;
            if (g[iter].flow < g[iter].capa && label[v] == 0) {
                label[v] = label[u] + 1;
                queue[++ tail] = v;
            }
        }
    }
    return label[vt];
}

long long dfs (int u, long long d) {
    if (u == vt) {
        return d;
    }
    long long delta = 0;
    for (int& iter = arc[u]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        if (label[v] == label[u] + 1 && g[iter].flow < g[iter].capa) {
            long long r = dfs (v, std::min (d - delta, g[iter].capa - g[iter].flow));
            g[iter].flow += r;
            g[M - iter].flow -= r;
            delta += r;
            if (d == delta) {
                break;
            }
        }
    }
    return delta;
}

bool visit[N];
int find (int u) {
    int result = u != vs && u != vt;
    visit[u] = true;
    for (int iter = first[u]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        if (!visit[v] && g[iter].flow < g[iter].capa) {
            result += find (v);
        }
    }
    return result;
}

int main () {
    scanf ("%d%d", &n, &m);
    vs = n + 1;
    vt = n + 2;
    for (int i = 1; i <= n; ++ i) {
        int value;
        scanf ("%d", &value);
        if (value > 0) {
            add_edge (vs, i, value);
            sum_profit += value;
        } else if (value < 0) {
            add_edge (i, vt, -value);
        }
    }
    for (int i = 0; i < m; ++ i) {
        int u, v;
        scanf ("%d%d", &u, &v);
        add_edge (u, v, INF);
    }
    long long flow = 0;
    while (bfs()) {
        memcpy (arc, first, sizeof (first));
        flow += dfs (vs, INF);
    }
    printf ("%d %lld\n", find (vs), sum_profit - flow);
    return 0;
}
