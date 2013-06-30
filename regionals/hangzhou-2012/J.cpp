#include <cstdio>
#include <cstring>
#include <climits>

const int N = 55;

int x[N], y[N], range[N];
int n, m, answer;
bool visit[N][N], need[N][N];

int queue[N];

int abs(int x) {
    return x < 0 ? -x : x;
}

int main() {
    while (scanf("%d", &n) && n > 0) {
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= n; ++ j) {
                need[i][j] = true;
            }
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d", x + i, y + i);
            need[x[i]][y[i]] = false;
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%d", range + i);
        }
        int total = n * n - m;

        answer = -1;
        for (int mask = 0; mask < 1 << m; ++ mask) {
            memset(visit, 0, sizeof(visit));
            int counter = 0, number = 0;
            for (int i = 0; i < m; ++ i) {
                if (1 << i & mask) {
                    number ++;
                    int u = i, rx = x[u], ry = y[u], r = range[u];
                    for (int x = 1; x <= n; ++ x) {
                        for (int y = 1; y <= n; ++ y) {
                            if (need[x][y] && !visit[x][y] && abs(rx - x) + abs(ry - y) <= r) {
                                visit[x][y] = true;
                                counter ++;
                            }
                        }
                    }
                }
            }
            if (counter == total && (answer == -1 || number < answer)) {
                answer = number;
            }
        }
        printf("%d\n", answer);
    }
    return 0;
}
