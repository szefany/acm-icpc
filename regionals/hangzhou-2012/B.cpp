#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <iostream>

const double PI = acos(-1);
const double EPS = 1E-8;

int sgn(double x) {
    if (x < -EPS) {
        return -1;
    }
    return x < EPS ? 0 : 1;
}

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    Point operator - (const Point &other) {
        return Point (x - other.x, y - other.y);
    }
    Point operator + (const Point &other) {
        return Point (x + other.x, y + other.y);
    }
    Point operator * (double b) {
        return Point(x * b, y * b);
    }
    double len() {
        return hypot(x, y);
    }
    double len2() {
        return x * x + y * y;
    }
    Point trunc(double r) {
        double l = len();
        if (sgn(l) == 0) {
            return *this;
        }
        r /= l;
        return Point(x * r, y * r);
    }
};

double det(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

struct Line {
    static const double DELTA = 1E10;
    Point a, b;
    Line() {}
    Line(Point a, Point b): a(a), b(b) {}
    Line(double x, double y, double alpha) {
        double dy = DELTA * tan(alpha);
        a = Point(x + DELTA, y + dy);
        b = Point(x - DELTA, y - dy);
    }
    Point lineprog(Point p) {
        return a + ((b - a) * (dot(b - a, p - a) / (b - a).len2()));
    }
};

struct Segment {
    Point a, b;
    Segment() {}
    Segment(Point a, Point b): a(a), b(b) {}
    Segment(double x1, double y1, double x2, double y2) {
        a = Point(x1, y1);
        b = Point(x2, y2);
    }
};

struct Circle {
    double x, y, r;
    Circle() {}
    Circle(double x, double y, double r): x(x), y(y), r(r) {}
};

std::vector<Segment> rect;

#define sqr(x) ((x) * (x))
double get_dist(Point a, Point b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

double get_dist(Point p, Line v) {
    return fabs(det(p - v.a, v.b - v.a)) / get_dist(v.a, v.b);
}

double get_dist(Point p, Segment v) {
    Point a = v.a;
    Point b = v.b;
    if (sgn(dot(p - b, a - b)) < 0 || sgn(dot(p - a, b - a)) < 0) {
        return std::min(get_dist(p, a), get_dist(p, b));
    }
    return get_dist(p, Line(a, b));
}

bool cross(Circle c, Line v) {
    double d = get_dist(Point(c.x, c.y), v);
    return sgn(d - c.r) <= 0;
}

void get_cross_point(Circle c, Line v, std::vector<Point> &points) {
    points.clear();
    Point p(c.x, c.y);
    Point a = v.lineprog(p);
    double d = get_dist(p, v);
    d = sqrt(c.r * c.r - d * d);
    if (sgn(d) == 0) {
        points.push_back(a);
    }
    points.push_back(a - ((v.b - v.a).trunc(d)));
    points.push_back(a + ((v.b - v.a).trunc(d)));
}

int main() {
    double sx, sy;
    while (scanf("%lf%lf", &sx, &sy) != EOF) {
        if (sgn(sx) == 0 && sgn(sy) == 0) {
            break;
        }
        Point start(sx, sy);

        double cx, cy, r;
        scanf("%lf%lf%lf", &cx, &cy, &r);
        Circle c(cx, cy, r);

        rect.clear();
        double x1, y1, x2, y2;
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        rect.push_back(Segment(x1, y1, x2, y1));
        rect.push_back(Segment(x2, y1, x2, y2));
        rect.push_back(Segment(x2, y2, x1, y2));
        rect.push_back(Segment(x1, y2, x1, y1));

        double answer = 1E20;

        for (double alpha = 0; sgn(alpha - PI) <= 0; alpha += 1E-3) {
            Line l(sx, sy, alpha);
            if (cross(c, l)) {
                std::vector<Point> cross_points;
                get_cross_point(c, l, cross_points);
                Point p;
                if ((int)cross_points.size() == 1) {
                    p = cross_points[0];
                } else {
                    double d_0 = get_dist(start, cross_points[0]);
                    double d_1 = get_dist(start, cross_points[1]);
                    p = sgn(d_0 - d_1) <= 0 ? cross_points[0] : cross_points[1];
                }
                double next_dist = 1E20;
                for (int i = 0; i < 4; ++ i) {
                    next_dist = std::min(next_dist, get_dist(p, rect[i]));
                }
                answer = std::min(answer, get_dist(start, p) + next_dist);
            }
        }

        printf("%.2f\n", answer);
    }
}
