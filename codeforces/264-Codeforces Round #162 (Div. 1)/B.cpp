// Codeforces Round #162 (Div. 1)
// Problem B, Good Sequences
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100005;

vector<int> divisors[N];
bool visit[N];
int f[N], a[N], prime[N];
int n, counter;

int main () {
    for (int i = 2; i < N; ) {
        prime[++ counter] = i;
        for (int j = i + i; j < N; j += i) {
            visit[j] = true;
        }
        for (i ++; i < N && visit[i]; ++ i);
    }
    memset (visit, 0, sizeof (visit));
    scanf ("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf ("%d", &a[i]);
        if (visit[a[i]]) continue;
        visit[a[i]] = true;
        int x = a[i];
        for (int j = 1; j <= counter && prime[j] * prime[j] <= x; ++ j) {
            if (x % prime[j] == 0) {
                divisors[a[i]].push_back (prime[j]);
                while (x % prime[j] == 0) {
                    x /= prime[j];
                }
            }
        }
        if (x > 1) {
            divisors[a[i]].push_back (x);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++ i) {
        int temp = 1;
        for (int j = 0; j < divisors[a[i]].size(); ++ j) {
            int x = divisors[a[i]][j];
            temp = max (temp, f[x] + 1);
        }
        for (int j = 0; j < divisors[a[i]].size(); ++ j) {
            int x = divisors[a[i]][j];
            f[x] = max (f[x], temp);
        }
        ans = max (ans, temp);
    }
    printf ("%d\n", ans);
    return 0;
}

