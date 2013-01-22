// POJ 2826, An Easy Problem?!
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const double EPS = 1e-6;

struct Point {
    double x, y;
    Point () {}
    Point (double _x, double _y): x(_x), y(_y) {}
    Point operator - (const Point &other) {
        return Point (x - other.x, y - other.y);
    }
};

struct Segment {
    Point a, b;
    void input () {
        scanf ("%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y);
        if (a.y < b.y) {
            swap (a, b);
        }
    }
};

int sgn (double x) {
    if (x < -EPS) return -1;
    return x < EPS ? 0 : 1;
}

double det (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double dot (Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

Point cross (Segment u, Segment v) {
    double a1 = det (v.b - v.a, u.a - v.a);
    double a2 = det (v.b - v.a, u.b - v.a);
    return Point ((u.a.x * a2 - u.b.x * a1) / (a2 - a1), (u.a.y * a2 - u.b.y * a1) / (a2 - a1));
}

bool intersect (Segment u, Segment v) {
    int d1 = sgn (det (u.b - u.a, v.a - u.a));
    int d2 = sgn (det (u.b - u.a, v.b - u.a));
    int d3 = sgn (det (v.b - v.a, u.a - v.a));
    int d4 = sgn (det (v.b - v.a, u.b - v.a));
    if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return true;
    return (d1 == 0 && sgn (dot (v.a - u.a, v.a - u.b)) <= 0
        || d2 == 0 && sgn (dot (v.b - u.a, v.b - u.b)) <= 0
        || d3 == 0 && sgn (dot (u.a - v.a, u.a - v.b)) <= 0
        || d4 == 0 && sgn (dot (u.b - v.a, u.b - v.b)) <= 0);
}

bool cover (Segment u, Segment v) {
    if (u.a.y < v.a.y) {
        swap (u, v);
    }
    int d = sgn (det (u.a - u.b, v.a - v.b));
    return (d < 0 && sgn (u.a.x - v.a.x) >= 0) || (d > 0 && sgn (u.a.x - v.a.x) <= 0);
}

int main () {
    int testCount;
    scanf ("%d", &testCount);
    while (testCount --) {
        Segment u, v;
        u.input ();
        v.input ();
        if (sgn (det (u.a - u.b, v.a - v.b)) == 0 || sgn (u.a.y - u.b.y) == 0
            || sgn (u.a.y - u.b.y) == 0 || !intersect (u, v) || cover (u, v)) {
            puts ("0.00");
            continue;
        }
        Point p = cross (u, v);
        Point p2 = u.a.y < v.a.y ? u.a : v.a;
        if (u.a.y < v.a.y) {
            swap (u, v);
        }
        double x = u.a.x + (p2.y - u.a.y) * (u.b.x - u.a.x) / (u.b.y - u.a.y);
        double ans = fabs (x - p2.x) * fabs (p2.y - p.y) / 2;
        printf ("%.2f\n", ans + EPS);
    }
    return 0;
}

