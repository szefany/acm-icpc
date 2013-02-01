// POJ 1265, Area
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int N = 105;
const double EPS = 1E-8;

struct Point {
    int x, y;
    Point () {}
    Point (int x0, int y0): x (x0), y (y0) {}
    Point operator - (const Point &other) {
        return Point (x - other.x, y - other.y);
    }
};

int sgn (double x) {
    if (x < -EPS) {
        return -1;
    }
    return x < EPS ? 0 : 1;
}

double det (Point p, Point q) {
    return p.x * q.y - p.y * q.x;
}

double dot (Point p, Point q) {
    return p.x * q.x + p.y * q.y;
}

bool on_segment (Point p, Point a, Point b) {
    return sgn (det (p - a, p - b)) == 0 && sgn (dot (p - a, p - b)) <= 0;
}

struct Polygon {
    static const int N = 105;
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

    int relation (Point p) {
        // 0: inside 1: on the edge 2: outside
        for (int i = 0; i < size; ++ i) {
            if (on_segment (p, points[i], points[(i + 1) % size])) {
                return 1;
            }
        }
        int counter[2] = {0};
        for (int i = 0; i < size; ++ i) {
            Point last = points[i];
            Point now = points[(i + 1) % size];
            if (sgn (last.y - p.y) < 0 && sgn (now.y - p.y) >= 0 \
                || sgn (now.y - p.y) < 0 && sgn (last.y - p.y) >= 0) {
                double x = ((double)p.y - last.y) * ((double)now.x - last.x) / (now.y - last.y) + last.x;
                counter[sgn (x - p.x) >= 0] ++;
            }
        }
        return ((counter[0] & 1) && (counter[1] & 1)) ? 0 : 2;
    }
};

int n;

int main() {
    int test_count;
    scanf ("%d", &test_count);
    for (int counter = 1; counter <= test_count; ++ counter) {
        scanf ("%d", &n);
        Polygon poly;
        int x = 0, y = 0;
        int min_x = 0, max_x = 0, min_y = 0, max_y = 0;
        poly.push (Point (0, 0));
        for (int i = 0; i < n; ++ i) {
            int dx, dy;
            scanf ("%d%d", &dx, &dy);
            x += dx, y += dy;
            poly.push (Point (x, y));
            min_x = min (min_x, x), min_y = min (min_y, y);
            max_x = max (max_x, x), max_y = max (max_y, y);
        }
        poly.size --;
        double area = poly.area ();
        int answer[2] = {0};
        for (int x = min_x; x <= max_x; ++ x) {
            for (int y = min_y; y <= max_y; ++ y) {
                int flag = poly.relation (Point (x, y));
                if (flag < 2) {
                    answer[flag] ++;
                }
            }
        }
        printf ("Scenario #%d:\n", counter);
        printf ("%d %d %.1f\n\n", answer[0], answer[1], area);
    }
    return 0;
}
