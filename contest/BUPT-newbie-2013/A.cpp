// Gobang, BUPT Newbie 2013
#include <cstdio>
#include <cstring>
#include <vector>

#define foreach(i, v) for (__typeof ((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 100;
const int D[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

char board[N][N];
int covered[N][N];
int n, m;

int abs (int x) {
    return x < 0 ? -x : x;
}

int count (char key) {
    int result = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (board[i][j] == key) {
                for (int k = 0; k < 4; ++ k) {
                    int temp = 0;
                    for (int x = i, y = j; x < n && y < m; x += D[k][0], y += D[k][1]) {
                        if (board[x][y] == key) {
                            temp ++;
                        } else {
                            break;
                        }
                    }
                    result = std::max (result, temp);
                }
            }
        }
    }
    return result;
}

int main () {
    while (scanf ("%d%d", &n, &m) != EOF) {
        for (int i = 0; i < n; ++ i) {
            scanf ("%s", board[i]);
        }
        int number[2] = {0};
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                if (board[i][j] != '.') {
                    number[board[i][j] - '1'] ++;
                }
            }
        }
        if (abs (number[0] - number[1]) > 1) {
            puts ("fault");
            continue;
        }
        int win = -1;
        if (number[0] != number[1]) {
            win = number[0] > number[1] ? 0 : 1;
        }
        int counter[2];
        for (int i = 0; i < 2; ++ i) {
            counter[i] = count ((char)(i + '1'));
        }
        if (counter[0] >= 5 && counter[1] >= 5 || win == 1 && counter[0] >= 5 || win == 0 && counter[1] >= 5 || \
            counter[0] >= 10 || counter[1] >= 10) {
            puts ("fault");
        } else if (counter[0] < 5 && counter[1] < 5) {
            puts ("other");
        } else {
            puts (counter[0] >= 5 ? "white" : "black");
        }
    }
    return 0;
}
