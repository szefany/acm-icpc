#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const double EPS = 1E-8;
const double INF = 1E5;

int sgn(double x) {
    return x < -EPS ? -1 : x > EPS;
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    Point operator - (const Point &o) const {
        return Point(x - o.x, y - o.y);
    }
    double norm2() const;
    double norm() const;
    double dist(const Point &a) const;
    double dist_line(const Point &a, const Point &b) const;
    double dist_segment(const Point &a, const Point &b) const;
};

double det(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double Point::norm2() const {return dot(*this, *this);}
double Point::norm() const {return sqrt(norm2());}

double Point::dist(const Point &a) const {
    return (*this - a).norm();
}

double Point::dist_line(const Point &a, const Point &b) const {
    Point p = *this;
    return fabs(det(p - a, p - b) / (a - b).norm());
}

double Point::dist_segment(const Point &a, const Point &b) const {
    Point p = *this;
    if (sgn(dot(p - b, a - b)) < 0 || sgn(dot(p - a, b - a)) < 0)
        return std::min(dist(a), dist(b));
    return dist_line(a, b);
}

double v1, v2, v, t, x;
double end_time;

struct Rain_Data {
    double x, y, r, h;
    void input() {
        scanf("%lf%lf%lf%lf", &x, &y, &r, &h);
    }
};

struct Event {
    double left, right;
    Event(double l, double r): left(l), right(r) {}
    bool operator < (const Event &o) const {
        int flag = sgn(left - o.left);
        return flag < 0 || flag == 0 && right < o.right;
    }
};

std::vector<Event> events;

bool in_rain(const Rain_Data &data, double dt) {
    double r = data.r;
    double h = data.h;
    double x0 = data.x;
    double y0 = data.y;
    double x1 = x - v1 * dt;
    double y1 = v * dt;

    bool result;
    if (sgn(y1 - y0) <= 0) {
        result = sgn(Point(x1, y1).dist(Point(x0, y0)) - r) <= 0;
    } else {
        Point a(x0, y0 + h);
        Point b(x0 + r, y0);
        Point c(x0 - r, y0);
        Point p(x1, y1);
        result = sgn(det(b - p, a - p)) >= 0 && sgn(det(a - p, c - p)) >= 0 \
            && sgn(det(c - p, b - p)) >= 0;
    }
    return result;
}

double calc_dist(const Rain_Data &data, double dt) {
    if (in_rain(data, dt)) {
        return 0;
    }

    double r = data.r;
    double h = data.h;
    double x0 = data.x;
    double y0 = data.y;
    double x1 = x - v1 * dt;
    double y1 = v * dt;

    double result;
    if (sgn(y1 - y0) <= 0) {
        result = Point(x0, y0).dist(Point(x1, y1)) - r;
    } else if (sgn(x1 - x0) >= 0) {
        result = Point(x1, y1).dist_segment(Point(x0, y0 + h), Point(x0 + r, y0));
    } else {
        result = Point(x1, y1).dist_segment(Point(x0, y0 + h), Point(x0 - r, y0));
    }
    return result;
}

void solve(const Rain_Data &data) {
    double x0 = data.x;
    double y0 = data.y;
    double r = data.r;
    double h = data.h;

    double lower, upper;

    lower = -INF, upper = INF;
    while (fabs(upper - lower) > EPS) {
        double dt = (upper - lower) / 3;
        double t1 = lower + dt;
        double t2 = upper - dt;
        if (calc_dist(data, t1) > calc_dist(data, t2)) {
            lower = t1;
        } else {
            upper = t2;
        }
    }
    double t0 = (lower + upper) / 2;
    double d0 = calc_dist(data, t0);
    if (sgn(d0) > 0) {
        return;
    }

    lower = -INF, upper = t0;
    while (fabs(upper - lower) > EPS) {
        double m = (lower + upper) / 2;
        if (in_rain(data, m)) {
            upper = m;
        } else {
            lower = m;
        }
    }
    double start = (lower + upper) / 2;

    lower = t0, upper = INF;
    while (fabs(upper - lower) > EPS) {
        double m = (lower + upper) / 2;
        if (in_rain(data, m)) {
            lower = m;
        } else {
            upper = m;
        }
    }
    double end = (lower + upper) / 2;

    events.push_back(Event(start, end));
}

int main() {
    int test;
    scanf("%d", &test);
    for (int counter = 1; counter <= test; ++ counter) {
        scanf("%lf%lf%lf%lf%lf", &v1, &v2, &v, &t, &x);
        end_time = v2 * t / (v2 - v1);

        int n;
        scanf("%d", &n);
        events.clear();
        for (int i = 0; i < n; ++ i) {
            Rain_Data data;
            data.input();
            solve(data);
        }
        std::sort(events.begin(), events.end());
        double answer = 0, current = 0;
        foreach(iter, events) {
            double l = (*iter).left;
            double r = (*iter).right;
            l = std::max(l, 0.0);
            r = std::min(r, end_time);
            if (sgn(l - current) > 0) {
                answer += r - l;
                current = r;
            } else {
                answer += std::max(current, r) - current;
                current = std::max(current, r);
            }
        }
        printf("Case %d: %.4f\n", counter, answer);
    }
    return 0;
}
