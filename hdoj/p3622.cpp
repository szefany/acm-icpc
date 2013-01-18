// HDOJ 3622, Bomb Game
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 505;
const int M = 50000;

struct Graph {
    Graph () {}
    Graph (int v, int n): to(v), next(n) {}
    int to, next;
} g[2][M];
int first[2][M], edgeCount;

double x[N][2], y[N][2];
bool visit[N];
int rank[N], color[N];
int n, counter;

void init () {
    memset (first, 0, sizeof (first));
    memset (color, 0, sizeof (color));
    edgeCount = 0;
}

bool judge (const double &a, const double &b) {
    return b - a > 1e-6;
}

double sqr (double x) {
    return x * x;
}

double dist (int i, int p1, int j, int p2) {
    return sqrt (sqr (x[i][p1] - x[j][p2]) + sqr (y[i][p1] - y[j][p2]));
}

void dfs1 (int u) {
    visit[u] = true;
    for (int iter = first[0][u]; iter != 0; iter = g[0][iter].next) {
        int v = g[0][iter].to;
        if (!visit[v]) {
            dfs1 (v);
        }
    }
    rank[++ counter] = u;
}

void dfs2 (int u) {
    visit[u] = true;
    color[u] = counter;
    for (int iter = first[1][u]; iter != 0; iter = g[1][iter].next) {
        int v = g[1][iter].to;
        if (!visit[v]) {
            dfs2 (v);
        }
    }
}

void addEdge (int u, int p1, int v, int p2) {
    if (p1 == 1) u += n;
    if (p2 == 1) v += n;
    // cout << u << " " << v << endl;
    edgeCount ++;
    g[0][edgeCount] = Graph (v, first[0][u]), first[0][u] = edgeCount;
    g[1][edgeCount] = Graph (u, first[1][v]), first[1][v] = edgeCount;
}

bool check (double r) {
    init ();
    for (int i = 1; i <= n; ++ i) {
        for (int j = i + 1; j <= n; ++ j) {
            if (judge (dist (i, 0, j, 0), 2 * r)) {
                addEdge (i, 0, j, 1);
                addEdge (j, 0, i, 1);
            }
            if (judge (dist (i, 0, j, 1), 2 * r)) {
                addEdge (i, 0, j, 0);
                addEdge (j, 1, i, 1);
            }
            if (judge (dist (i, 1, j, 0), 2 * r)) {
                addEdge (i, 1, j, 1);
                addEdge (j, 0, i, 0);
            }
            if (judge (dist (i, 1, j, 1), 2 * r)) {
                addEdge (i, 1, j, 0);
                addEdge (j, 1, i, 0);
            }
        }
    }
    counter = 0;
    memset (visit, 0, sizeof (visit));
    for (int i = 1; i <= n + n; ++ i) {
        if (!visit[i]) {
            dfs1 (i);
        }
    }
    memset (visit, 0, sizeof (visit));
    counter = 0;
    for (int i = n + n; i >= 1; -- i) {
        int u = rank[i];
        if (!visit[u]) {
            counter ++;
            dfs2 (u);
        }
    }
    for (int i = 1; i <= n; ++ i) {
        if (color[i] == color[i + n]) {
            return false;
        }
    }
    return true;
}

int main () {
    freopen ("input.txt", "r", stdin);
    while (scanf ("%d", &n) != EOF) {
        init ();
        for (int i = 1; i <= n; ++ i) {
            scanf ("%lf%lf%lf%lf", &x[i][0], &y[i][0], &x[i][1], &y[i][1]);
        }
        double l = 0, r = 100000;
        while (r - l > 1e-5) {
            double mid = (l + r) / 2;
            if (check (mid)) {
                if (mid < 1) {
                    int x;
                }
                l = mid;
            }
            else {
                r = mid;
            }
        }
        printf ("%.2f\n", (l + r) / 2);
    }
    return 0;
}
