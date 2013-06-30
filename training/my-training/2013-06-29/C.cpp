#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int N = 200000 + 10;

double a[N];
int n, m;

int main() {
    freopen("input", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        scanf("%lf", a + i);
    }
    std::sort(a + 1, a + n + 1);

    double square_sum = 0, sum = 0, answer = 1E100;
    for (int i = 1; i < m; ++ i) {
        square_sum += a[i] * a[i];
        sum += a[i];
    }
    for (int i = m; i <= n; ++ i) {
        square_sum += a[i] * a[i];
        sum += a[i];
#define sqr(x) ((x) * (x))
        double temp = square_sum + m * sqr(sum / m) - 2 * sum * sum / m;
        answer = std::min(answer, temp);
        square_sum -= sqr(a[i - m + 1]);
        sum -= a[i - m + 1];
    }
    printf("%.2f\n", answer / m);
    return 0;
}
