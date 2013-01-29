// POJ 2074, Line of Sight
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

const double EPS = 1E-8;

int sgn (double x) {
    if (x < -EPS) {
        return -1;
    }
    return x < EPS ? 0 : 1;
}

struct Point {
    double x, y;
    Point () {}
    Point (double x0, double y0): x(x0), y(y0) {}
};

struct Segment {
    Point a, b;
    Segment () {}
    Segment (Point a0, Point b0): a(a0), b(b0) {}
    bool input () {
        double x1, x2, y;
        scanf ("%lf%lf%lf", &x1, &x2, &y);
        if (x1 > x2) {
            swap (x1, x2);
        }
        a = Point (x1, y);
        b = Point (x2, y);
        return sgn (x1 + x2 + y) != 0;
    }
    bool operator < (const Segment &other) const {
        return sgn (a.x - other.a.x) < 0 || sgn (a.x - other.a.x) == 0 && sgn (b.x - other.b.x) < 0;
    }
};

vector<Segment> segments;
Segment house, property;
int n;

void get_coefficient (Point a, Point b, double &A, double &B, double &C) {
    if (sgn (a.x - b.x) == 0) {
        A = -1;
        B = 0;
        C = a.x;
    }
    else {
        A = (a.y - b.y) / (a.x - b.x);
        B = -1;
        C = a.y - A * a.x;
    }
}

void insert (Point s1, Point s2, Point a, Point b) {
    double A, B, C;
    double y = property.a.y;
    get_coefficient (s1, a, A, B, C);
    double x1 = -(B * y + C) / A;
    get_coefficient (s2, a, A, B, C);
    double x2 = -(B * y + C) / A;
    double xl = min (x1, x2);
    get_coefficient (s1, b, A, B, C);
    x1 = -(B * y + C) / A;
    get_coefficient (s2, b, A, B, C);
    x2 = -(B * y + C) / A;
    double xr = max (x1, x2);
    segments.push_back (Segment (Point (xl, y), Point (xr, y)));
}

int main () {
    while (house.input ()) {
        property.input ();
        scanf ("%d", &n);
        segments.clear ();
        for (int i = 0; i < n; ++ i) {
            Segment s;
            s.input ();
            if (sgn (s.a.y - house.a.y) >= 0 || sgn (s.a.y - property.a.y) < 0) {
                continue;
            }
            insert (house.a, house.b, s.a, s.b);
        }
        sort (segments.begin(), segments.end());
        double ans = -1;
        double l = property.a.x, r = property.b.x, last = l;
        for (int i = 0; i < segments.size(); ++ i) {
            double x1 = segments[i].a.x;
            double x2 = segments[i].b.x;
            if (sgn (x2 - l) <= 0 || sgn (x1 - r) >= 0) {
                continue;
            }
            if (sgn (x1 - last) > 0) {
                ans = max (ans, x1 - last);
            }
            last = max (last, x2);
        }
        if (sgn (last - r) < 0) {
            ans = max (ans, r - last);
        }
        if (sgn (ans) < 0) {
            puts ("No View");
        }
        else {
            printf ("%.2f\n", ans);
        }
    }
    return 0;
}
