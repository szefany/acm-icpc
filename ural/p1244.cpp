#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 100 + 10;
const int M = 100000 + 10;

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

int from[N][M], weights[N];

bool visit[N];
int answer[N];

// -1: cannot arrive
// -2: multiple ways
// 0/1: use current

int main() {
    int total, n;
    scanf("%d%d", &total, &n);
    for (int i = 1; i < M; ++ i) {
        from[0][i] = -1;
    }
    from[0][0] = 0;
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", weights + i);
        int x = weights[i];
        for (int j = 0; j <= total; ++ j) {
            if (from[i - 1][j] < 0) {
                from[i][j] = from[i - 1][j];
            } else {
                from[i][j] = 0;
            }
            if (from[i][j] == -2) {
                continue;
            }
            if (j >= x) {
                if (from[i - 1][j - x] == -2) {
                    from[i][j] = -2;
                } else if (from[i - 1][j - x] != -1) {
                    if (from[i][j] == -1) {
                        from[i][j] = 1;
                    } else {
                        from[i][j] = -2;
                    }
                }
            }
        }
    }
    if (from[n][total] == -1) {
        puts("0");
    } else if (from[n][total] == -2) {
        puts("-1");
    } else {
        for (int i = n, j = total; i; -- i) {
            bool used = from[i][j];
            if (used) {
                visit[i] = true;
                j -= weights[i];
            }
        }
        int length = 0;
        for (int i = 1; i <= n; ++ i) {
            if (!visit[i]) {
                answer[++ length] = i;
            }
        }
        for (int i = 1; i <= length; ++ i) {
            printf("%d%c", answer[i], i == length ? '\n' : ' ');
        }
    }
    return 0;
}
