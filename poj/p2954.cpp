// POJ 2954, Triangle
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const double EPS = 1E-8;

struct Point {
    int x, y;
    void input () {
        scanf ("%d%d", &x, &y);
    }
};

Point points[5];

int det (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

int gcd (int x, int y) {
    if (x < y) {
        swap (x, y);
    }
    while (y) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

int abs (int x) {
    return x > 0 ? x : -x;
}

int main () {
    while (1) {
        int counter = 0;
        for (int i = 0; i < 3; ++ i) {
            points[i].input ();
            if (points[i].x == 0 && points[i].y == 0) {
                counter ++;
            }
        }
        if (counter == 3) {
            break;
        }
        int area = 0, on_edge = 0;
        for (int i = 0; i < 3; ++ i) {
            int j = (i + 1) % 3;
            area += det (points[i], points[j]);
            on_edge += gcd (abs (points[i].x - points[j].x), abs (points[i].y - points[j].y));
        }
        printf ("%d\n", (abs (area) - on_edge + 2) / 2);
    }
    return 0;
}
