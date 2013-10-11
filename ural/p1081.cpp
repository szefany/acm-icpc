#include <cstdio>

const int N = 50;

long long dp[2][N];
int n, m;

int main() {
    dp[1][1] = dp[0][1] = 1;
    for (int i = 2; i < N; ++ i) {
        dp[1][i] = dp[0][i - 1];
        dp[0][i] = dp[0][i - 1] + dp[1][i - 1];
    }
    scanf("%d%d", &n, &m);
    if (dp[0][n] + dp[1][n] < m) {
        puts("-1");
    } else {
        for (int i = n; i >= 1; -- i) {
            if (dp[0][i] >= m) {
                putchar('0');
            } else {
                m -= dp[0][i];
                putchar('1');
            }
        }
        puts("");
    }
    return 0;
}
