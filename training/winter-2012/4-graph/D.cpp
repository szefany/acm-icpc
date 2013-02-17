// POJ 3686, The Windy's
#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 3000;
const int INF = 1 << 30;

bool visit[2][N];
int g[N][N], lx[N], ly[N], match[N];
int n, m;

bool find (int u, int m) {
    visit[0][u] = true;
    for (int i = 0; i < m; ++ i) {
        if (lx[u] + ly[i] == g[u][i] && !visit[1][i]) {
            visit[1][i] = true;
            if (match[i] == -1 || find (match[i], m)) {
                match[i] = u;
                return true;
            }
        }
    }
    return false;
}

int km (int n, int m) {
    for (int i = 0; i < m; ++ i) {
        ly[i] = 0;
        match[i] = -1;
    }
    for (int i = 0; i < n; ++ i) {
        lx[i] = -INF;
        for (int j = 0; j < m; ++ j) {
            lx[i] = std::max (lx[i], g[i][j]);
        }
    }
    for (int u = 0; u < n; ++ u) {
        while (1) {
            memset (visit, 0, sizeof (visit));
            if (find (u, m)) {
                break;
            }
            int delta = INF;
            for (int i = 0; i < n; ++ i) {
                if (visit[0][i]) {
                    for (int j = 0; j < m; ++ j) {
                        if (!visit[1][j]) {
                            delta = std::min (delta, lx[i] + ly[j] - g[i][j]);
                        }
                    }
                }
            }
            for (int i = 0; i < n; ++ i) {
                if (visit[0][i]) {
                    lx[i] -= delta;
                }
            }
            for (int i = 0; i < m; ++ i) {
                if (visit[1][i]) {
                    ly[i] += delta;
                }
            }
        }        
    }
    int result = 0;
    for (int i = 0; i < m; ++ i) {
        if (match[i] != -1) {
            result += g[match[i]][i];
        }
    }
    return -result;
}

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        memset (g, 0, sizeof (g));
        scanf ("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                int x;
                scanf ("%d", &x);
                for (int k = 1; k <= n; ++ k) {
                    g[i][j * n + k - 1] = -x * k;
                }
            }
        }
        printf ("%.6f\n", (double)km (n, n * m) / n);
    }
    return 0;
}
