#include <cstdio>
#include <cstring>

const int MOD = 1000000000 + 7;

int a[100000], b[100000];
int n;

int inverse (int a) {
    return a == 1 ? 1 : (long long)(MOD - MOD / a) * inverse (MOD % a) % MOD;
}

int main () {
    scanf ("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf ("%d", &a[i]);
    }
    int result = 1;
    for (int i = 0; i < n; ++ i) {
        result = (long long)result * a[i] % MOD;
        a[i] = inverse (a[i]);
    }
    for (int i = 0; i < n; ++ i) {
        int answer = (long long)result * a[i] % MOD;
        printf ("%d%c", answer, i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
