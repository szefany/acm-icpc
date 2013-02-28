// Codeforces Round #169 (Div. 2)
// Problem A, Lunch Rush
#include <iostream>

int main () {
    long long n, k, answer = - (1LL) << 60;
    std::cin >> n >> k;
    for (int i = 0; i < n; ++ i) {
        long long f, t, temp;
        std::cin >> f >> t;
        if (t < k) {
            temp = f;
        } else {
            temp = f - t + k;
        }
        answer = std::max (answer, temp);
    }
    std::cout << answer << std::endl;
    return 0;
}
