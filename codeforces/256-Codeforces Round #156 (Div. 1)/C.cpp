// Codeforces Round #156 (Div. 1)
// Problem C, Furlo and Rublo and Game
#include <iostream>
#include <cstdio>
using namespace std;

int sg (long long x) {
    if (x < 4) return 0;
    if (x < 16) return 1;
    if (x < 82) return 2;
    if (x < 6724) return 0;
    if (x < 50626) return 3;
    if (x < 2562991876LL) return 1;
    return 2;
}

int main () {
    int n;
    scanf ("%d", &n);
    int ans = 0;
    while (n --) {
        long long x;
        cin >> x;
        ans ^= sg (x);
    }
    puts (ans ? "Furlo" : "Rublo");
    return 0;
}
