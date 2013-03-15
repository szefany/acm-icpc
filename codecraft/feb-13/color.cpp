#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 14;
const int C = N * 10;
const int S = 1 << N;

long long dp[N][S];
int n, m;

std::vector <int> available[N], nodes[C], all_colors;
bool valid[N][C], g[N][N], visit[N];

void initialise () {
    memset (g, 0, sizeof (g));
    memset (valid, 0, sizeof (valid));
    all_colors.clear();
    for (int i = 0; i < N; ++ i) {
        available[i].clear();
    }
}

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        initialise ();
        scanf ("%d", &n);
        char buffer[20];
        for (int i = 0; i < n; ++ i) {
            scanf ("%s", buffer);
            for (int j = 0; j < n; ++ j) {
                g[i][j] = buffer[j] == 'Y';
            }
        }
        for (int i = 0; i < n; ++ i) {
            int number;
            scanf ("%d", &number);
            while (number --) {
                int x;
                scanf ("%d", &x);
                available[i].push_back (x);
                all_colors.push_back (x);
            }
        }
        std::sort (all_colors.begin(), all_colors.end());
        all_colors.resize (unique (all_colors.begin(), all_colors.end()) - all_colors.begin());
        int color_count = all_colors.size();
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < available[i].size(); ++ j) {
                int color = std::lower_bound (all_colors.begin(), all_colors.end(), available[i][j]) \
                    - all_colors.begin() + 1;
                valid[i][color] = true;
            }
        }
        memset (dp, 0, sizeof (dp));
        dp[0][0] = 1;
        for (int i = 0; i < color_count; ++ i) {
            for (int mask = 0; mask < 1 << n; ++ mask) {
                if (dp[i][mask] == 0) {
                    continue;
                }
                dp[i + 1][mask] += dp[i][mask];
                int total_mask = ((1 << n) - 1) ^ mask;
                for (int j = 0; j < n; ++ j) {
                    if (!valid[j][i + 1] && (1 << j & total_mask)) {
                        total_mask ^= 1 << j;
                    }
                }
                for (int sub_mask = total_mask; sub_mask; sub_mask = (sub_mask - 1) & total_mask) {
                    dp[i + 1][mask | sub_mask] += dp[i][mask];
                }
            }
        }
        printf ("%lld\n", dp[color_count][(1 << n) - 1]);
    }
    return 0;
}
