// POJ 1269, Intersecting Lines
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int N = 20;
const double EPS = 1e-6;

struct Point {
    double x, y;
    Point () {}
    Point (double _x, double _y): x(_x), y(_y) {}
    void input () {
        scanf ("%lf%lf", &x, &y);
    }
    Point operator - (const Point &other) {
        return Point (x - other.x, y - other.y);
    }
};

double det (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

int sgn (double x) {
    if (x < -EPS) return -1;
    return x < EPS ? 0 : 1;
}

int main () {
    freopen ("input.txt", "r", stdin);
    puts ("INTERSECTING LINES OUTPUT");
    int n;
    scanf ("%d", &n);
    while (n --) {
        Point a, b, c, d;
        a.input (), b.input (), c.input (), d.input ();
        if (sgn (det (a - c, b - c)) == 0 && sgn (det (a - d, b - d)) == 0) {
            puts ("LINE");
        }
        else if (sgn (det (c - d, a - b)) == 0) {
            puts ("NONE");
        }
        else {
            double a1 = det (d - c, a - c);
            double a2 = det (d - c, b - c);
            double x = (a.x * a2 - b.x * a1) / (a2 - a1);
            double y = (a.y * a2 - b.y * a1) / (a2 - a1);
            printf ("POINT %.2f %.2f\n", x, y);
        }
    }
    puts ("END OF OUTPUT");
    return 0;
}