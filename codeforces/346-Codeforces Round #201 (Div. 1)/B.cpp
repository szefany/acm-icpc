#include <cstdio>
#include <cstring>
#include <algorithm>

using std::max;

const int N = 100 + 10;

int next[N];
int dp[N][N][N];

struct data {
    int a, b, c;
    data(int a = 0, int b = 0, int c = 0): a(a), b(b), c(c) {}
} from[N][N][N];

char a[N], b[N], c[N];
char result[N];

int main() {
    scanf("%s%s%s", a + 1, b + 1, c + 1);
    int len_a = strlen(a + 1);
    int len_b = strlen(b + 1);
    int len_c = strlen(c + 1);

    next[1] = 0;
    for (int i = 2, j = 0; i <= len_c; ++ i) {
        while (j > 0 && c[i] != c[j + 1]) {
            j = next[j];
        }
        j += c[i] == c[j + 1];
        next[i] = j;
    }

    int a1 = 0, a2 = 0, a3 = 0; 
    int answer = 0;
    for (int i = 0; i <= len_a; ++ i) {
        for (int j = 0; j <= len_b; ++ j) {
            for (int k = 0; k < len_c; ++ k) {
                if (dp[i][j][k] > answer) {
                    answer = dp[i][j][k];
                    a1 = i;
                    a2 = j;
                    a3 = k;
                }
                if (dp[i][j][k] > dp[i + 1][j][k]) {
                    dp[i + 1][j][k] = dp[i][j][k];
                    from[i + 1][j][k] = data(i, j, k);
                }
                if (dp[i][j][k] > dp[i][j + 1][k]) {
                    dp[i][j + 1][k] = dp[i][j][k];
                    from[i][j + 1][k] = data(i, j, k);
                }
                if (i < len_a && j < len_b && a[i + 1] == b[j + 1]) {
                    char key = a[i + 1];
                    int x = k;
                    while (x > 0 && key != c[x + 1]) {
                        x = next[x];
                    }
                    x += key == c[x + 1];
                    if (x < len_c && dp[i][j][k] + 1 > dp[i + 1][j + 1][x]) {
                        dp[i + 1][j + 1][x] = dp[i][j][k] + 1;
                        from[i + 1][j + 1][x] = data(i, j, k);
                    }
                }
            }
        }
    }
    if (answer == 0) {
        puts("0");
    } else {
        int length = 0;
        while (dp[a1][a2][a3]) {
            int x = from[a1][a2][a3].a;
            int y = from[a1][a2][a3].b;
            int z = from[a1][a2][a3].c;
            if (x == a1 - 1 && y == a2 - 1) {
                result[length ++] = a[a1];
            }
            a1 = x;
            a2 = y;
            a3 = z;
        }
        std::reverse(result, result + length);
        puts(result);
    }
    return 0;
}
