#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

const int N = 10000 + 5;
const double EPS = 1E-8;

double capacity[N], temp[N];
int n;
double p;

int sgn (double x) {
    if (x < -EPS) {
        return -1;
    }
    return x < EPS ? 0 : 1;
}

bool check (double x) {
    double need = 0, supply = 0;
    for (int i = 0; i < n; ++ i) {
        if (capacity[i] > x) {
            supply += capacity[i] - x;
        } else {
            need += x - capacity[i];
        }
    }
    return sgn (supply * (1 - p) - need) > 0;
}

int main () {
    scanf ("%d%lf", &n, &p), p /= 100;
    double max_capacity = 0;
    for (int i = 0; i < n; ++ i) {
        scanf ("%lf", &capacity[i]);
        max_capacity = std::max (max_capacity, capacity[i]);
    }
    std::sort (capacity, capacity + n);
    double l = 0, r = max_capacity;
    while (fabs (r - l) > 1E-10) {
        double middle = (l + r) / 2;
        if (check (middle)) {
            l = middle;
        } else {
            r = middle;
        }
    }
    printf ("%.10f\n", (l + r) / 2);
    return 0;
}
