#include <cstdio>
#include <cstring>

const int N = 2000000 + 10;

int primes[N], length;
int n;

bool visit[N];

int main() {
    scanf("%d", &n);
    for (int i = 2; length < n; ) {
        primes[++ length] = i;
        for (int j = i + i; j < N; j += i) {
            visit[j] = true;
        }
        for (i ++; visit[i]; ++ i);
    }
    for (int i = 1; i <= n; ++ i) {
        printf("%d%c", primes[i], i == n ? '\n' : ' ');
    }
    return 0;
}
