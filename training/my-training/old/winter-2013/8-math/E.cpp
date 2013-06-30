// Codeforces Beta Round #93 (Div. 2 Only)
// Problem C, Hot Bath
#include <cstdio>

const double EPS = 1E-8;
const double INF = 1E10;

double answer;
int y1, y2, t1, t2, x1, x2, t0;

int sgn (double x) {
    if (x < -EPS) {
        return -1;
    }
    return x < EPS ? 0 : 1;
}

void update (long long x, long long y) {
    if (y > x2 || x * t1 + y * t2 < (x + y) * t0) {
        return;
    }
    double temp = ((double)x * t1 + (double)y * t2) / (x + y) - t0;
    int flag = sgn (temp - answer);
    if (flag < 0 || flag == 0 && x + y > y1 + y2) {
        answer = temp;
        y1 = x;
        y2 = y;
    } 
}

int main () {
    answer = INF, y1 = 0, y2 = 0;
    scanf ("%d%d%d%d%d", &t1, &t2, &x1, &x2, &t0);
    for (int x = 0; x <= x1; ++ x) {
        int y = (x == 0 || t2 == t0) ? x2 : ((double)t0 - t1) * x / ((double)t2 - t0);
        update (x, y);
        update (x, y + 1);
    }
    printf ("%d %d\n", y1, y2);
    return 0;
}