#include <cstdio>
#include <cstring>
#include <climits>

const int N = 500 + 10;

int a[N][N], from[N][N];
long long left[N][N], cost[N][N];
int n, m;

int queue[N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            scanf("%d", &a[i][j]);
            left[i][j] = left[i][j - 1] + a[i][j];
        }
    }

    memset(cost, 127, sizeof(cost));
    for (int i = 1; i <= m; ++ i) {
        cost[n][i] = a[n][i];
    }
    for (int i = n - 1; i >= 1; -- i) {
        for (int j = 1; j <= m; ++ j) {
            for (int k = 1; k <= m; ++ k) {
                long long temp = cost[i + 1][k] + (k <= j ? left[i][j] - left[i][k - 1] : left[i][k] - left[i][j - 1]);
                if (temp < cost[i][j]) {
                    cost[i][j] = temp;
                    from[i][j] = k;
                }
            }
        }
    }

    long long answer = 1LL << 60;
    int id = 0;
    for (int i = 1; i <= m; ++ i) {
        if (cost[1][i] < answer) {
            answer = cost[1][i];
            id = i;
        }
    }
    int length = 0;
    for (int i = 1, j = id; i <= n; ++ i) {
        queue[++ length] = j;
        int k = from[i][j];
        if (k == 0) {
            break;
        }
        if (k < j) {
            for (int x = j - 1; x >= k; -- x) {
                queue[++ length] = x;
            }
        } else {
            for (int x = j + 1; x <= k; ++ x) {
                queue[++ length] = x;
            }
        }
        j = k;
    }
    for (int i = 1; i <= length; ++ i) {
        printf("%d%c", queue[i], i == length ? '\n' : ' ');
    }
    return 0;
}
