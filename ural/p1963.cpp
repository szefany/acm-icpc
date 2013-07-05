#include <cstdio>
#include <cstring>
#include <cmath>

const int N = 10;
const double EPS = 1E-8;

int sgn(double x) {
    return x < -EPS ? -1 : x > EPS;
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    Point operator + (const Point &other) {
        return Point(x + other.x, y + other.y);
    }
    Point operator - (const Point &other) {
        return Point(x - other.x, y - other.y);
    }   
    Point operator / (const double a) {
        return Point(x / a, y / a);
    }
    bool operator == (const Point &other) {
        return sgn(x - other.x) == 0 && sgn(y - other.y) == 0;
    }
    void input() {
        scanf("%lf%lf", &x, &y);
    }
};

Point points[N];

#define sqr(x) ((x) * (x))
double get_dist(Point a, Point b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

Point rotate (Point p, Point o, double angle) {
    Point vec = p - o;
    double c = cos (angle), s = sin (angle);
    return Point (o.x + vec.x * c - vec.y * s, o.y + vec.x * s + vec.y * c);
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

bool check(Point a, Point b) {
    for (int i = 0; i < 4; ++ i) {
        Point p = points[i];
        if ((p == a) || (p == b)) {
            continue;
        }
        double d1 = get_dist(a, b);
        double d2 = get_dist(p, b);
        double d3 = get_dist(p, a);
        double alpha = acos((d1 * d1 + d2 * d2 - d3 * d3) / (2 * d1 * d2));
        Point q = rotate(p, b, 2 * alpha);
        if (sgn(dot(p - q, a - b)) != 0) {
            q = rotate(p, b, -2 * alpha);
        }
        bool flag = false;
        for (int i = 0; i < 4; ++ i) {
            if (q == points[i]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            return false;
        }
    }
    return true;
}

int main() {
    for (int i = 0; i < 4; ++ i) {
        points[i].input();      
    }
    
    int answer = 0;
    for (int i = 0; i < 4; ++ i) {
        for (int j = i + 1; j < 4; ++ j) {
            answer += check(points[i], points[j]);
        }
    }
    for (int i = 0; i < 4; ++ i) {
        for (int j = i + 1; j < 4; ++ j) {
            Point p = (points[i] + points[(i + 1) % 4]) / 2;
            Point q = (points[j] + points[(j + 1) % 4]) / 2;
            answer += check(p, q);
        }
    }
    printf("%d\n", answer * 2);
    return 0;
}
