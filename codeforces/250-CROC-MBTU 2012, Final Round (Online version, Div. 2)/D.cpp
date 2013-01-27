// CROC-MBTU 2012, Final Round (Online version, Div. 2)
// Problem D, Building Bridge
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 100005;

int x[2][N], s[N], a, b, n, m;

struct Data {
    int x, rank;
} data[N];

double dis (int x1, int y1, int x2, int y2) {
#define sqr(x) (x) * (x)
    return sqrt (sqr ((double)x1 - x2) + sqr ((double)y1 - y2));
}

int find_max (int key) {
    int l = 1, r = n;
    while (l < r) {
        int mid = l + r >> 1;
        if (data[mid].x > key) {
            r = mid;
        }
        else l = mid + 1;
    }
    return l;
}

double calc (int x, int y) {
    double k = (double)y / x;
    return k * a;
}

bool cmp (Data p, Data q) {
    return p.x < q.x;
}

int main () {
    scanf ("%d%d%d%d", &n, &m, &a, &b);
    for (int i = 1; i <= n; ++ i) {
        scanf ("%d", &x[0][i]);
    }
    for (int j = 1; j <= m; ++ j) {
        scanf ("%d", &x[1][j]);
    }
    for (int i = 1; i <= m; ++ i) {
        scanf ("%d", &s[i]);
    }
    for (int i = 1; i <= n; ++ i) {
        data[i].x = x[0][i];
        data[i].rank = i;
    }
    sort (data + 1, data + n + 1, cmp);
    double ans = 1e20;
    int l, r;
    for (int i = 1; i <= m; ++ i) {
        double y = calc (b, x[1][i]);
        int y1 = (int) y;
        int iter = find_max (y1); // >
        if (iter <= n) {
            double d = dis (0, 0, a, data[iter].x) + dis (a, data[iter].x, b, x[1][i]) + s[i];
            if (d < ans) {
                ans = d;
                l = data[iter].rank;
                r = i;
            }
        }
        iter --;
        if (iter != 0) {
            double d = dis (0, 0, a, data[iter].x) + dis (a, data[iter].x, b, x[1][i]) + s[i];
            if (d < ans) {
                ans = d;
                l = data[iter].rank;
                r = i;
            }
        }
    }
    printf ("%d %d\n", l, r);
    return 0;
}
