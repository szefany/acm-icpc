#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

const int N = 5000 + 10;
const long long INF = 1LL << 50;

int a[N], b[N];
long long dp[2][N], min_value[2][N];
int n;

int abs(int x) {
    return x > 0 ? x : -x;
}

int main() {
    std::vector<int> total;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
        total.push_back(a[i]);
    }
    std::sort(total.begin(), total.end());
    total.resize(unique(total.begin(), total.end()) - total.begin());
    int s = total.size();

    for (int i = 0; i < s; ++ i) {
        dp[1][i] = abs(a[1] - total[i]);
        if (i == 0) {
            min_value[1][i] = dp[1][i];
        } else {
            min_value[1][i] = std::min(min_value[1][i - 1], dp[1][i]);
        }
    }
    for (int i = 2; i <= n; ++ i) {
        for (int j = 0; j < s; ++ j) {
            dp[i & 1][j] = abs(a[i] - total[j]) + min_value[i + 1 & 1][j];
            if (j == 0) {
                min_value[i & 1][j] = dp[i & 1][j];
            } else {
                min_value[i & 1][j] = std::min(min_value[i & 1][j - 1], dp[i & 1][j]);
            }
        }
    }
    long long answer = INF;
    for (int i = 0; i < s; ++ i) {
        answer = std::min(answer, dp[n & 1][i]);
    }
    std::cout << answer << std::endl;
    return 0;
 }
