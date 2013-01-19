// Codeforces Round #157 (Div. 2)
// Problem E, Little Elephant and LCM
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 100005;
const int M = 130;
const int MOD = 1000000000 + 7;

int divisors[M], pivot[N];
int a[N], b[N];
int n;

int power (int x, int y) {
    if (y == 0) return 1;
    int result = power (x, y >> 1);
    result = (long long)result * result % MOD;
    if (y & 1) {
        result = (long long)result * x % MOD;
    }
    return result;
}

int main () {
    freopen ("input.txt", "r", stdin);
    scanf ("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf ("%d", &a[i]);
    }
    sort (a + 1, a + n + 1);
    for (int i = 1; i <= a[n]; ++ i) {
        pivot[i] = lower_bound (a + 1, a + n + 1, i) - a;
    }
    long long ans = 0;
    for (int x = 1; x <= a[n]; ++ x) {
        int length = 0;
        for (int i = 1; i * i <= x; ++ i) {
            if (x % i == 0) {
                divisors[++ length] = i;
                if (i * i != x) {
                    divisors[++ length] = x / i;
                }
            }
        }
        sort (divisors + 1, divisors + length + 1);
        long long temp1 = 1;
        for (int i = 1; i <= length; ++ i) {
            int number = i == length ? n - pivot[divisors[i]] + 1 : pivot[divisors[i + 1]] - pivot[divisors[i]];
            temp1 = temp1 * power (i, number) % MOD;
        }
        long long temp2 = 1;
        if (length == 1) temp2 = 0;
        else {
            for (int i = 1; i < length; ++ i) {
                int number = i == length - 1 ? n - pivot[divisors[i]] + 1 : pivot[divisors[i + 1]] - pivot[divisors[i]];
                temp2 = temp2 * power (i, number) % MOD;
            }
        }
        ans = ((ans + temp1 - temp2) % MOD + MOD) % MOD;
    }
    cout << ans << endl;
    return 0;
}