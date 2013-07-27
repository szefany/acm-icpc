#include <cstdio>
#include <cstring>
#include <vector>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 100000;

std::vector<int> neighbors[N];
bool visit[N], is_leaf[N];
int value[N], trap[N], father[N], queue[N], dp[N][5][2];
int n, m;

void initialise() {
    for (int i = 0; i < n; ++ i) {
        is_leaf[i] = true;
        father[i] = -1;
        visit[i] = false;
        neighbors[i].clear();
    }
}

int main() {
    int test;
    scanf("%d", &test);
    while (test --) {
        scanf("%d%d", &n, &m);
        initialise();
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", value + i, trap + i);
        }
        for (int i = 1; i < n; ++ i) {
            int u, v;
            scanf("%d%d", &u, &v);
            neighbors[u].push_back(v);
            neighbors[v].push_back(u);
        }

        queue[0] = 0;
        visit[0] = true;
        for (int head = 0, tail = 0; head <= tail; ++ head) {
            int u = queue[head];
            foreach(iter, neighbors[u]) {
                int v = *iter;
                if (!visit[v]) {
                    visit[v] = true;
                    father[v] = u;
                    is_leaf[u] = false;
                    queue[++ tail] = v;                    
                }
            }
        }
        int answer = 0;
        memset(dp, 200, sizeof(dp));
        for (int i = n - 1; i >= 0; -- i) {
            int u = queue[i];
            dp[u][trap[u]][trap[u]] = value[u];
            foreach(iter, neighbors[u]) {
                int v = *iter;
                if (v != father[u]) {
                    answer = std::max(answer, dp[u][0][0] + dp[v][0][0]);
                    for (int j = 0; j <= m; ++ j) {
                        for (int k = 0; j + k <= m; ++ k) {
                            for (int x = 0; x < 2; ++ x) {
                                for (int y = 0; y < 2; ++ y) {
                                    if (x + y || j + k < m) {
                                        answer = std::max(answer, dp[u][j][x] + dp[v][k][y]);
                                    }
                                }
                            }
                        }
                    }
                    for (int j = 0; j + trap[u] <= m; ++ j) {
                        for (int x = 0; x < 2; ++ x) {
                            dp[u][j + trap[u]][x] = std::max(dp[u][j + trap[u]][x], dp[v][j][x] + value[u]);
                        }
                    }
                }
            }
            for (int j = 0; j <= m; ++ j) {
                answer = std::max(answer, dp[u][j][1]);
                if (trap[u] || j < m) {
                    answer = std::max(answer, dp[u][j][0]);
                }
            }
        }
        printf("%d\n", answer);
    }
    return 0;
}