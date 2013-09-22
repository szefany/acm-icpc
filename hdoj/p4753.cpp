#include <cstdio>
#include <cstring>
#include <map>

using std::map;
using std::min;
using std::max;

map<int, map<int, int> > edges;

const int contains[9][4] = {{0, 3, 4, 7}, {1, 4, 5, 8}, {2, 5, 6, 9},
                            {7, 10, 11, 14}, {8, 11, 12, 15}, {9, 12, 13, 16},
                            {14, 17, 18, 21}, {15, 18, 19, 22}, {16, 19, 20, 23}};

int belongs[24][2];
int amount[24];

void initialise() {
    edges[1][2] = 0, edges[2][3] = 1, edges[3][4] = 2;
    edges[1][5] = 3, edges[2][6] = 4, edges[3][7] = 5, edges[4][8] = 6;
    edges[5][6] = 7, edges[6][7] = 8, edges[7][8] = 9;
    edges[5][9] = 10, edges[6][10] = 11, edges[7][11] = 12, edges[8][12] = 13;
    edges[9][10] = 14, edges[10][11] = 15, edges[11][12] = 16;
    edges[9][13] = 17, edges[10][14] = 18, edges[11][15] = 19, edges[12][16] = 20;
    edges[13][14] = 21, edges[14][15] = 22, edges[15][16] = 23;
    memset(amount, 0, sizeof(amount));
    for (int i = 0; i < 9; ++ i) {
        for (int j = 0; j < 4; ++ j) {
            int x = contains[i][j];
            belongs[x][amount[x] ++] = i;
        }
    }
}

const int N = 25;
const int M = 12;
const int S = 1 << M;

int visit[N];
int new_id[N], which[N];
int dp[S], remain[S];
int n;

int main() {
    initialise();
    int test;
    scanf("%d", &test);
    for (int t = 1; t <= test; ++ t) {
        scanf("%d", &n);

        memset(visit, 0, sizeof(visit));
        for (int i = 1; i <= n; ++ i) {
            int a, b;
            scanf("%d%d", &a, &b);
            if (a > b) {
                std::swap(a, b);
            }
            visit[edges[a][b]] = i;
        }

        int score[2] = {0};
        for (int i = 0; i < 9; ++ i) {
            bool flag = true;
            int latest = -1;
            for (int j = 0; j < 4 && flag; ++ j) {
                flag &= visit[contains[i][j]] > 0;
                latest = max(latest, visit[contains[i][j]]);
            }
            if (flag) {
                score[latest & 1] ++;
            }
        }

        memset(new_id, 0, sizeof(new_id));
        int counter = 0;
        for (int i = 0; i < 24; ++ i) {
            if (!visit[i]) {
                new_id[i] = counter;
                which[counter ++] = i;
            }
        }

        for (int mask = 0; mask < 1 << counter; ++ mask) {
            remain[mask] = 9;
            for (int i = 0; i < 9; ++ i) {
                bool flag = true;
                for (int j = 0; j < 4; ++ j) {
                    int x = contains[i][j];
                    flag &= visit[x] || (1 << new_id[x] & mask);
                }
                remain[mask] -= flag;
            }
        }

        memset(dp, 0, sizeof(dp));
        for (int mask = (1 << counter) - 1; mask >= 0; -- mask) {
            for (int i = 0; i < counter; ++ i) {
                if (1 << i & mask) {
                    continue;
                }
                int x = which[i];
                int delta = 0;
                for (int j = 0; j < amount[x]; ++ j) {
                    int rect = belongs[x][j];
                    int number = 0;
                    for (int k = 0; k < 4; ++ k) {
                        int e = contains[rect][k];
                        number += visit[e] || (1 << new_id[e] & mask);
                    }
                    if (number == 3) {
                        delta ++;
                    }
                }
                int new_mask = mask | 1 << i;
                dp[mask] = max(dp[mask], remain[new_mask] - dp[new_mask] + delta);
            }
        }

        score[n + 1 & 1] += dp[0];
        score[n & 1] += remain[0] - dp[0];
        printf("Case #%d: ", t);
        puts(score[1] > score[0] ? "Tom200" : "Jerry404");
    }
    return 0;
}

