// POJ 3130, How I Mathematician Wonder What You Are!
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1E-8;

struct Point {
    double x, y;
    Point () {}
    Point (double x0, double y0): x (x0), y (y0) {}
    Point operator - (const Point &other) const {
        return Point (x - other.x, y - other.y);
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

struct Line {
    Point a, b;
    double angle;
    Line () {}
    Line (Point p, Point q) {
        a = p, b = q;
        angle = atan2 (b.y - a.y, b.x - a.x);
    }
    bool operator < (const Line &other) const {
        int flag = sgn (angle - other.angle);
        if (flag) {
            return flag < 0;
        }
        return sgn (det (other.a - a, b - a)) > 0;
    }
};

Point cross_point (Line u, Line v) {
    double a1 = det (v.b - v.a, u.a - v.a);
    double a2 = det (v.b - v.a, u.b - v.a);
    return Point ((u.a.x * a2 - u.b.x * a1) / (a2 - a1), (u.a.y * a2 - u.b.y * a1) / (a2 - a1)); 
}

struct Halfplane {
    static const int SIZE = 60;
    int size;
    Line lines[SIZE];

    Halfplane () {size = 0;}
    void push (Point a, Point b) {
        lines[size ++] = Line (a, b);
    }
    bool intersect () {
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
        return head + 1 < tail;
    }
};

const int N = 60;

Point points[N];
int n;

int main () {
    while (scanf ("%d", &n) != EOF && n > 0) {
        for (int i = 0; i < n; ++ i) {
            points[i].input ();
        }
        Halfplane halfplane;
        for (int i = 0; i < n; ++ i) {
            halfplane.push (points[i], points[(i + 1) % n]);
        }
        puts (halfplane.intersect () ? "1" : "0");
    }
    return 0;
}
