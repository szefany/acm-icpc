// Codeforces Round #162 (Div. 1)
// Problem C, Choosing Balls
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100005;

int color[N], value[N];
long long f[N][2], g[N];
int n, a, b, m;

pair<long long, int> temp[2];
int main () {
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        scanf ("%d", &value[i]);
    }
    for (int i = 1; i <= n; ++ i) {
        scanf ("%d", &color[i]);
    }
    while (m --) {
        scanf ("%d%d", &a, &b);
        memset (f, 0, sizeof (f));
        memset (g, 200, sizeof (g));
        memset (temp, 200, sizeof (temp));
        long long ans = 0, INF = g[0];
        f[0][0] = 0;
        for (int i = 1; i <= n; ++ i) {
            f[i][0] = max (f[i - 1][0], f[i - 1][1]);
            f[i][1] = (long long)b * value[i];
            if (g[color[i]] != INF) {
                f[i][1] = max (f[i][1], g[color[i]] + (long long)a * value[i]);
            }
            if (temp[0].second != color[i]) {
                f[i][1] = max (f[i][1], temp[0].first + (long long)b * value[i]);
            }
            else {
                f[i][1] = max (f[i][1], temp[1].first + (long long)b * value[i]);
            }
            g[color[i]] = max (g[color[i]], f[i][1]);
            if (f[i][1] > temp[0].first) {
                if (temp[0].second != color[i]) {
                    temp[1] = temp[0];
                    temp[0] = make_pair (f[i][1], color[i]);
                }
                else {
                    temp[0] = make_pair (f[i][1], color[i]);        
                }
            }
            else if (f[i][1] > temp[1].first && temp[0].second != color[i]) {
                temp[1] = make_pair (f[i][1], color[i]);
            }
            ans = max (ans, max (f[i][1], f[i][0]));
        }
        cout << ans << endl;
    }
    return 0;
}
