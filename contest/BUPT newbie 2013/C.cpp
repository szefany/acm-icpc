// zwbjay, BUPT Newbie 2013
#include <cstdio>
#include <cstring>

const int N = 15;
const int M = 30;

struct Node {
    int mask;
    int ability[M];
} queue[1 << 17];

bool visit[1 << 17];
int need[N][M], supply[N][M], current[M];
int n, m;

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        scanf ("%d%d", &n, &m);
        for (int i = 0; i < m; ++ i) {
            scanf ("%d", &queue[0].ability[i]);
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                scanf ("%d", &need[i][j]);
            }
            for (int j = 0; j < m; ++ j) {
                scanf ("%d", &supply[i][j]);
            }
        }
        memset (visit, 0, sizeof (visit));
        int answer = -1;
        queue[0].mask = 0;
        for (int head = 0, tail = 0; head <= tail; ++ head) {
            int mask = queue[head].mask;
            if (mask & 1) {
                answer = __builtin_popcount (mask) - 1;
                break;
            }
            for (int i = 0; i < n; ++ i) {
                if (!(1 << i & mask) && !visit[mask | 1 << i]) {
                    bool valid = true;
                    for (int j = 0; j < m && valid; ++ j) {
                        valid &= queue[head].ability[j] >= need[i][j];
                    }
                    if (valid) {
                        tail ++;
                        queue[tail].mask = mask | 1 << i;
                        visit[mask | 1 << i] = true;
                        for (int j = 0; j < m; ++ j) {
                            queue[tail].ability[j] = queue[head].ability[j] + supply[i][j];
                        }
                    }
                }
            }
        }
        printf ("%d\n", answer);
    }
    return 0;
}
