#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

const int N = 100 + 10;
const int M = 1000 + 10;
const int INF = 1 << 29;

int trans[N][N], cost[N][M], order[M];
int dp[M][N], from[M][N];
int n, m;

void update(int &t1, const int &s1, int &t2, const int &s2) {
    if (s1 < t1 || s1 == t1 && s2 < t2) {
        t1 = s1;
        t2 = s2;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            scanf("%d", &trans[i][j]);
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            scanf("%d", &cost[i][j]);
        }
    }
    for (int i = 0; i < m; ++ i) {
        cost[0][i] = INF;
    }

    std::string string;
    while (getline(std::cin, string)) {
        if (string.length() == 0) {
            continue;
        }
        std::stringstream buffer;
        buffer << string;
        int size = 0, x;
        while (buffer >> x) {
            order[++ size] = x;
        }
        dp[size + 1][0] = 0;
        for (int i = 1; i < n; ++ i) {
            dp[size + 1][i] = INF;
        }
        for (int i = size; i >= 1; -- i) {
            for (int j = 0; j < n; ++ j) {
                dp[i][j] = from[i][j] = INF;
                for (int k = 0; k < n; ++ k) {
                    update(dp[i][j], dp[i + 1][k] + trans[j][k] + cost[j][order[i]], from[i][j], k);
                }
            }
        }
        dp[0][0] = from[0][0] = INF;
        for (int i = 0; i < n; ++ i) {
            update(dp[0][0], dp[1][i] + trans[0][i], from[0][0], i);
        }
        printf("%d\n", dp[0][0]);
        for (int i = 1, x = from[0][0]; i <= size; x = from[i][x], ++ i) {
            printf("%d%c", x, i == size ? '\n' : ' ');
        }
    }
    return 0;
}
