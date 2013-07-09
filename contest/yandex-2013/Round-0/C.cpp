#include <iostream>

bool check(long long n) {
    long long result;
    long long t = n & 3;
    if (t & 1) {
        result = t / 2u ^ 1;
    } else {
        result = t / 2u ^ n;
    }
    return result == 0;
}

int main() {
    long long n;
    std::cin >> n;
    std::cout << n * (n + 1) / 2 << " ";

    long long answer;
    if (n != 1 && check(n)) {
        answer = 0;
    } else if (n % 4 == 3) {
        answer = n;
    } else if (n % 4 == 1) {
        answer = (n + 1) / 2;
    } else if (n % 4 == 0) {
        if (n == 4) {
            answer = 1;
        } else {
            long long x = 1;
            while (x << 1 <= n) {
                x <<= 1;
            }
            answer = n - x + 1;
        }
    } else if (n == 2) {
        answer = 1;
    } else if (n == 6) {
        answer = 3;
    } else {
        long long x = 6;
        long long y = 4;
        while (x + y <= n) {
            x += y;
            y <<= 1;
        }
        answer = n - x + 3;
    }
    std::cout << answer << std::endl;
    return 0;
}
