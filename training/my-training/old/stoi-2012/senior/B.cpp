#include <cstdio>
#include <cstring>

const int N = 1000 + 5;
const int MOD = 1000000000 + 7;

int n, m, k, x0, y0;
int number[2][N], C[N][N], temp[N][N];

void solve (int now, int n, int k, int x0) {
    memset (temp, 0, sizeof (temp));
    temp[0][x0] = 1;
    for (int i = 1; i <= k; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            if (j > 1) {
                (temp[i][j] += temp[i - 1][j - 1]) %= MOD;
            }
            if (j < n) {
                (temp[i][j] += temp[i - 1][j + 1]) %= MOD;
            }
        }
    }
    for (int i = 0; i <= k; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            (number[now][i] += temp[i][j]) %= MOD;
        }
    }
}

int main () {
    scanf ("%d%d%d%d%d", &n, &m, &k, &x0, &y0);
    C[0][0] = 1;
    for (int i = 1; i <= k; ++ i) {
        C[i][0] = 1; 
        for (int j = 1; j <= i; ++ j) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
    }
    solve (0, n, k, x0);
    solve (1, m, k, y0);
    int answer = 0;
    for (int i = 0; i <= k; ++ i) {
        (answer += (long long)number[0][i] * number[1][k - i] % MOD * C[k][i] % MOD) %= MOD;
    }
    printf ("%d\n", answer);
    return 0;
}
