#include <cstdio>
#include <iostream>

const int N = 500 + 10;

long long dp[N];
int n;

int main() {
    scanf("%d", &n);
    dp[0] = 1;
    for (int j = 1; j < n; ++ j) {
        for (int i = n; i >= j; -- i) {
            dp[i] += dp[i - j];
        }
    }
    std::cout << dp[n] << std::endl;
    return 0;
}
