#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

// #define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)
#define foreach(i, v) for (std::vector<int>::iterator i = (v).begin(); i != (v).end(); ++ i)

const int N = 200000 + 10;

std::vector<int> neighbors[N], tree_edges[N];
bool visit[N];
int depth[N], lowest[N], color[N], dp[N];
int n, m, length;

void initialise() {
    for (int i = 1; i <= n; ++ i) {
        neighbors[i].clear();
        tree_edges[i].clear();
        color[i] = dp[i] = depth[i] = lowest[i] = 0;
        visit[i] = false;
    }
}

void get_length(int u) {
    visit[u] = true;
    dp[u] = 0;
    foreach(iter, tree_edges[u]) {
        int v = *iter;
        if (!visit[v]) {
            get_length(v);
            length = std::max(length, dp[u] + dp[v] + 1);
            dp[u] = std::max(dp[u], dp[v] + 1);
        }
    }
}

void dfs(int u, int p) {
    lowest[u] = depth[u] = depth[p] + 1;
    bool first = true;
    foreach(iter, neighbors[u]) {
        int v = *iter;
        if (v == p && first) {
            first = false;
        } else if (depth[v]) {
            lowest[u] = std::min(lowest[u], depth[v]);
        } else {
            dfs(v, u);
            lowest[u] = std::min(lowest[u], lowest[v]);
        }
    }
}

int color_count;
void paint(int u, int c) {
    visit[u] = true;
    color[u] = c;
    foreach(iter, neighbors[u]) {
        int v = *iter;
        if (!visit[v]) {
            paint(v, lowest[v] > depth[u] ? ++ color_count : c);
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &m) && n + m > 0) {
        initialise();
        while (m --) {
            int u, v;
            scanf("%d%d", &u, &v);
            neighbors[u].push_back(v);
            neighbors[v].push_back(u);
        }

        dfs(1, 0);
        memset(visit, 0, sizeof(visit));
        color_count = 1;
        paint(1, 1);

        for (int u = 1; u <= n; ++ u) {
            foreach(iter, neighbors[u]) {
                int v = *iter;
                if (color[u] != color[v]) {
                    tree_edges[color[u]].push_back(color[v]);
                }
            }
        }

        memset(visit, 0, sizeof(visit));
        length = 0;
        get_length(1);
        printf("%d\n", color_count - 1 - length);
    }
    return 0;
}
