// POJ 2540, Hotter Colder
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 200;
const double EPS = 1E-8;
const double PI = acos (-1.0);

int sgn (double x) {
    if (x < -EPS) {
        return -1;
    }
    return x < EPS ? 0 : 1;
}

struct Point {
    double x, y;
    Point () {}
    Point (double x0, double y0): x (x0), y (y0) {}
    Point operator - (const Point& other) const {
        return Point (x - other.x, y - other.y);
    }
    bool operator < (const Point& other) const {
        int flag = sgn (x - other.x);
        if (flag) {
            return flag < 0;
        }
        return y < other.y;
    }
};

double det (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double det (Point a, Point b, Point c) {
    return det (b - a, c - a);
}

struct Line {
    Point a, b;
    double angle;
    Line () {}
    Line (Point p, Point q) {
        a = p, b = q;
        angle = atan2 (b.y - a.y, b.x - a.x);
    }
    Line (Point p, Point q, bool is_counter_clockwise) {
        if (!is_counter_clockwise) {
            swap (p, q);
        }
        a = p, b = q;
        angle = atan2 (b.y - a.y, b.x - a.x);
    }
    bool operator < (const Line& other) const {
        int flag = sgn (angle - other.angle);
        if (flag) {
            return flag < 0;
        }
        return sgn (det (b - a, other.a - a)) < 0;
    }
};

Point cross_point (Line u, Line v) {
    double a1 = det (v.b - v.a, u.a - v.a);
    double a2 = det (v.b - v.a, u.b - v.a);
    return Point ((u.a.x * a2 - u.b.x * a1) / (a2 - a1), (u.a.y * a2 - u.b.y * a1) / (a2 - a1));
}

struct Halfplane {
    static const int SIZE = N;
    int size;
    Line lines[SIZE];
    Halfplane () {size = 0;}
    void push (Line l) {
        lines[size ++] = l;
    }
    bool push (double A, double B, double C) {
        // Ax + By + C < 0
        if (sgn (A) == 0 && sgn (B) == 0 && sgn (C) >= 0) {
            return false;
        }
        if (sgn (B)) {
            double k = -A / B, b = -C / B;
            lines[size ++] = Line (Point (0, k * 0 + b), Point (1E5, k * 1E5 + b), sgn (B) < 0);
        }
        else {
            double x0 = -C / A;
            Point p (x0, 0), q (x0, 1E5);
            if (sgn (A) < 0) {
                swap (p, q);
            }
            lines[size ++] = Line (p, q, true);
        }
        return true;
    }
    double intersect () {
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
        if (head + 1 >= tail) {
            return 0;
        }
        double area = 0;
        Point last = cross_point (lines[queue[head]], lines[queue[head + 1]]);
        for (int i = head + 1; i <= tail; ++ i) {
            int j = i == tail ? head : i + 1;
            Point now = cross_point (lines[queue[i]], lines[queue[j]]);
            area += det (last, now);
            last = now;
        }
        area += det (last, cross_point (lines[queue[head]], lines[queue[head + 1]]));
        return fabs (area) / 2;
    }
};

Point rotate (Point p, Point o, double angle) {
    Point vec = p - o;
    double c = cos (angle), s = sin (angle);
    return Point (o.x + vec.x * c - vec.y * s, o.y + vec.x * s + vec.y * c);
}

int main () {
    Halfplane halfplane;
    halfplane.push (Line (Point (0, 0), Point (10, 0), true));
    halfplane.push (Line (Point (10, 0), Point (10, 10), true));
    halfplane.push (Line (Point (10, 10), Point (0, 10), true));
    halfplane.push (Line (Point (0, 10), Point (0, 0), true));
    Point last (0, 0);
    double x, y;
    bool flag = false;
    while (scanf ("%lf", &x) != EOF) {
        scanf ("%lf", &y);
        Point now (x, y);
        char buffer[7];
        scanf ("%s", buffer);
        if (flag || sgn (x - last.x) == 0 && sgn (y - last.y) == 0 && *buffer != 'S') {
            puts ("0.00");
            continue;
        }
        Point p ((last.x + x) / 2, (last.y + y) / 2);
        Point q = rotate (last, p, PI / 2);
        if (*buffer == 'S') {
            halfplane.push (Line (p, q));
            halfplane.push (Line (q, p));
        }
        else if (*buffer == 'H') {
            halfplane.push (Line (p, q, sgn (det (p, q, now)) > 0));
        }
        else {
            halfplane.push (Line (p, q, sgn (det (p, q, now)) < 0));
        }
        double area = halfplane.intersect ();
        printf ("%.2f\n", area);
        if (sgn (area) == 0) {
            flag = true;
        }
        last = now;
    }
    return 0;
}
