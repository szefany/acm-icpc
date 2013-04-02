#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1600;
const int M = 20005;
long long INF = -(1LL << 60);

int elements[N][N];
long long f[N][N], min_value[N][N], max_value[N][N];
int n, m;

bool cmp (int x, int y) {
    return x > y;
}

int main () {
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            scanf ("%d", &elements[i][j]);
        }
    }
    memset (f, 200, sizeof (f));
    memset (min_value, 200, sizeof (min_value));
    memset (max_value, 200, sizeof (max_value));
    memset (min_value[0], 0, sizeof (min_value[0]));
    memset (max_value[0], 0, sizeof (max_value[0]));
    for (int i = 1; i <= n; ++ i) {
        long long sum = 0;
        for (int j = 1; j <= m; ++ j) {
            sum += elements[i][j];
            if (i & 1) {
                f[i][j] = sum + min_value[i - 1][j - 1];
            } else {
                f[i][j] = sum + max_value[i - 1][j + 1];
            }
        }
        for (int j = 1; j <= m; ++ j) {
            min_value[i][j] = max (min_value[i][j - 1], f[i][j]);
        }
        for (int j = m; j >= 1; -- j) {
            max_value[i][j] = max (max_value[i][j + 1], f[i][j]);
        }
    }
    long long ans = INF;
    for (int i = 1; i <= m; ++ i) {
        ans = max (ans, f[n][i]);
    }
    cout << ans << endl;
    return 0;
}
