#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

struct Flows {
    static const int N = 1500;
    static const int M = 500000;
    static const int INF = 1 << 29;

    struct Edge {
        Edge(int u = 0, int v = 0, int f = 0, int c = 0, int n = 0): from(u), to(v), flow(f), capa(c), next(n) {}
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
        // printf("%d %d %d %d\n", u, v, lower, upper);
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

    int maximum_available_flow() {
        // with source and target
        for (int i = 1; i <= n; ++ i) { // NOTE THIS
            if (id[i]) {
                add_edge(ss, i, 0, id[i]);
            }
            if (od[i]) {
                add_edge(i, st, 0, od[i]);
            }
        }
        add_edge(vt, vs, 0, INF);
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
        result = 0;
        first[ss] = first[st] = 0;
        while (bfs(vs, vt)) {
            memcpy(arc, first, sizeof(arc));
            result += dfs(vs, vt, INF);
        }
        return result;
    }
} flows;

const int N = 1000 + 10;

int bound[150][N];
int answer[N];
int n, m;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        flows.initialise(n + m + 2);
        int &vs = flows.vs;
        int &vt = flows.vt;
        vs = n + m + 1;
        vt = n + m + 2;
        for (int i = 1; i <= m; ++ i) {
            int x;
            scanf("%d", &x);
            flows.add_edge(i + n, vt, x, flows.INF);
        }
        std::vector<std::pair<int, int> > order;
        for (int i = 1; i <= n; ++ i) {
            int number, limit;
            scanf("%d%d", &number, &limit);
            flows.add_edge(vs, i, 0, limit);
            for (int j = 1; j <= number; ++ j) {
                int x, l, r;
                scanf("%d%d%d", &x, &l, &r);
                x ++;
                flows.add_edge(i, x + n, l, r);
                order.push_back(std::make_pair(l, flows.edge_count));
            }
        }
        int flow = flows.maximum_available_flow();
        if (flow == -1) {
            puts("-1");
        } else {
            printf("%d\n", flow);
            for (int i = 0; i < order.size(); ++ i) {
                int l = order[i].first;
                int iter = order[i].second;
                printf("%d\n", l + flows.g[iter].flow);
            }
        }
        puts("");
    }
}
