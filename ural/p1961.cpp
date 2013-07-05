#include <cstdio>
#include <iostream>

long long n, m, N;

int main() {
    std::cin >> n >> m >> N;
    long long l = m, r = N - n + m;
    while (l < r) {
        long long x = l + r + 1 >> 1;
        long long a = (x + 1) * (N - x - n + m);
        long long b = (x + 1 - m) * (N - x);
        if (a >= b) {
            l = x;
        } else {
            r = x - 1;
        }
    }
    long long x = l;
    long long a = (x + 1) * (N - x - n + m);
    long long b = (x + 1 - m) * (N - x);
    if (a >= b && l + 1 <= N - n + m) {
        l ++;
    }
    std::cout << l << std::endl;
    return 0;
}
