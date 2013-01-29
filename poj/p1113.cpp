// POJ 1113, Wall
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;

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

double dist (Point a, Point b) {
#define sqr(x) ((x) * (x))
    return sqrt (sqr (a.x - b.x) + sqr (a.y - b.y));
}

Point p0;
bool cmp (Point p, Point q) {
    int flag = sgn (det (p - p0, q - p0));
    if (flag != 0) {
        return flag > 0;
    }
    return dist (p, p0) > dist (q, p0);
}

struct Polygon {
    static const int N = 1005;
    Point points[N];
    int size;
    Polygon () {size = 0;}
    void push (Point p) {
        points[size ++] = p;
    }
    void get_convex (Polygon &convex) {
        int pivot = 0;
        for (int i = 1; i < size; ++ i) {
            int flag = sgn (points[i].x - points[pivot].x);
            if (flag < 0 || flag == 0 && points[i].y < points[pivot].y) {
                pivot = i;
            }
        }
        swap (points[pivot], points[0]);
        p0 = points[0];
        sort (points + 1, points + size, cmp);
        for (int i = 0; i < 3; ++ i) {
            convex.push (points[i]);
        }
        int &top = convex.size;
        for (int i = 3; i <= size; ++ i) {
            int k = i % size;
            while (top > 2 && sgn (det (convex.points[top - 1] - points[k], convex.points[top - 2] - points[k])) > 0) {
                top --;
            }
            convex.push (points[k]);
        }
    }
};

const double PI = acos (-1.0);
int n, l;

int main () {
    scanf ("%d%d", &n, &l);
    Polygon poly;
    for (int i = 1; i <= n; ++ i) {
        Point p;
        p.input ();
        poly.push (p);
    }
    Polygon convex;
    poly.get_convex (convex);
    double ans = 2 * PI * l;
    int size = convex.size;
    for (int i = 0; i < size; ++ i) {
        ans += dist (convex.points[i], convex.points[(i + 1) % size]);
    }
    printf ("%.0f\n", ans);
    return 0;
}
