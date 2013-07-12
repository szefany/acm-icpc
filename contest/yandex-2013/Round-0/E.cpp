#include <cstdio>
#include <iostream>
#include <queue>
#include <algorithm>

const int N = 100000 + 10;

long long a[N];
long long n, x, k;

void buffer(long long temp, int &pivot) {
    while (pivot < n && temp > 0) {
        long long delta = std::min(temp, a[pivot]);
        a[pivot] -= delta;
        temp -= delta;
        if (a[pivot] == 0) {
            pivot ++;
        }
    }
}

int main() {
    std::cin >> n >> x >> k;
    for (int i = 0; i < n; ++ i) {
        std::cin >> a[i];
    }
    long long number = 0, sum = 0;
    for (int i = 0; i < n; ++ i) {
        sum += a[i];
        if (a[i] >= x && x > 0) {
            number += a[i] / x;
            a[i] %= x;
        }
    }
    long long answer = 0;
    if (number * (x + k) >= sum) {
        answer = (sum + x + k - 1) / (x + k);
    } else if (x == 0) {
        answer = (sum + k - 1) / k;
    } else {
        answer = number;
        std::sort(a, a + n);
        int pivot = 0;
        buffer(number * k, pivot);
        for (int i = n - 1; pivot <= i; -- i) {
            answer ++;
            a[i] = 0;
            buffer(k, pivot);
        }
    }
    std::cout << answer << std::endl;
    return 0;
}
