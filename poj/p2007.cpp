// POJ 2007, Scrambled Polygon
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const double EPS = 1E-8;

struct Point {
    int x, y;
    Point () {}
    Point (int x0, int y0): x (x0), y (y0) {}
    Point operator - (const Point &other) {
        return Point (x - other.x, y - other.y);
    }
};

vector<Point> points;
Point p0;

int sgn (double x) {
    if (x < -EPS) {
        return -1;
    }
    return x < EPS ? 0 : 1;
}

double det (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

bool cmp (Point p, Point q) {
    return det (p - p0, q - p0) > 0;
}

int main () {
    int x, y;
    while (scanf ("%d %d", &x, &y) != EOF) {
        points.push_back (Point (x, y));
    }
    p0 = points[0];
    sort (points.begin() + 1, points.end(), cmp);
    for (int i = 0; i < points.size(); ++ i) {
        printf ("(%d,%d)\n", points[i].x, points[i].y);
    }
    return 0;
}
