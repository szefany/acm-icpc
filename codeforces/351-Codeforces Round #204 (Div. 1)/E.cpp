#include <cstdio>
#include <cstring>
#include <iostream>
#include <climits>

const int N = 2000 + 10;

int dp[2][N], element[N], buffer[N], amount[N];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", element + i);
        if (element[i] < 0) {
            element[i] = -element[i];
        }
    }

    int answer = 0;
    while (n) {
        int max_value = -1;
        for (int i = 1; i <= n; ++ i) {
            max_value = std::max(max_value, element[i]);
        }
        element[n + 1] = -1;
        amount[n + 1] = 0;
        for (int i = n; i >= 1; -- i) {
            amount[i] = amount[i + 1] + (element[i + 1] == max_value);
        }

        memset(dp[0], 127, sizeof(dp[0]));
        dp[0][0] = 0;
        int count = 0;
        for (int i = 1; i <= n; ++ i) {
            if (element[i] == max_value) {
                count ++;
                memset(dp[count & 1], 127, sizeof(dp[count & 1]));
                for (int j = 0; j <= count; ++ j) {
                    dp[count & 1][j] = dp[count + 1 & 1][j] + i - (count - j);
                    if (j) {
                        dp[count & 1][j] = std::min(dp[count & 1][j], dp[count + 1 & 1][j - 1] + n - i - amount[i]);
                    }
                }
            }
        }
        int temp = INT_MAX;
        for (int i = 0; i <= count; ++ i) {
            temp = std::min(temp, dp[count & 1][i]);
        }
        answer += temp;

        int size = 0;
        for (int i = 1; i <= n; ++ i) {
            if (element[i] != max_value) {
                buffer[++ size] = element[i];
            }
        }
        memcpy(element, buffer, sizeof(int) * (size + 1));
        n = size;
    }
    printf("%d\n", answer);
    return 0;
}
