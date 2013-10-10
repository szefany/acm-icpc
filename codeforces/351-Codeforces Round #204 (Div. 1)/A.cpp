#include <iostream>
#include <cstdio>
#include <cmath>
#include <climits>

const double EPS = 1E-8;

int n;

int abs(int x) {
    return x > 0 ? x : -x;
}

int main() {
    int sum = 0;
    int count = 0;
    std::cin >> n;
    for (int i = 1; i <= n << 1; ++ i) {
        double temp;
        std::cin >> temp;
        int x = round(temp * 1000) + EPS;
        x %= 1000;
        sum += x;
        count += x == 0;
    }
    int answer = INT_MAX;
    for (int i = n - count; i <= n; ++ i) {
        answer = std::min(answer, abs(sum - i * 1000));
    }
    printf("%.3f\n", answer / 1000.0);
    return 0;
}
