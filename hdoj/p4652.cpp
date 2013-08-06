#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>

const int N = 1000000 + 10;

long double a[N], b[N], g[N], sum_a[N], sum_b[N];

int main() {
    int test;
    while (scanf("%d", &test) != EOF) {
        while (test --) {
            int command, m, n;
            scanf("%d%d%d", &command, &m, &n);
            if (command == 0) {
                a[1] = 0;
                for (int i = 2; i <= n; ++ i) {
                    a[i] = m * (a[i - 1] - 1);
                }
                std::cout << std::fixed << std::setprecision(8) << 1 - a[n] << '\n';
            } else {
                a[1] = sum_a[1] = 1;
                b[1] = sum_b[1] = 0;
                for (int x = 1; x < n; ++ x) {
                    a[x + 1] = ((m - 1) * a[x] - sum_a[x - 1]) / (m - x);
                    b[x + 1] = ((m - 1) * b[x] - sum_b[x - 1] - m) / (m - x);
                    sum_a[x] = sum_a[x - 1] + a[x];
                    sum_b[x] = sum_b[x - 1] + b[x];
                }
                long double answer = -b[n] / a[n] + 1;
                std::cout << std::fixed << std::setprecision(8) << answer << '\n';
            }
        }
    }
    return 0;
}
