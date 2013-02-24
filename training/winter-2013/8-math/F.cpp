// UVA 11401, Triangle Counting
#include <iostream>
#include <cstdio>

const int N = 1000000 + 5;
long long number[N];

int main () {
    for (int i = 4; i < N; ++ i) {
        number[i] = number[i - 1] + ((long long)(i - 1) * (i - 2) / 2 - (i - 1) / 2) / 2;
    }
    int n;
    while (scanf ("%d", &n) != EOF && n >= 3) {
        std::cout << number[n] << '\n';
    }
    return 0;
}