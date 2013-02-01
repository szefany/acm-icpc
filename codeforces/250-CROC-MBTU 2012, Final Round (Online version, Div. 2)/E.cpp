// CROC-MBTU 2012, Final Round (Online version, Div. 2)
// Problem E, Mad Joe
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 1000000 + 5;
const int X = 100 + 5;
const int Y = 10000 + 5;
const int direction[2][2] = {{0, -1}, {0, 1}};

struct Pair {
    int x, y;
    Pair () {}
    Pair (int x0, int y0): x (x0), y (y0) {}
};

char map[X][Y];
int n, m;

#define id(x, y) ((x) * m + (y) + 1)

bool invalid (int x, int y) {
    return y < 0 || y >= m || map[x][y] == '#';
}

int main () {
    scanf ("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf ("%s", map[i]);
    }
    long long steps = 0;
    Pair from (0, -1);
    for (int x = 0, y = 0, d = 1; x < n - 1; ) {
        if (map[x][y] == '#') {
            steps = -1;
            break;
        }
        if (map[x + 1][y] == '.') {
            x ++;
            from = Pair (x + direction[d ^ 1][0], y + direction[d ^ 1][1]);
            steps ++;
        }
        else {
            int dx = x + direction[d][0];
            int dy = y + direction[d][1];
            if (dy >= 0 && dy < m && map[dx][dy] != '#') {
                if (map[dx][dy] == '.') {
                    x = dx;
                    y = dy;
                    steps ++;
                }
                else {
                    map[dx][dy] = '.';
                    if (invalid (from.x, from.y) || map[from.x][from.y] == '+') {
                        steps += 2 * abs (y - from.y) + 1;
                        x = dx;
                        y = dy;
                        if (!invalid (from.x, from.y)) {
                            map[from.x][from.y] = '.';
                        }
                    }
                    else {
                        steps += 1 + abs (y - from.y);
                        x = from.x;
                        y = from.y;
                        d ^= 1;
                        from = Pair (dx, dy);
                    }
                }
            }
            else {
                if (invalid (from.x, from.y)) {
                    steps = -1;
                    break;
                }
                if (map[from.x][from.y] == '.') {
                    steps += 1 + abs (y - from.y);
                    y = from.y;
                    d ^= 1;
                    from = Pair (dx, dy);
                }
                else {
                    steps += abs (y - from.y);
                    d ^= 1;
                    y = from.y - direction[d][1];
                    from = Pair (dx, dy);
                }
            }
        }
    }
    if (steps == -1) {
        puts ("Never");
    }
    else {
        cout << steps << '\n';
    }
    return 0;
}
