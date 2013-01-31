// POJ 3348, Cows
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1E-8;
const int N = 10005;

struct Point {
    int x, y;
    Point () {}
    Point (int x0, int y0): x (x0), y (y0) {}
    Point operator - (const Point &other) {
        return Point (x - other.x, y - other.y);
    }
    void input () {
        scanf ("%d%d", &x, &y);
    }
};

int det (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

int dot (Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

int dist (Point a, Point b) {
#define sqr(x) ((x) * (x))
    return sqrt (sqr ((double)a.x - b.x) + sqr ((double)a.y - b.y));
}

Point p0;
bool cmp (Point p, Point q) {
    int flag = det (p - p0, q - p0);
    if (flag != 0) {
        return flag > 0;
    }
    return dist (p, p0) > dist (q, p0);
}

struct Segment {
    Point a, b;
    Segment () {}
    Segment (Point a0, Point b0): a (a0), b (b0) {}
};

double get_area (Point A, Point B, Point C) {
    double a = dist (B, C), b = dist (A, C), c = dist (A, B);
    double p = (a + b + c) / 2;
    return sqrt (p * (p - a) * (p - b) * (p - c));
}

struct Polygon {
    static const int N = 10005;
    int size;
    Point points[N];
    Polygon () {size = 0;}
    void push (Point p) {
        points[size ++] = p;
    }
    void get_convex (Polygon &convex) {
        if (size < 3) {
            for (int i = 0; i < size; ++ i) {
                convex.push (points[i]);
            }
            return;
        }
        int id = 0;
        for (int i = 1; i < size; ++ i) {
            int flag = points[i].x - points[id].x;
            if (flag < 0 || flag == 0 && points[i].y < points[id].y) {
                id = i;
            }
        }
        p0 = points[id];
        swap (points[0], points[id]);
        sort (points + 1, points + size, cmp);
        int &top = convex.size;
        for (int i = 0; i < 3; ++ i) {
            convex.push (points[i]);
        }
        for (int i = 3; i <= size; ++ i) {
            int now = i % size;
            while (top > 2 && det (convex.points[top - 1] - points[now], convex.points[top - 2] - points[now]) >= 0) {
                top --;
            }
            convex.push (points[now]);
        }
        top --;
    }
    double convex_area () {
        double area = 0;
        for (int i = 0; i < size; ++ i) {
            area += det (points[i], points[(i + 1) % size]);
        }
        return fabs (area) / 2;
    }
};

int n;
Point points[N];

int main () {
    scanf ("%d", &n);
    Polygon poly;
    for (int i = 0; i < n; ++ i) {
        points[i].input ();
        poly.push (points[i]);
    }
    Polygon convex;
    poly.get_convex (convex);
    double area = convex.convex_area ();
    printf ("%d\n", (int)(area / 50 + EPS));
    return 0;
}
