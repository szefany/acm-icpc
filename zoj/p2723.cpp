// ZOJ 2723, Semi-Prime
#include <cstdio>

const int N = 1000000 + 5;

bool is_prime[N];
int primes[N];
int n, counter;

int main () {
    for (int i = 2; i < N; ++ i) {
        is_prime[i] = true;
    }
    for (int i = 2; i < N; ) {
        primes[counter ++] = i;
        for (int j = i + i; j < N; j += i) {
            is_prime[j] = false;
        }
        for (++ i; !is_prime[i]; ++ i);
    }
    while (scanf ("%d", &n) != EOF) {
        bool valid = !is_prime[n];
        if (valid) {
            for (int i = 0; i < counter && primes[i] < n; ++ i) {
                int x = primes[i];
                if (n % x == 0) {
                    valid = is_prime[n / x];
                    break;
                }
            }
        }
        puts (valid ? "Yes" : "No");
    }
    return 0;
}
