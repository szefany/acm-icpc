#include <cstdio>
#include <iostream>
#include <iomanip>

const int N = 15000 + 10;

long double dp[2][N][2];
long double ways[2][N];
int n, m;

int main() {
    scanf("%d%d", &n, &m);
    
    dp[n & 1][2][0] = 1;
    dp[n & 1][3][1] = 1;
    ways[n & 1][2] = 1;
    ways[n & 1][3] = 1;

    for (int i = n - 1; i >= 1; -- i) {
        dp[i & 1][2][0] = dp[i + 1 & 1][0][0] + 1;
        dp[i & 1][2][1] = dp[i + 1 & 1][0][0];
        ways[i & 1][2] = ways[i + 1 & 1][0];

        for (int j = 3; j <= m; ++ j) {
            ways[i & 1][j] = ways[i + 1 & 1][j - 2] + ways[i + 1 & 1][j - 3];
            if (ways[i & 1][j] == 0) {
                continue;
            }
            double p0 = ways[i + 1 & 1][j - 2] / ways[i & 1][j];
            double p1 = 1 - p0;
            dp[i & 1][j][0] = p0 * (dp[i + 1 & 1][j - 2][0] + 1) + p1 * dp[i + 1 & 1][j - 3][1];
            dp[i & 1][j][1] = p0 * dp[i + 1 & 1][j - 2][0] + p1 * (dp[i + 1 & 1][j - 3][1] + 1);
        }
    }
    std::cout << std::setprecision(8) << std::fixed << n - dp[1][m][1] << '\n';
    return 0;
}
