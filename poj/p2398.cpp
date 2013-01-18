// POJ 2398, toy storage
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 2005;
const double EPS = 1E-6;

struct Point {
    double x, y;
    Point () {}
    Point (double _x, double _y): x(_x), y(_y) {}
    void input () {
        scanf ("%lf%lf", &x, &y);
    }
} points[N];

int n, m;
int ans[N], number[N], rank[N];

int sgn (double x) {
    if (x < -EPS) return -1;
    return x < EPS ? 0 : 1;
}

double det (Point a, Point b, Point c) {
    double x1 = b.x - a.x, y1 = b.y - a.y;
    double x2 = c.x - a.x, y2 = c.y - a.y;
    return x1 * y2 - x2 * y1;
}

bool cmp (int a, int b) {
    return sgn (points[a * 2].x - points[b * 2].x) == -1 || (sgn (points[a * 2].x - points[b * 2].x) == 0 && sgn (points[a * 2 + 1].x - points[b * 2 + 1].x) == -1);
}

int main () {
    freopen ("input.txt", "r", stdin);
    double lx, rx, uy, dy;
    while (scanf ("%d", &n) != EOF && n) {
        scanf ("%d%lf%lf%lf%lf", &m, &lx, &uy, &rx, &dy);
        memset (ans, 0, sizeof (ans));
        memset (number, 0, sizeof (number));
        for (int i = 0; i < n; ++ i) {
            double x1, x2;
            scanf ("%lf%lf", &x1, &x2);
            points[i * 2] = Point (x1, uy);
            points[i * 2 + 1] = Point (x2, dy);
        }
        points[n * 2] = Point (rx, uy);
        points[n * 2 + 1] = Point (rx, dy);
        n ++;
        for (int i = 0; i < n; ++ i) {
            rank[i] = i;
        }
        sort (rank, rank + n, cmp);
        while (m --) {
            Point p;
            p.input ();
            for (int i = 0; i < n; ++ i) {
                int iter = rank[i];
                if (det (p, points[iter * 2], points[iter * 2 + 1]) < EPS) {
                    number[iter] ++;
                    break;
                }
            }
        }
        for (int i = 0; i < n; ++ i) {
            ans[number[i]] ++;
        }
        puts ("Box");
        for (int i = 1; i <= n; ++ i) {
            if (ans[i]) {
                printf ("%d: %d\n", i, ans[i]);
            }
        }
    }
    return 0;
}
