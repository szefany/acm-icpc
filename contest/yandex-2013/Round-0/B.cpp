#include <cstdio>

const int N = 50000;

bool visit[N];
int primes[N], total;
int queue[N], length;

int main() {
    for (int i = 2; i < N; ) {
        primes[++ total] = i;
        for (int j = i + i; j < N; j += i) {
            visit[j] = true;
        }
        for (i ++; visit[i]; ++ i);
    }
    for (int i = 1; i < total; ++ i) {
        if (primes[i] + 2 == primes[i + 1]) {
            queue[++ length] = primes[i] + 1;
        }
    }
    int n;
    scanf("%d", &n);
    for (int i = 1; queue[i] <= n; ++ i) {
        printf("%d\n", queue[i]);
    }
    return 0;
}
