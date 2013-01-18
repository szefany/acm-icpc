// POJ 2318, toys
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 10005;
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
int ans[N];

double det (Point a, Point b, Point c) {
    double x1 = b.x - a.x, y1 = b.y - a.y;
    double x2 = c.x - a.x, y2 = c.y - a.y;
    return x1 * y2 - x2 * y1;
}

int main () {
    freopen ("input.txt", "r", stdin);
    double lx, rx, uy, dy;
    while (scanf ("%d", &n) != EOF && n) {
        scanf ("%d%lf%lf%lf%lf", &m, &lx, &uy, &rx, &dy);
        memset (ans, 0, sizeof (ans));
        for (int i = 0; i < n; ++ i) {
            double x1, x2;
            scanf ("%lf%lf", &x1, &x2);
            points[i * 2] = Point (x1, uy);
            points[i * 2 + 1] = Point (x2, dy);
        }
        points[n * 2] = Point (rx, uy);
        points[n * 2 + 1] = Point (rx, dy);
        n ++;
        while (m --) {
            Point p;
            p.input ();
            for (int i = 0; i < n; ++ i) {
                if (det (p, points[i * 2], points[i * 2 + 1]) < EPS) {
                    ans[i] ++;
                    break;
                }
            }
        }
        for (int i = 0; i < n; ++ i) {
            printf ("%d: %d\n", i, ans[i]);
        }
        puts ("");
    }
    return 0;
}
