#include <cstdio>

const int N = 30;
const double EPS = 1E-16;

double prob[N][N];
int a[N], b[N], c[N];
int n;

const int S = 1 << 10;
bool arrived[S];
double expt[S];

double solve(int mask) {
    if (arrived[mask]) {
        return expt[mask];
    }
    if (mask == S - 1) {
        return expt[mask] = 0;
    }
    double p = 0, sum = 0;
    for (int i = 0; i < 10; ++ i) {
        if (1 << i & mask) {
            p += prob[n][i];
        } else {
            sum += solve(1 << i | mask) * prob[n][i];
        }
    }
    arrived[mask] = true;
    return expt[mask] = (1 + sum) / (1 - p);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", b + i);
    }
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", c + i);
    }

    prob[0][1] = 1;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j <= 10; ++ j) {
            for (int k = 0; k <= 9; ++ k) {
                int x = (a[i + 1] * k * k + b[i + 1] * k + c[i + 1]) % 11;
                prob[i + 1][(j * x) % 11] += prob[i][j] / 10;
            }
        }
    }
    prob[n][0] += prob[n][10];
    for (int i = 0; i <= 9; ++ i) {
        if (prob[n][i] < EPS) {
            puts("-1");
            return 0;
        }
    }

    double answer = solve(0);
    printf("%.10f\n", answer);
    return 0;
}
