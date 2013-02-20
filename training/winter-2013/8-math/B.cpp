// UVALive 5760, Alice and Bob
#include <cstdio>
#include <cstring>

const int N = 60;

int sg[N][N * 1000];

int solve (int x, int y) {
    if (sg[x][y] != -1) {
        return sg[x][y];
    }
    if (y == 1) {
        return solve (x + 1, 0);
    }
    if (x == 0) {
        return sg[x][y] = y % 2;
    }
    if (x > 0 && solve (x - 1, y) == 0 || y > 0 && solve (x, y - 1) == 0 || x > 0 && y > 0 \
        && solve (x - 1, y + 1) == 0 || x > 1 && solve (x - 2, y + 2 + (y != 0)) == 0) {
        return sg[x][y] = 1;
    }
    return sg[x][y] = 0;
}

int main () {
    memset (sg, -1, sizeof (sg));
    int test_count;
    scanf ("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        int n;
        scanf ("%d", &n);
        int number = 0, sum = 0;
        for (int i = 0; i < n; ++ i) {
            int x;
            scanf ("%d", &x);
            if (x == 1) {
                number ++;
            } else {
                sum += x;
            }
        }
        printf ("Case #%d: %s\n", t, solve (number, sum + n - number - 1) ? "Alice" : "Bob");
    }
    return 0;
}
