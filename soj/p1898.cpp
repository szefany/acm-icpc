#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>

const int N = 100 + 1;

std::vector<int> neighbors[N];
int dp[N][N], contain[N], temp[N], n, total;
bool black[N];

void dfs(int u, int p) {
    contain[u] = black[u];
    for (int i = 0; i < neighbors[u].size(); ++ i) {
        int v = neighbors[u][i];
        if (v != p) {
            dfs(v, u);
            contain[u] += contain[v];
        }
    }

    if (black[u]) {
        dp[u][1] = 1;
    } else if (contain[u]) {
        dp[u][1] = 0;
    }
    for (int i = 0; i < neighbors[u].size(); ++ i) {
        int v = neighbors[u][i];
        if (v != p) {
            memcpy(temp, dp[u], sizeof(temp));
            for (int j = 1; j <= total; ++ j) {
                for (int k = 1; k <= j; ++ k) {
                    if (dp[v][k] >= 0 && temp[j - k] >= 0) {
                        dp[u][j] = std::max(dp[u][j], dp[v][k] + temp[j - k]);
                    }
                }
            }
        }
    }
}

int main() {
    int test;
    scanf("%d", &test);
    while (test --) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i) {
            neighbors[i].clear();
            black[i] = false;
        }
        total = 0;
        for (int i = 0; i < n; ++ i) {
            char buffer[2];
            scanf("%s", buffer);
            if (*buffer == 'b') {
                total ++;
                black[i] = true;
            }
        }
        for (int i = 0; i < n - 1; ++ i) {
            int u, v;
            scanf("%d%d", &u, &v);
            u --, v --;
            neighbors[u].push_back(v);
            neighbors[v].push_back(u);
        }

        memset(dp, 200, sizeof(dp));
        dfs(0, -1);

        int answer = 0;
        for (int i = 0; i < n; ++ i) {
            answer = std::max(answer, dp[i][total]);
        }
        answer = total - answer;
        printf("%d\n", answer);
    }
    return 0;
}
