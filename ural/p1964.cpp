#include <iostream>

long long n, m;

int main() {
    std::cin >> n >> m;
    long long answer = n;
    while (m --) {
        long long x;
        std::cin >> x;
        if (x <= n - answer) {
            answer = 0;
        } else {
            answer = x - (n - answer);
        }
    }
    std::cout << answer << std::endl;
    return 0;
}
