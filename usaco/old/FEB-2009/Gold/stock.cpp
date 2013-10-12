#include <cstdio>
#include <iostream>

const int N = 50 + 1;
const int D = 10 + 1;
const int P = 700000 + 1;

int dp[P];
int price[N][D], n, m, money;

int main() {
    scanf("%d%d%d", &n, &m, &money);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            scanf("%d", &price[i][j]);
        }
    }
    for (int i = 1; i < m; ++ i) {
        for (int j = 0; j <= money; ++ j) {
            dp[j] = 0;
        }
        for (int j = 1; j <= n; ++ j) {
            for (int k = price[j][i]; k <= money; ++ k) {
                dp[k] = std::max(dp[k], dp[k - price[j][i]] + price[j][i + 1]);
            }
        }
        int temp = money;
        for (int j = money; j >= 0; -- j) {
            money = std::max(money, temp - j + dp[j]);
        }
    }
    printf("%d\n", money);
    return 0;
}
