#include <cstdio>
#include <cstring>
#include <iostream>

typedef unsigned long long Long;

const int N = 40;

Long dp[N][N];
int n, m;

int main() {
    scanf("%d%d", &n, &m);
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= i; ++ j) {
            for (int a = 1; a <= i; ++ a) {
                dp[i][j] += dp[a - 1][j - 1] * dp[i - a][j - 1];
                for (int x = 0; x < j - 1; ++ x) {
                    dp[i][j] += dp[a - 1][j - 1] * dp[i - a][x];
                    dp[i][j] += dp[a - 1][x] * dp[i - a][j - 1];
                }
            }
        }
    }
    long long answer = 0;
    for (int i = m; i <= n; ++ i) {
        answer += dp[n][i];
    }
    std::cout << answer << std::endl;
    return 0;
}
