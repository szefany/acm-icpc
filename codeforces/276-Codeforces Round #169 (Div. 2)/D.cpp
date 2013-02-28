// Codeforces Round #169 (Div. 2)
// Problem D, Little Girl and Maximum XOR
#include <iostream>

int main () {
    long long l, r, answer = 0;
    std::cin >> l >> r;
    for (int i = 63; i >= 0; -- i) {
        long long x = (1LL) << i;
        if ((x & l) != (x & r)) {
            answer += (x << 1) - 1;
            break;
        }
    }
    std::cout << answer << std::endl;
    return 0;
}
