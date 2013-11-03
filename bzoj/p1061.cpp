#include <cstdio>
#include <cstring>
#include <iostream>

const int INF = 1 << 29;

struct MincostFlow {
    static const int N = 1100;
    static const int M = 100000;
    struct Edge {
        int from, to, flow, capa, cost, next;
        Edge() {}
        Edge(int u, int v, int f, int capa, int cost, int n): from(u), to(v), flow(f), capa(capa), cost(cost), next(n) {}
    } g[M];
    int first[N], edge_count;

    int vs, vt;

    void init(int a, int b) {
        memset(first, 0, sizeof(first));
        memset(dist, 0, sizeof(dist));
        edge_count = 0;
        vs = a, vt = b;
    }

    void add_edge(int u, int v, int capa, int cost) {
        edge_count ++;
        g[edge_count] = Edge(u, v, 0, capa, cost, first[u]), first[u] = edge_count;
        g[M - edge_count] = Edge(v, u, 0, 0, -cost, first[v]), first[v] = M - edge_count;
    }

    int arc[N], dist[N], links[N], total_cost, total_flow;
    bool visit[N], in_queue[N];

    int dfs(int u, int flow) {
        if (u == vt) {
            total_cost += dist[u] * flow;
            return flow;
        }
        int result = 0;
        in_queue[u] = visit[u] = true;
        for (int &iter = arc[u]; iter; iter = g[iter].next) {
            int v = g[iter].to;
            int r = dist[u] + g[iter].cost - dist[v];
            int limit = std::min(flow, g[iter].capa);
            if (limit > 0) {
                links[v] = std::min(links[v], r);
                if (r == 0 && !in_queue[v]) {
                    r = dfs(v, limit);
                    result += r;
                    flow -= r;
                    g[iter].capa -= r;
                    g[M - iter].capa += r;
                }
            }
            if (flow == 0) {
                break;
            }
        }
        in_queue[u] = false;
        return result;
    }

    int mincost_flow() {
        total_cost = 0;
        total_flow = 0;
        while (1) {
            memcpy(arc, first, sizeof(arc));
            memset(visit, 0, sizeof(visit));
            memset(links, 100, sizeof(links));
            total_flow += dfs(vs, INF);
            int delta = links[0];
            for (int u = 1; u <= vt; ++ u) {
                if (!visit[u] && links[u] < delta) {
                    delta = links[u];
                }
            }
            if (delta == links[0]) {
                break;
            }
            for (int u = 1; u <= vt; ++ u) {
                if (!visit[u]) {
                    dist[u] += delta;
                }
            }
        }
        return total_cost;
    }
} graph;

void read(int &result) {
    char c;
    while (c = getchar(), c < '0' || c > '9');
    result = (c & 15);
    while (c = getchar(), c >= '0' && c <= '9') {
        result = result * 10 + (c & 15);
    }
}

const int P = 10000 + 10;

int need[P], n, m;

int main() {
    scanf("%d%d", &n, &m);
    int vs = n + 2;
    int vt = n + 3;
    graph.init(vs, vt);
    for (int i = 1; i <= n; ++ i) {
        read(need[i]);
        graph.add_edge(i + 1, i, INF, 0);
    }
    for (int i = 1; i <= n + 1; ++ i) {
        int x = need[i] - need[i - 1];
        if (x > 0) {
            graph.add_edge(vs, i, x, 0);
        } else {
            graph.add_edge(i, vt, -x, 0);
        }
    }

    for (int i = 1; i <= m; ++ i) {
        int left, right, cost;
        read(left), read(right), read(cost);
        graph.add_edge(left, right + 1, INF, cost);
    }

    int answer = graph.mincost_flow();
    printf("%d\n", answer);
    return 0;
}
