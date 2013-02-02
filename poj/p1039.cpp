// POJ 1039, Pipe
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 50;
const double EPS = 1e-8;
const double INF = 1e10;

struct Point {
    Point () {}
    Point (double _x, double _y): x(_x), y(_y) {}
    double x, y;
    void input () {
        scanf ("%lf%lf", &x, &y);
    }
    Point operator - (const Point &other) {
        return Point (x - other.x, y - other.y);
    }
};

struct Line {
    Line () {}
    Line (Point a0, Point b0): a(a0), b(b0) {}
    Point a, b;
};

struct Segment {
    Segment () {}
    Segment (Point a0, Point b0): a(a0), b(b0) {}
    Point a, b;
};

double det (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double dot (Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

int sgn (double x) {
    if (x < -EPS) return -1;
    return x < EPS ? 0 : 1;
}

bool strict_cross (Segment u, Line v) {
    int d1 = sgn (det (v.b - v.a, u.a - v.a));
    int d2 = sgn (det (v.b - v.a, u.b - v.a));
    return ((d1 ^ d2) == -2);
}

bool cross (Segment u, Line v) {
    int d1 = sgn (det (v.b - v.a, u.a - v.a));
    int d2 = sgn (det (v.b - v.a, u.b - v.a));
    if ((d1 ^ d2) == -2) return true;
    return (d1 == 0 || d2 == 0);
}

bool strict_cross (Segment u, Segment v) {
    int d1 = sgn (det (u.b - u.a, v.a - u.a));
    int d2 = sgn (det (u.b - u.a, v.b - u.a));
    int d3 = sgn (det (v.b - v.a, u.a - v.a));
    int d4 = sgn (det (v.b - v.a, u.b - v.a));
    return (d1 ^ d2) == -2 && (d3 ^ d4) == -2;
}

bool cross (Segment u, Segment v) {
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

Point cross_point (Segment u, Line v) {
    double a1 = det (v.b - v.a, u.a - v.a);
    double a2 = det (v.b - v.a, u.b - v.a);
    return Point ((u.a.x * a2 - u.b.x * a1) / (a2 - a1), (u.a.y * a2 - u.b.y * a1) / (a2 - a1));
}

int n;
Point points[N][2];

double check (Point a, Point b) {
    Line l (a, b);
    for (int i = 1; i <= n; ++ i) {
        if (!cross (Segment (points[i][0], points[i][1]), l)) {
            return -INF;
        }
        if (i < n) {
            for (int j = 0; j < 2; ++ j) {
                Segment s = Segment (points[i][j], points[i + 1][j]);
                if (strict_cross (s, l)) {
                    Point p = cross_point (s, l);
                    return p.x;
                }
            }
        }
    }
    return points[n][0].x;
}

int main () {
    while (scanf ("%d", &n) != EOF && n > 0) {
        for (int i = 1; i <= n; ++ i) {
            points[i][0].input ();
            points[i][1] = Point (points[i][0].x, points[i][0].y - 1);
        }
        double ans = points[1][0].x;
        for (int i = 1; i <= n; ++ i) {
            for (int j = i + 1; j <= n; ++ j) {
                for (int k = 0; k < 2; ++ k) {
                    double x = check (points[i][k], points[j][k ^ 1]);
                    if (x > ans) {
                        ans = x;
                    }
                }
            }
        }
        if (sgn (ans - points[n][0].x) == 0) {
            puts ("Through all the pipe.");
        }
        else {
            printf ("%.2f\n", ans);
        }
    }
    return 0;
}

