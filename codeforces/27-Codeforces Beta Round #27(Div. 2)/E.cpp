// Codeforces Beta Round #27(Div. 2)
// Problem E, Number With The Given Amount Of Divisors
#include <iostream>
#include <cstdio>
using namespace std;

const long long INF = 1000000000000000000LL;

int n, length;
int divisors[1000], prime[1000], counter;
bool visit[1000];

void get_prime () {
    for (int i = 2; i <= 1000; ) {
        prime[++ counter] = i;
        for (int j = i + i; j <= 1000; j += i) {
            visit[j] = true;
        }
        for (i ++; i <= 1000 && visit[i]; ++ i);
    }
}

long long ans;
void check () {
    long long result = 1;
    for (int i = length, j = 1; i >= 1; -- i, ++ j) {
        for (int j = 1; j <= divisors[i]; ++ j) {
            long long temp = result * prime[j];
            if (temp > INF || temp > ans) return;
            result = temp;
        }
    }
    if (result < ans) ans = result;
}

void dfs (int u, int x, int last, long long current) {
    if (x == 1) {
        ans = min (ans, current);
        return;
    }
    for (int i = min (x, 60); i >= 2; -- i) {
        if (x % i == 0) {
            long long temp = current;
            for (int j = 1; j < i; ++ j) {
                temp *= prime[u];
                if (temp > ans || temp > INF) break;
            }
            if (temp > ans || temp > INF) continue;
            dfs (u + 1, x / i, i, temp);
        }
    }
}

int main () {
    get_prime ();
    cin >> n;
    ans = 1LL << 60;
    dfs (1, n, 2, 1);
    cout << ans << endl;
}
