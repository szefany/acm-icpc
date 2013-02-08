// Bayan 2012-2013 Elimination Round (ACM ICPC Rules, English statements)
// Problem A, Old Peykan
#include <iostream>
#include <cstdio>
using namespace std;

const int N = 1000;

int n, m;
int d[N], s[N];

int main () {
    scanf ("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf ("%d", &d[i]);
    }
    for (int i = 0; i < n; ++ i) {
        scanf ("%d", &s[i]);
    }
    int answer = 0;
    for (int i = 0, fuel = 0, max_value = 0; i < n; ++ i) {
        fuel += s[i];
        max_value = max (max_value, s[i]);
        if (fuel >= d[i]) {
            fuel -= d[i];
            answer += d[i];
        }
        else {
            int stay = (d[i] - fuel) / max_value;
            if (fuel + stay * max_value < d[i]) {
                stay ++;
            }
            answer += d[i] + stay * m;
            fuel = fuel + stay * max_value - d[i];
        }
    }
    printf ("%d\n", answer);
    return 0;
}
