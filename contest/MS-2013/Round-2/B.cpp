#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

const int N = 500 + 1;
const double EPS = 1E-10;
const double INF = 1E10;

int sgn(double x) {
    if (x < -EPS) {
        return -1;
    }
    return x < EPS ? 0 : 1;
}

double x0;
struct Data {
    double pro[2], neg[2];
    bool operator < (const Data &other) const {
        return (pro[0] - x0 * neg[0] - pro[1] + x0 * neg[1]) 
            - (other.pro[0] - x0 * other.neg[0] - other.pro[1] + x0 * other.neg[1]) >= EPS;
    }
} data[N];

double f[N][N];
int n, n1, n2;

double solve(double x) {
    x0 = x;
    std::sort(data + 1, data + n + 1);
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j <= n1 + n2; ++ j) {
            f[i][j] = -INF;
        }
    }
    f[0][0] = 0;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 0; j <= std::min(i, n1 + n2); ++ j) {
            f[i][j] = f[i - 1][j];
            if (j >= 1) {
                double temp = f[i - 1][j - 1];
                if (j <= n1) {
                    temp += data[i].pro[0] - x * data[i].neg[0];
                } else {
                    temp += data[i].pro[1] - x * data[i].neg[1];
                }
                f[i][j] = std::max(f[i][j], temp);
            }
        }
    }
    return f[n][n1 + n2];
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        scanf("%d%d%d", &n, &n1, &n2);
        for (int i = 1; i <= n; ++ i) {
            scanf("%lf%lf%lf%lf", &data[i].pro[0], &data[i].neg[0], &data[i].pro[1], &data[i].neg[1]);
        }
        double l = 0, r = 1E8;
        while (r - l >= 1E-8) {
            double m = (l + r) / 2;
            if (solve(m) >= -EPS) {
                l = m;
            } else {
                r = m;
            }
        }
        double answer = (l + r) / 2;
        printf("Case #%d: %.6f\n", t, answer);
    }
    return 0;
}
