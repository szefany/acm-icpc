// POJ 1228, Grandpa's Estate
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1E-8;
const int N = 1005;

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
    return sqr (a.x - b.x) + sqr (a.y - b.y);
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

struct Polygon {
    static const int N = 1005;
    int size;
    Point points[N];
    Polygon () {size = 0;}
    void push (Point p) {
        points[size ++] = p;
    }
    void get_convex (Polygon &convex) {
        if (size < 2) {
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
    }
};

bool on_segment (Point p, Segment s) {
    return det (p - s.a, p - s.b) == 0 && dot (p - s.a, p - s.b) <= 0;
}

int n;
Point points[N];

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        scanf ("%d", &n);
        Polygon poly;
        for (int i = 0; i < n; ++ i) {
            points[i].input ();
            poly.push (points[i]);
        }
        Polygon convex;
        poly.get_convex (convex);
        bool flag = true;
        if (convex.size < 3 || convex.size == 3 && det (convex.points[0] - convex.points[1], \
            convex.points[2] - convex.points[1]) == 0) {
            flag = false;
        }
        else {
            for (int i = 0; i + 1 < convex.size; ++ i) {
                int counter = 0;
                for (int j = 0; j < n && counter < 3; ++ j) {
                    counter += on_segment (points[j], Segment (convex.points[i], convex.points[i + 1]));
                }
                if (counter < 3) {
                    flag = false;
                    break;
                }
            }
        }
        puts (flag ? "YES" : "NO");
    }
    return 0;
}
