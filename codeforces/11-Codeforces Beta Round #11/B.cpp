#include <cstdio>
#include <cstring>
#include <iostream>

int main() {
    long long n;
    std::cin >> n;
    if (n == 0) {
        puts("0");
        return 0;
    }
    if (n < 0) n = -n;
    long long x = 0;
    long long sum = 0;
    while (sum <= n) {
        x ++;
        sum += x;
    }
    sum -= x;
    x --;
    long long answer;
    if (sum == n) {
        answer = x;
    } else if (x % 2 == 1) {
        if ((n - sum) % 2 == 1) {
            answer = x + 2;
        } else {
            answer = x + 1;
        }
    } else {
        if ((n - sum) % 2 == 1) {
            answer = x + 1;
        } else {
            answer = x + 3;
        }
    }
    std::cout << answer << std::endl;
    return 0;
}
