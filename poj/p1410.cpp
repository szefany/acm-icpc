// POJ 1410, Intersection
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const double EPS = 1E-6;

struct Point {
    Point () {}
    Point (double _x, double _y): x(_x), y(_y) {}
    double x, y;
    Point operator - (const Point &other) {
        return Point (x - other.x, y - other.y);
    }
};

struct Segment {
    Segment () {}
    Segment (Point _a, Point _b): a(_a), b(_b) {}
    Point a, b;
    void input () {
        scanf ("%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y);
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

bool in_rectangle (Point a, double x1, double y1, double x2, double y2) {
    double min_x = min (x1, x2);
    double max_x = max (x1, x2);
    double min_y = min (y1, y2);
    double max_y = max (y1, y2);
    double x = a.x, y = a.y;
    return sgn (x - min_x) >= 0 && sgn (x - max_x) <= 0 && sgn (y - min_y) >= 0 && sgn (y - max_y) <= 0;
}

int main () {
    freopen ("input.txt", "r", stdin);
    int testCount;
    scanf ("%d", &testCount);
    while (testCount --) {
        Segment s;
        s.input ();
        double x1, y1, x2, y2;
        scanf ("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        if (intersect (s, Segment (Point (x1, y1), Point (x1, y2))) || intersect (s, Segment (Point (x1, y1), Point (x2, y1)))
            || intersect (s, Segment (Point (x2, y2), Point (x1, y2))) || intersect (s, Segment (Point (x2, y2), Point (x2, y1)))
            || (in_rectangle (s.a, x1, y1, x2, y2) && in_rectangle (s.b, x1, y1, x2, y2))) {
            puts ("T");
        }
        else puts ("F");
    }
    return 0;
}
