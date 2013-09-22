#include <cstdio>
#include <cstring>
#include <vector>

const int N = 100000 + 10;
const int M = 30;

int sum_a[N][M], sum_b[N][M];
int a[N], b[N], next[N];
int n, m;

int main() {
    while (scanf("%d%d%*d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", a + i);
        }
        for (int i = 1; i <= m; ++ i) {
            scanf("%d", b + i);
        }

        memset(sum_a[0], 0, sizeof(sum_a[0]));
        memset(sum_b[0], 0, sizeof(sum_b[0]));
        for (int i = 1; i <= n; ++ i) {
            memcpy(sum_a[i], sum_a[i - 1], sizeof(sum_a[0]));
            sum_a[i][a[i]] ++;
        }
        for (int i = 1; i <= m; ++ i) {
            memcpy(sum_b[i], sum_b[i - 1], sizeof(sum_b[0]));
            sum_b[i][b[i]] ++;
        }

        next[1] = 0;
        for (int i = 2, j = 0; i <= m; ++ i) {
            bool flag = false;
            while (j >= 0) {
                j ++;
                int small_1 = 0;
                for (int k = 1; k < b[i]; ++ k) {
                    small_1 += sum_b[i][k] - sum_b[i - j][k];
                }
                int equal_1 = sum_b[i][b[i]] - sum_b[i - j][b[i]];
                
                int small_2 = 0;
                for (int k = 1; k < b[j]; ++ k) {
                    small_2 += sum_b[j][k];
                }
                int equal_2 = sum_b[j][b[j]];

                if (small_1 == small_2 && equal_1 == equal_2) {
                    flag = true;
                    break;
                }
                j --;
                if (j == 0) {
                    break;
                }
                j = next[j];
            }
            next[i] = j;
        }

        std::vector<int> positions;
        for (int i = 1, j = 0; i <= n; ++ i) {
            bool flag = false;
            while (j >= 0) {
                j ++;
                int small_1 = 0;
                for (int k = 1; k < a[i]; ++ k) {
                    small_1 += sum_a[i][k] - sum_a[i - j][k];
                }
                int equal_1 = sum_a[i][a[i]] - sum_a[i - j][a[i]];
                
                int small_2 = 0;
                for (int k = 1; k < b[j]; ++ k) {
                    small_2 += sum_b[j][k];
                }
                int equal_2 = sum_b[j][b[j]];

                if (small_1 == small_2 && equal_1 == equal_2) {
                    flag = true;
                    break;
                }
                j --;
                if (j == 0) {
                    break;
                }
                j = next[j];
            }
            if (j == m) {
                positions.push_back(i);
                j = next[j];
            }
        }

        int answer = 0;
        if (positions.size() > 0) {
            answer = 1;
            for (int i = 0, now = positions[0]; i < positions.size(); ++ i) {
                if (positions[i] >= now + m) {
                    answer ++;
                    now = positions[i];
                }
            }
        }
        printf("%d\n", answer);
    }
    return 0;
}
