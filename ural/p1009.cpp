#include <cstdio>
#include <iostream>

const int N = 20;

long long dp[N][2];
int n, k;

int main() {
    scanf("%d%d", &n, &k);
    dp[1][1] = k - 1;
    for (int i = 2; i <= n; ++ i) {
        dp[i][0] = dp[i - 1][1];
        dp[i][1] = (dp[i - 1][1] + dp[i - 1][0]) * (k - 1);
    }
    std::cout << dp[n][0] + dp[n][1] << '\n';
    return 0;
}
