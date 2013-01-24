// ZOJ 3469, Food Delivery
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 1005;

int n, v, s;
int b[N], x[N], f[N][N][2], sum[N];

struct data {
    int x, b;
    bool operator < (const data &other) const {
        return x < other.x;
    }
} a[N];

int main () {
    while (scanf ("%d%d%d", &n, &v, &s) != EOF) {
        for (int i = 1; i <= n; ++ i) {
            scanf ("%d%d", &a[i].x, &a[i].b);
        }
        sort (a + 1, a + n + 1);
        memset (f, 60, sizeof (f));
        memset (sum, 0, sizeof (sum));
        for (int i = 1; i <= n; ++ i) {
            sum[i] = sum[i - 1] + a[i].b;
        }
        for (int i = 1; i <= n; ++ i) {
            f[i][i][0] = f[i][i][1] = v * abs (a[i].x - s) * sum[n];
        }
        for (int len = 2; len <= n; ++ len) {
            for (int i = 1; i + len - 1 <= n; ++ i) {
                int j = i + len - 1;
                f[i][j][0] = min (f[i + 1][j][0] + (a[i + 1].x - a[i].x) * v * ((long long)sum[i] + sum[n] - sum[j]), 
                    f[i + 1][j][1] + (a[j].x - a[i].x) * v * ((long long)sum[i] + sum[n] - sum[j]));
                f[i][j][1] = min (f[i][j - 1][0] + (a[j].x - a[i].x) * v * ((long long)sum[i - 1] + sum[n] - sum[j - 1]),
                    f[i][j - 1][1] + (a[j].x - a[j - 1].x) * v * ((long long)sum[i - 1] + sum[n] - sum[j - 1]));
            }
        }
        printf ("%d\n", min (f[1][n][0], f[1][n][1]));
    }
    return 0;
}
