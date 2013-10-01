#include <cstdio>
#include <cstring>
#include <iostream>

long long check(long long n) {
    long long result;
    long long t = n & 3;
    if (t & 1) {
        result = t / 2 ^ 1;
    } else {
        result = t / 2 ^ n;
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    long long result = 0;
    while (n --) {
        long long x, m;
        std::cin >> x >> m;
        result ^= check(x - 1) ^ check(x + m - 1);
    }
    puts(result == 0 ? "bolik" : "tolik");
    return 0;
}
