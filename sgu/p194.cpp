#include <cstdio>
#include <cstring>
#include <iostream>

struct Flows {
    static const int N = 400;
    static const int M = 100000;
    static const int INF = 1 << 29;

    struct Edge {
        Edge(int u = 0, int v = 0, int f = 0, int c = 0, int n = 0): to(v), flow(f), capa(c), next(n) {}
        int from, to, flow, capa, next;
    } g[M];
    int first[N], arc[N], edge_count, ss, st, vs, vt;

    int id[N], od[N], n;

    void initialise(int size) {
        memset(first, 0, sizeof(first));
        memset(id, 0, sizeof(id));
        memset(od, 0, sizeof(od));
        edge_count = 0;
        n = size;
        ss = n + 1;
        st = n + 2;
    }

    void add_edge(int u, int v, int lower, int upper) {
        edge_count ++;
        g[edge_count] = Edge(u, v, 0, upper - lower, first[u]), first[u] = edge_count;
        g[M - edge_count] = Edge(v, u, 0, 0, first[v]), first[v] = M - edge_count;
        id[v] += lower;
        od[u] += lower;
    } 

    int queue[N], label[N];
    bool bfs(int s, int t) {
        memset(label, 0, sizeof(label));
        queue[0] = s;
        label[s] = 1;
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
        return label[t] != 0;
    }

    int dfs(int u, int t, int limit) {
        if (u == t) {
            return limit;
        }
        int delta = 0;
        for (int &iter = arc[u]; iter; iter = g[iter].next) {
            int v = g[iter].to;
            if (g[iter].flow < g[iter].capa && label[v] == label[u] + 1) {
                int r = dfs(v, t, std::min(limit - delta, g[iter].capa - g[iter].flow));
                g[iter].flow += r;
                g[M - iter].flow -= r;
                delta += r;
                if (delta == limit) {
                    break;
                }
            }
        }
        return delta;
    }

    int available_flow() {
        // no source and target
        for (int i = 1; i <= n; ++ i) { // NOTE THIS
            if (id[i]) {
                add_edge(ss, i, 0, id[i]);
            }
            if (od[i]) {
                add_edge(i, st, 0, od[i]);
            }
        }
        int result = 0;
        while (bfs(ss, st)) {
            memcpy(arc, first, sizeof(arc));
            result += dfs(ss, st, INF);
        }
        for (int iter = first[ss]; iter; iter = g[iter].next) {
            if (g[iter].flow != g[iter].capa) {
                return -1;
            }
        }
        return result;
    }
} flows;

const int M = 100000;

int bound[M];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    flows.initialise(n);
    for (int i = 1; i <= m; ++ i) {
        int u, v, a, b;
        scanf("%d%d%d%d", &u, &v, &a, &b);
        flows.add_edge(u, v, a, b);
        bound[i] = a;
    }
    int flow = flows.available_flow();
    if (flow == -1) {
        puts("NO");
    } else {
        puts("YES");
        for (int iter = 1; iter <= m; ++ iter) {
            printf("%d\n", flows.g[iter].flow + bound[iter]);
        }
    }
    return 0;
}
