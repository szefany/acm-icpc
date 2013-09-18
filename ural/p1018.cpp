#include <cstdio>
#include <cstring>
#include <algorithm>

using std::max;
using std::min;

const int N = 100 + 10;
const int INF = 1 << 29;

struct Edge {
    int to, weight, next;
    Edge(int v = 0, int w = 0, int n = 0): to(v), weight(w), next(n) {}
} g[N * 2];
int first[N], edge_count;

void add_edge(int u, int v, int w) {
    edge_count ++;
    g[edge_count] = Edge(v, w, first[u]), first[u] = edge_count;
}

int dp[N][N], edges[N], sum[N];
int n, m;

int which[N], left[N], right[N];
int counter;

void dfs(int u, int p) {
    which[++ counter] = u;
    left[u] = right[u] = counter;
    for (int iter = first[u]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        if (v != p) {
            sum[v] += g[iter].weight;
            edges[v] ++;
            dfs(v, u);
            right[u] = max(right[u], right[v]);
            sum[u] += sum[v];
            edges[u] += edges[v];
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    int total = 0;
    for (int i = 1; i < n; ++ i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
        total += w;
    }
    m = n - 1 - m;
    dfs(1, 0);
    for (int i = 1; i <= m; ++ i) {
        dp[n + 1][i] = INF;
    }
    for (int i = n; i >= 1; -- i) {
        int u = which[i];
        int next = right[u] + 1;
        for (int j = 1; j <= m; ++ j) {
            dp[i][j] = min(dp[i + 1][j], dp[next][max(0, j - edges[u])] + sum[u]);
        }
    }
    printf("%d\n", total - dp[1][m]);
    return 0;
}
