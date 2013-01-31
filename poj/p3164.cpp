// POJ 3164, Command Network
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 105;
const int M = N * N;
const double INF = 1e10;
const double EPS = 1e-8;

struct Graph {
    int from, to;
    double weight;
    Graph () {}
    Graph (int u, int v, double w): from (u), to (v), weight (w) {}
} g[M];

double x[N], y[N], link_cost[N];
int visit[N], id[N], link_node[N];
int n, m, edge_count;

double dist (int u, int v) {
#define sqr(x) ((x) * (x))
    return sqrt (sqr (x[u] - x[v]) + sqr (y[u] - y[v]));
}

int sgn (double x) {
    if (x < -EPS) {
        return -1;
    }
    return x < EPS ? 0 : 1;
}

double solve (int root) {
    double result = 0;
    while (1) {
        for (int i = 1; i <= n; ++ i) {
            link_cost[i] = INF;
        }
        for (int iter = 1; iter <= edge_count; ++ iter) {
            int u = g[iter].from;
            int v = g[iter].to;
            if (g[iter].weight < link_cost[v] && u != v) {
                link_node[v] = u;
                link_cost[v] = g[iter].weight;
            }
        }
        for (int i = 1; i <= n; ++ i) {
            if (i != root && sgn (link_cost[i] - INF) == 0) {
                return -1;
            }
        }
        int cycle_count = 0;
        memset (id, 0, sizeof (id));
        memset (visit, 0, sizeof (visit));
        link_cost[root] = 0;
        for (int i = 1; i <= n; ++ i) {
            result += link_cost[i];
            int node = i;
            while (visit[node] != i && id[node] == 0 && node != root) {
                visit[node] = i;
                node = link_node[node];
            }
            if (node != root && id[node] == 0) {
                cycle_count ++;
                for (int u = link_node[node]; u != node; u = link_node[u]) {
                    id[u] = cycle_count;
                }
                id[node] = cycle_count;
            }
        }
        if (cycle_count == 0) {
            return result;
        }
        for (int i = 1; i <= n; ++ i) {
            if (id[i] == 0) {
                id[i] = ++ cycle_count;
            }
        }
        for (int iter = 1; iter <= edge_count; ++ iter) {
            int u = g[iter].from;
            int v = g[iter].to;
            g[iter].from = id[u];
            g[iter].to = id[v];
            if (u != v) {
                g[iter].weight -= link_cost[v];
            }
        }
        n = cycle_count;
        root = id[root];
    }
}

int main () {
    while (scanf ("%d%d", &n, &m) != EOF) {
        edge_count = 0;
        for (int i = 1; i <= n; ++ i) {
            scanf ("%lf%lf", &x[i], &y[i]);
        }
        for (int i = 1; i <= m; ++ i) {
            int u, v;
            scanf ("%d%d", &u, &v);
            if (u != v) {
                g[++ edge_count] = Graph (u, v, dist (u, v));
            }
        }
        double ans = solve (1);
        if (sgn (ans) < 0) {
            puts ("poor snoopy");
        }
        else {
            printf ("%.2f\n", ans);
        }
    }
    return 0;
}
