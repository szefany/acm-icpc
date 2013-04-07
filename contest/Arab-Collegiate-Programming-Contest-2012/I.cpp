#include <cstdio>
#include <cstring>

const int N = 100 + 5;
const int D[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

int g[N][N], number[N];

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        int n, m;
        scanf ("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                scanf ("%d", &g[i][j]);
            }
        }
        memset (number, 0, sizeof (number));
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                int key = g[i][j];
                if (key == -1) {
                    continue;
                }
                for (int k = 0; k < 8; ++ k) {
                    int x = i + D[k][0], y = j + D[k][1];
                    if (x >= 0 && x < n && y >= 0 && y < m && g[x][y] == key) {
                        number[key] = 1;
                        break;
                    } 
                }
            }
        }
        int answer = 0;
        for (int i = 0; i <= 100; ++ i) {
            answer += number[i];
        }
        printf ("%d\n", answer);
    }
    return 0;
}
