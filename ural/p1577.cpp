#include <cstdio>
#include <cstring>

const int N = 2000 + 10;
const int INF = 1 << 29;
const int MOD = 1000000000 + 7;

int minimal[N][N], amount[N][N];
char a[N], b[N];

void update(int &dest_1, int &dest_2, int src_1, int src_2) {
    if (src_1 < dest_1) {
        dest_1 = src_1;
        dest_2 = src_2;
    } else if (src_1 == dest_1) {
        (dest_2 += src_2) %= MOD;
    }
}

int main() {
    scanf("%s", a + 1);
    int n = strlen(a + 1);
    scanf("%s", b + 1);
    int m = strlen(b + 1);

    minimal[0][0] = 0;
    amount[0][0] = 1;
    for (int i = 1; i <= n; ++ i) {
        minimal[i][0] = i;
        amount[i][0] = 1;
    }
    for (int i = 1; i <= m; ++ i) {
        minimal[0][i] = i;
        amount[0][i] = 1;
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            minimal[i][j] = INF;
            amount[i][j] = 0;
            if (a[i] == b[j]) {
                update(minimal[i][j], amount[i][j], minimal[i - 1][j - 1] + 1, amount[i - 1][j - 1]);
            } else {
                update(minimal[i][j], amount[i][j], minimal[i - 1][j] + 1, amount[i - 1][j]);
                update(minimal[i][j], amount[i][j], minimal[i][j - 1] + 1, amount[i][j - 1]);
            }
        }
    }
    printf("%d\n", amount[n][m]);
    return 0;
}
