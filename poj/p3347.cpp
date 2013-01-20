// POJ 3347, Kadj Squares
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

const int N = 60;
const double EPS = 1e-6;
const double q2 = sqrt (2.0);

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
    Segment () {}
    Segment (Point _a, Point _b): a(_a), b(_b) {}
};

int sgn (double x) {
    if (x < -EPS) return -1;
    return x < EPS ? 0 : 1;
}

double det (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

bool intersect (Segment u, Segment v) {
    int d1 = sgn (det (u.b - u.a, v.a - u.a));
    int d2 = sgn (det (u.b - u.a, v.b - u.a));
    int d3 = sgn (det (v.b - v.a, u.a - v.a));
    int d4 = sgn (det (v.b - v.a, u.b - v.a));
    return ((d1 ^ d2) == -2 && (d3 ^ d4) == -2);
}

double length[N], a[N];
Point pl[N], pr[N];
int n;

Point left_point (double x, double l) {
    return Point (x - l / q2, l / q2);
}

Point right_point (double x, double l) {
    return Point (x + l / q2, l / q2);
}

bool check (double x, int index) {
    Point p = left_point (x, length[index]);
    Segment s (Point (x, 0), p);
    if (sgn (p.x) < 0) {
        return false;
    }
    for (int i = 1; i < index; ++ i) {
        if (intersect (s, Segment (Point (a[i], 0), pl[i])) || intersect (s, Segment (Point (a[i], 0), pr[i]))) {
            return false;
        }
    }
    return true;
}

int main () {
    freopen ("input.txt", "r", stdin);
    while (scanf ("%d", &n) != EOF && n > 0) {
        for (int i = 1; i <= n; ++ i) {
            scanf ("%lf", &length[i]);
        }
        for (int i = 1; i <= n; ++ i) {
            double l = a[i - 1], r = 1e10;
            while (fabs (r - l) > EPS) {
                double mid = (l + r) / 2;
                if (check (mid, i)) {
                    r = mid;
                }
                else {
                    l = mid;
                }
            }
            a[i] = (l + r) / 2;
            pl[i] = left_point (a[i], length[i]);
            pr[i] = right_point (a[i], length[i]);
        }
        vector<int> ans;
        for (int i = 1; i <= n; ++ i) {
            double l = pl[i].x;
            double r = pr[i].x;
            double y = pl[i].y;
            for (int j = 1; j <= n; ++ j) {
                double ty = pl[j].y;
                if (i == j || sgn (y - ty) >= 0) continue;
                double temp;
                if (a[j] > a[i]) {
                    temp = pl[j].x;
                    if (temp < r) r = temp;
                }
                else {
                    temp = pr[j].x;
                    if (temp > l) l = temp;
                }
            }
            if (sgn (r - l) > 0) {
                ans.push_back (i);   
            }
        }
        for (int i = 0; i < ans.size(); ++ i) {
            printf ("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
        }
    }
    return 0;
}