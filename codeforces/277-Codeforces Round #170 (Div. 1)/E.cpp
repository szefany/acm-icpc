#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

const int N = 1000;
const int M = N * N;

struct Edge {
    int from, to, flow, capa, next;
    double cost;
    Edge(int u, int v, int capa, double cost, int n): from(u), to(v), capa(capa), cost(cost), next(n), flow(0) {}
    Edge() {}
} g[M];
int first[N], vs, vt, edge_count;

void add_edge(int u, int v, int capa, double cost) {
    edge_count ++;
    g[edge_count] = Edge(u, v, capa, cost, first[u]), first[u] = edge_count;
    g[M - edge_count] = Edge(v, u, 0, -cost, first[v]), first[v] = M - edge_count;
}

const int Q = N + 10;
const double INF = 1E20;
int queue[N + N], links[N];
bool visit[N];
double dist[N];

void MincostFlow(int &flow, double &cost) {
    flow = cost = 0;
    while (true) {
        for (int i = 1; i < N; ++ i) {
            visit[i] = false;
            links[i] = 0;
            dist[i] = INF;
        }
        queue[1] = vs;
        dist[vs] = 0;
        for (int head = 0, tail = 1; head != tail; ) {
            head = head % Q + 1;
            int u = queue[head];
            visit[u] = false;
            for (int iter = first[u]; iter; iter = g[iter].next) {
                int v = g[iter].to;
                if (g[iter].flow < g[iter].capa && dist[u] + g[iter].cost < dist[v]) {
                    dist[v] = dist[u] + g[iter].cost;
                    links[v] = iter;
                    if (!visit[v]) {
                        visit[v] = true;
                        tail = tail % Q + 1;
                        queue[tail] = v;
                    }
                }
            }
        }
        if (links[vt] == 0) {
            break;
        }
        int delta = 1 << 20;
        for (int u = vt, iter; u != vs; u = g[iter].from) {
            iter = links[u];
            delta = std::min(delta, g[iter].capa - g[iter].flow);
        }
        for (int u = vt, iter; u != vs; u = g[iter].from) {
            iter = links[u];
            g[iter].flow += delta;
            g[M - iter].flow -= delta;
        }
        flow += delta;
        cost += delta * dist[vt];
    }
}

int x[N], y[N];
int n;

#define sqr(x) ((x) * (x))
double get_dist(int i, int j) {
    return sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d%d", &x[i], &y[i]);
    }
    vs = n + n + 1;
    vt = n + n + 2;
    for (int i = 1; i <= n; ++ i) {
        add_edge(vs, i, 2, 0);
        add_edge(i + n, vt, 1, 0);
        for (int j = 1; j <= n; ++ j) {
            if (y[i] > y[j]) {
                add_edge(i, j + n, 1, get_dist(i, j));
            }
        }
    }
    int flow;
    double cost;
    MincostFlow(flow, cost);
    if (flow != n - 1) {
        puts("-1");
    } else {
        printf("%.10f\n", cost);
    }
    return 0;
}
