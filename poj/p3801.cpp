#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 400;
const int INF = 1 << 30;

struct Graph {
    static const int N = 400;
    static const int M = 1000000;

    struct Edge {
        int from, to, flow, capa, next;
        Edge() {}
        Edge(int u, int v, int capa, int n): from(u), to(v), flow(0), capa(capa), next(n) {}
    } g[M];
    int first[N], arc[N], edge_count;
    int vs, vt, ss, st, n, total_flow;
    int id[N], od[N];

    void initialise(int number) {
        edge_count = total_flow = 0;
        n = number;
        memset(first, 0, sizeof(first));
        memset(id, 0, sizeof(id));
        memset(od, 0, sizeof(od));
    }

    void add_edge(int u, int v, int capa) {
        edge_count ++;
        g[edge_count] = Edge(u, v, capa, first[u]), first[u] = edge_count;
        g[M - edge_count] = Edge(v, u, 0, first[v]), first[v] = M - edge_count;
    }

    void add_edge(int u, int v, int lower, int upper) {
        if (lower < upper) {
            add_edge(u, v, upper - lower);
        }
        id[v] += lower;
        od[u] += lower;
    }

    void flush() {
        total_flow = 0;
        for (int i = 1; i <= vt; ++ i) {
            if (id[i]) {
                total_flow += id[i];
                add_edge(ss, i, id[i]);
            }
            if (od[i]) {
                add_edge(i, st, od[i]);
            }
        }
    }

    int queue[N], links[N];
    bool bfs(int s, int t) {
        memset(links, 0, sizeof (links));
        links[s] = 1;
        queue[0] = s;
        for (int head = 0, tail = 0; head <= tail; ++ head) {
            int u = queue[head];
            for (int iter = first[u]; iter; iter = g[iter].next) {
                int v = g[iter].to;
                if (links[v] == 0 && g[iter].flow < g[iter].capa) {
                    links[v] = links[u] + 1;
                    queue[++ tail] = v;
                }
            }
        }
        return links[t];
    }

    int dfs(int u, int t, int d) {
        if (u == t) return d;
        int delta = 0;
        for (int &iter = arc[u]; iter != 0; iter = g[iter].next) {
            int v = g[iter].to;
            if (links[v] == links[u] + 1 && g[iter].flow < g[iter].capa) {
                int r = dfs(v, t, std::min(d - delta, g[iter].capa - g[iter].flow));
                g[iter].flow += r;
                g[M - iter].flow -= r;
                delta += r;
                if (delta == d) {
                    return d;
                }
            }
        }
        return delta;
    }

    int MinFlow() {
        int a = 0;
        while (bfs(ss, st)) {
            memcpy(arc, first, sizeof(arc));
            a += dfs(ss, st, INF);
        }
        add_edge(vt, vs, INF);
        int b = 0;
        while (bfs(ss, st)) {
            memcpy(arc, first, sizeof(arc));
            b += dfs(ss, st, INF);
        }
        return (a + b == total_flow) ? g[edge_count].flow : -1;
    }

} graph;

int get_id() {
    char buffer[10];
    scanf("%s", buffer);
    int result;
    if (*buffer == '+') {
        result = graph.vs;
    } else if (*buffer == '-') {
        result = graph.vt;
    } else {
        sscanf(buffer, "%d", &result);
    }
    return result;
}

int n, m;

int main() {
    freopen("input", "r", stdin);
    while (scanf("%d%d", &n, &m) && n + m > 0) {
        graph.initialise(n);
        int &ss = graph.ss, &st = graph.st;
        int &vs = graph.vs, &vt = graph.vt;
        vs = n + 1, vt = n + 2;
        ss = n + 3, st = n + 4;

        while (m --) {
            int u = get_id(), v = get_id(), bound;
            scanf("%d", &bound);
            graph.add_edge(u, v, bound, INF);
        }
        graph.flush();

        int answer = graph.MinFlow();
        if (answer == -1) {
            puts("impossible");
        } else {
            printf("%d\n", answer);
        }
    }
    return 0;
}
