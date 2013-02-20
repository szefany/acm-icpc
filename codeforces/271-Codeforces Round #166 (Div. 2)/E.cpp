// Codeforces Round #166 (Div. 2)
// Problem E, Three Horses
#include <iostream>
#include <cstdio>
#include <algorithm>

int n, m;

long long solve (long long key) {
    long long result = 0;
    while (key <= m) {
        result += m - key;
        key <<= 1;
    }
    return result;
}

int main () {
    scanf ("%d%d", &n, &m);
    int value = 0;
    for (int i = 0; i < n; ++ i) {
        int x;
        scanf ("%d", &x);
        value = std::__gcd (value, x - 1);
    }
    while (value % 2 == 0) {
        value /= 2;
    }
    long long answer = 0;
    for (int i = 1; i * i <= value; ++ i) {
        if (value % i == 0) {
            answer += solve (i);
            if (i * i != value) {
                answer += solve (value / i);
            }
        }
    }
    std::cout << answer << std::endl;
    return 0;
}
