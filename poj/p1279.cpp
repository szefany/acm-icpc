// POJ 1279, Art Gallery
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 1500;
const double EPS = 1E-8;

struct Point {
    double x, y;
    Point () {}
    Point (double x0, double y0): x (x0), y (y0) {}
    Point operator - (const Point &other) const {
        return Point (x - other.x, y - other.y);
    }
    Point operator + (const Point &other) const {
        return Point (x + other.x, y + other.y);
    }
    void input () {
        scanf ("%lf%lf", &x, &y);
    }
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

double det (Point a, Point b, Point c) {
    return det (b - a, c - a);
}

double dot (Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

struct Line {
    Point a, b;
    double angle;
    Line () {}
    Line (Point start, Point end) {
        a = start, b = end;
        angle = atan2 (b.y - a.y, b.x - a.x);
    }
    bool operator < (const Line &other) const {
        int flag = sgn (angle - other.angle);
        if (flag) {
            return flag < 0;
        }
        return det (b - a, other.b - a) < 0;
    }
};

Point cross_point (Line u, Line v) {
    double a1 = det (v.b - v.a, u.a - v.a);
    double a2 = det (v.b - v.a, u.b - v.a);
    return Point ((u.a.x * a2 - u.b.x * a1) / (a2 - a1), (u.a.y * a2 - u.b.y * a1) / (a2 - a1));
}

struct Polygon {
    int size;
    Point points[N];
    Polygon () {size = 0;}
    void push (Point p) {
        points[size ++] = p;
    }
    double area () {
        double result = 0;
        for (int i = 0; i < size; ++ i) {
            result += det (points[i], points[(i + 1) % size]);
        }
        return fabs (result) / 2;
    }
};

struct Halfplane {
    int size;
    Line lines[N];
    Halfplane () {size = 0;}
    void push (Line l) {
        lines[size ++] = l;
    }
    void intersect (Polygon& convex) {
        sort (lines, lines + size);
        int counter = 1;
        for (int i = 1; i < size; ++ i) {
            if (sgn (lines[i].angle - lines[i - 1].angle)) {
                lines[counter ++] = lines[i];
            }
        }
        size = counter;
        int* queue = new int [size + 1], head = 0, tail = 1;
        queue[0] = 0, queue[1] = 1;
        for (int i = 2; i < size; ++ i) {
            while (head < tail && sgn (det (lines[i].a, lines[i].b, \
                cross_point (lines[queue[tail]], lines[queue[tail - 1]]))) < 0) {
                tail --;
            }
            while (head < tail && sgn (det (lines[i].a, lines[i].b, \
                cross_point (lines[queue[head]], lines[queue[head + 1]]))) < 0) {
                head ++;
            }
            queue[++ tail] = i;
        }
        while (head < tail && sgn (det (lines[queue[head]].a, lines[queue[head]].b, \
            cross_point (lines[queue[tail]], lines[queue[tail - 1]]))) < 0) {
            tail --;
        }
        while (head < tail && sgn (det (lines[queue[tail]].a, lines[queue[tail]].b, \
            cross_point (lines[queue[head]], lines[queue[head + 1]]))) < 0) {
            head ++;
        }
        for (int i = head; i < tail; ++ i) {
            convex.push (cross_point (lines[queue[i]], lines[queue[i + 1]]));
        }
        convex.push (cross_point (lines[queue[head]], lines[queue[tail]]));
    }
};

Point points[N];
int n;

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        scanf ("%d", &n);
        for (int i = 0; i < n; ++ i) {
            points[i].input ();
        }
        Halfplane halfplane;
        for (int i = n - 1; i >= 0; -- i) {
            int j = i - 1 + (i == 0 ? n : 0);
            halfplane.push (Line (points[i], points[j]));
        }
        Polygon convex;
        halfplane.intersect (convex);
        printf ("%.2f\n", convex.area());
    }
    return 0;
}
