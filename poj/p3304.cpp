// POJ 3304, Segments
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int N = 105;
const double EPS = 1e-8;

struct Point {
    double x, y;
};

struct Segment {
    Point a, b;
    void input () {
        scanf ("%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y);
    }
} segments[N];

int n;

int sgn (double x) {
    if (x < -EPS) return -1;
    return x < EPS ? 0 : 1;
}

double det (Point a, Point b, Point c) {
    double x1 = b.x - a.x, y1 = b.y - a.y;
    double x2 = c.x - a.x, y2 = c.y - a.y;
    return x1 * y2 - x2 * y1;
}

#define sqr(x) (x) * (x)
double dist (Point a, Point b) {
    return sqrt (sqr (a.x - b.x) + sqr (a.y - b.y));
}

bool check (Point a, Point b) {
    if (dist (a, b) < EPS) {
        return false;
    }
    for (int i = 1; i <= n; ++ i) {
        if (sgn (det (a, b, segments[i].a) * det (a, b, segments[i].b)) > 0) {
            return false;
        }
    }
    return true;
}

int main () {
    freopen ("input.txt", "r", stdin);
    int testCount;
    scanf ("%d", &testCount);
    while (testCount --) {
        scanf ("%d", &n);
        for (int i = 1; i <= n; ++ i) {
            segments[i].input ();
        }
        bool flag = false;
        for (int i = 1; i <= n && !flag; ++ i) {
            flag |= check (segments[i].a, segments[i].b);
            for (int j = i + 1; j <= n && !flag; ++ j) {
                flag |= check (segments[i].a, segments[j].a) || check (segments[i].a, segments[j].b) || check (segments[i].b, segments[j].a) \
                || check (segments[i].b, segments[j].b);
            }
        }
        puts (flag ? "Yes!" : "No!");
    }
    return 0;
}