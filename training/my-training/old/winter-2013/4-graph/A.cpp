#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 105;

int dist[N], addi[N], start[N], end[N];
int n;

void read (int &key) {
    int a, b;
    scanf (" %d:%d", &a, &b);
    key = a * 60 + b;
}

int main () {
    while (scanf ("%d", &n) != EOF && n > 0) {
        for (int i = 1; i <= n; ++ i) {
            scanf ("%d%d", &dist[i], &addi[i]);
            read (start[i]);
            read (end[i]);
        }
        int s, t;
        read (s), read (t);
        int moment = s;
        for (int i = 1; i <= n; ++ i) {
            if (moment >= start[i] && moment < end[i] || moment < start[i] && moment + dist[i] > start[i]) {
                moment += addi[i];
            }
            moment += dist[i];
        }
        puts (moment < t ? "Lucky YY!" : "Poor YY!");
    }
    return 0;
}
