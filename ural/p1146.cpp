#include <cstdio>
#include <iostream>

const int N = 100 + 10;
const int INF = 1 << 20;

int matrix[N][N], height[N], sum[N][N];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            scanf("%d", &matrix[i][j]);
            sum[i][j] = sum[i - 1][j] + matrix[i][j];
        }
    }
    int answer = -INF;
    for (int lower = 1; lower <= n; ++ lower) {
        for (int upper = lower; upper <= n; ++ upper) {
            int current = 0;
            for (int i = 1; i <= n; ++ i) {
                height[i] = sum[upper][i] - sum[lower - 1][i];
                current += height[i];
                answer = std::max(answer, current);
                if (current <= 0) {
                    current = 0;
                }
            }
        }
    }
    printf("%d\n", answer);
    return 0;
}
