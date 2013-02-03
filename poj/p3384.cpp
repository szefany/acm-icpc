// POJ 3384, Feng Shui
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1E-8;
const double PI = acos (-1.0);
const int N = 105;

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
    void initise () {
        double d = sqrt (x * x + y * y);
        x /= d, y /= d;
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
    Line (Point p, Point q) {
        a = p, b = q;
        angle = atan2 (b.y - a.y, b.x - a.x);
    }
    bool operator < (const Line& other) const {
        int flag = sgn (angle - other.angle);
        if (flag) {
            return flag < 0;
        }
        return sgn (det (b - a, other.b - a)) < 0;
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
        if (head + 1 < tail) {
            convex.push (cross_point (lines[queue[head]], lines[queue[tail]]));
        }
    }
};

Point rotate (Point p, Point o, double angle) {
    Point vec = p - o;
    double c = cos (angle), s = sin (angle);
    return Point (o.x + vec.x * c - vec.y * s, o.y + vec.x * s + vec.y * c);
}

Line move (Line l, Point delta, double r) {
    Point a (l.a.x + delta.x * r, l.a.y + delta.y * r);
    Point b (l.b.x + delta.x * r, l.b.y + delta.y * r);
    return Line (a, b);
}

double dist (Point a, Point b) {
#define sqr(x) ((x) * (x))
    return sqrt (sqr (a.x - b.x) + sqr (a.y - b.y));
}

int n;
double r;
Point points[N], direction[N];
Line lines[N];

int main () {
    scanf ("%d%lf", &n, &r);
    for (int i = 0; i < n; ++ i) {
        points[i].input ();
    }
    for (int i = n - 1; i >= 0; -- i) {
        int j = i - 1 + (i == 0 ? n : 0);
        lines[i] = Line (points[i], points[j]);
        direction[i] = rotate (points[j], points[i], PI / 2) - points[i];
        direction[i].initise ();
    }
    Halfplane halfplane;
    for (int i = 0; i < n; ++ i) {
        halfplane.push (move (lines[i], direction[i], r));
    }
    Polygon convex;
    halfplane.intersect (convex);
    double d = 0;
    Point a, b;
    for (int i = 0; i < convex.size; ++ i) {
        for (int j = i; j < convex.size; ++ j) {
            double temp = dist (convex.points[i], convex.points[j]);
            if (temp > d) {
                d = temp;
                a = convex.points[i];
                b = convex.points[j];
            }
        }
    }
    printf ("%.4f %.4f %.4f %.4f\n", a.x, a.y, b.x, b.y);
    return 0;
}
