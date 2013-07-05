#include <iostream>

const int N = 50;

long long dp[N][2];
int n;

int main() {
    std::cin >> n;
    dp[1][0] = dp[1][1] = 1;
    for (int i = 2; i <= n; ++ i) {
        dp[i][0] = dp[i - 1][1] + dp[i - 2][1];
        dp[i][1] = dp[i - 1][0] + dp[i - 2][0];
    }
    long long answer = dp[n][0] + dp[n][1];
    std::cout << answer << std::endl;
    return 0;
}
