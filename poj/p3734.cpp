#include <cstdio>

const int MOD = 10007;

int power(int a, int b) {
    int result = 1, t = a;
    while (b) {
        if (b & 1) {
            (result *= t) %= MOD;
        }
        (t *= t) %= MOD;
        b >>= 1;
    }
    return result;
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        int n;
        scanf("%d", &n);
        int answer = (power(4, n - 1) + power(2, n - 1)) % MOD;
        printf("%d\n", answer);
    }
    return 0;
}
