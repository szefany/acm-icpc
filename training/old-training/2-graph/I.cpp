#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int M = 35;
const int N = M * M;
const int d[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

struct Graph {
    Graph () {}
    Graph (int v, int n): to(v), next(n) {}
    int to, next;
} g[N * N];
int edgeCount, first[N];

int A[M][M];
int n, m, k;

void addEdge (int u, int v) {
    edgeCount ++;
    g[edgeCount] = Graph (v, first[u]), first[u] = edgeCount;
}

bool vis[N];
int links[N], id[M][M];
int counter;
bool find (int u) {
    if (vis[u]) return false;
    vis[u] = true;
    for (int iter = first[u]; iter != 0; iter = g[iter].next) {
        int v = g[iter].to;
        if (links[v] == 0 || find (links[v])) {
            links[v] = u;
            return true;
        }
    }
    return false;
}

int main () {
    freopen ("input.txt", "r", stdin);
    scanf ("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; ++ i) {
        int x, y;
        scanf ("%d%d", &y, &x);
        A[x][y] = 1;
    }
    int temp[2] = {0, 0};
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            if (A[i][j]) continue;
            int color = (i + j & 1);
            id[i][j] = ++ counter;
            temp[color] ++;
        }
    }
    if (temp[0] != temp[1]) {
        puts ("NO");
        return 0;
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            if (A[i][j] || (i + j & 1)) continue;
            for (int k = 0; k < 4; ++ k) {
                int x = i + d[k][0];
                int y = j + d[k][1];
                if (x >= 1 && x <= n && y >= 1 && y <= m && !A[x][y]) {
                    addEdge (id[i][j], id[x][y]);
                }
            }
        }
    }
    bool flag = true;
    for (int i = 1; i <= n && flag; ++ i) {
        for (int j = 1; j <= m && flag; ++ j) {
            if (A[i][j] || (i + j & 1)) continue;
            memset (vis, 0, sizeof (vis));
            if (!find (id[i][j])) {
                flag = false;
                break;
            }
        }
    }
    puts (flag ? "YES" : "NO");
    return 0;
}

