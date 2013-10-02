#include <cstdio>
#include <cmath>
#include <iostream>

const int N = 1000 + 10;
const double INF = 1E50;

bool visit[N][N];
double dp[N][N];
int n, m;

int main() {
    int k;
    scanf("%d%d%d", &n, &m, &k);
    while (k --) {
        int x, y;
        scanf("%d%d", &x, &y);
        visit[x - 1][y - 1] = true;
    }
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j <= m; ++ j) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j <= m; ++ j) {
            dp[i + 1][j] = std::min(dp[i + 1][j], dp[i][j] + 100);
            dp[i][j + 1] = std::min(dp[i][j + 1], dp[i][j] + 100);
            if (visit[i][j]) {
                dp[i + 1][j + 1] = std::min(dp[i + 1][j + 1], dp[i][j] + sqrt(20000));
            }
        }
    }
    printf("%.0f\n", dp[n][m]);
    return 0;
}
