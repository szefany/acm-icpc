// POJ 1584, A Round Peg in a Ground Hole
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1E-8;

struct Point {
    double x, y;
    Point () {}
    Point (double x0, double y0): x(x0), y(y0) {}
    Point operator - (const Point &other) {
        return Point (x - other.x, y - other.y);
    }
    void input () {
        scanf ("%lf%lf", &x, &y);
    }
};

struct Line {
    Point a, b;
    Line () {}
    Line (Point a0, Point b0): a(a0), b(b0) {}
};

int sgn (double x) {
    if (x < -EPS) {
        return -1;
    }
    return x < EPS ? 0 : 1;
}

double det (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

void get_coefficient (Line u, double &A, double &B, double &C) {
    if (sgn (u.a.x - u.b.x) == 0) {
        A = -1;
        B = 0;
        C = u.a.x;
    }
    else {
        A = (u.a.y - u.b.y) / (u.a.x - u.b.x);
        B = -1;
        C = u.a.y - A * u.a.x;
    }
}

double get_distance (Point p, Line u) {
    double A, B, C;
    get_coefficient (u, A, B, C);
    return fabs (A * p.x + B * p.y + C) / sqrt (A * A + B * B);
}

double get_distance (Point a, Point b) {
#define sqr(x) ((x) * (x))
    return sqrt (sqr (a.x - b.x) + sqr (a.y - b.y));
}

struct Polygon {
    static const int N = 200;
    Point points[N];
    int size;
    Polygon () {size = 0;}
    void push (Point p) {
        points[size ++] = p;
    }
    bool is_convex () {
        int counter[3] = {0};
        for (int i = 0; i < size; ++ i) {
            int j = (i + 1) % size;
            int k = (j + 1) % size;
            counter[1 + sgn (det (points[j] - points[i], points[k] - points[i]))] = 1;
            if (counter[0] && counter[2]) {
                return false;
            }
        }
        return true;
    }
};

bool in_polygon (Point p, const Polygon &poly) {
    // Judge whether it is inside the polygon
    int counter[2] = {0};
    int size = poly.size;
    for (int i = 0; i < size; ++ i) {
        Point last = poly.points[i];
        Point now = poly.points[(i + 1) % size];
        if (sgn (last.y - p.y) < 0 && sgn (now.y - p.y) >= 0 \
            || sgn (now.y - p.y) < 0 && sgn (last.y - p.y) >= 0) {
            double x = (p.y - last.y) * (now.x - last.x) / (now.y - last.y) + last.x;
            if (sgn (x - p.x) < 0) {
                counter[0] ++;
            }
            else {
                counter[1] ++;
            }
        }
    }
    return (counter[0] & 1) && (counter[1] & 1);
}

int n;
double r;

int main () {
    freopen ("input.txt", "r", stdin);
    while (scanf ("%d", &n) != EOF && n >= 3) {
        scanf ("%lf", &r);
        Point centre;
        centre.input ();
        Polygon poly;
        for (int i = 0; i < n; ++ i) {
            Point p;
            p.input ();
            poly.push (p);
        }
        if (!poly.is_convex ()) {
            puts ("HOLE IS ILL-FORMED");
            continue;
        }
        bool flag = true;
        if (!in_polygon (centre, poly)) {
            flag = false;
        }
        else {
            int size = poly.size;
            for (int i = 0; i < size; ++ i) {
                if (sgn (get_distance (centre, Line (poly.points[i], poly.points[(i + 1) % size])) - r) < 0) {
                    flag = false;
                    break;
                }
            }
        }
        puts (flag ? "PEG WILL FIT" : "PEG WILL NOT FIT");
    }
    return 0;
}
