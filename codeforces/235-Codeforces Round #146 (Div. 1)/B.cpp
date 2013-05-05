#include <cstdio>

const int N = 100000 + 1;

double prob[N], dp[N];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%lf", &prob[i]);
    }
    dp[0] = 0;
    double temp = 0;
    for (int i = 1; i <= n; ++ i) {
        temp = (temp + prob[i - 1]) * prob[i];
        dp[i] = dp[i - 1] + prob[i] + 2 * temp;
    }
    printf("%.10f\n", dp[n]);
    return 0;
}
