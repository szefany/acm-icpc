#include <iostream>
#include <iomanip>

const int N = 500 + 10;

long long A[N], B[N];
int n, k1, k2, k3, a, b, c;

int main() {
    int test;
    std::cin >> test;
    while (test --) {
        std::cin >> n >> k1 >> k2 >> k3 >> a >> b >> c;
        long long k = k1 * k2 * k3;
        A[n] = 1;
        B[n] = k;
        for (int i = n - 1; i >= 0; -- i) {
            A[i] = p;
            B[i] = 1;
            for (int x = 1; x <= k1; ++ x) {
                for (int y = 1; y <= k2; ++ y) {
                    for (int z = 1; z <= k3; ++ z) {
                        if (x == a && y == b && z == c) {
                            continue;
                        }
                        int next = i + x + y + z;
                        if (next <= n) {
                            A[i] += A[next] * p;
                            B[i] += A[next] * p;
                        }
                    }
                }
            }
        }
        std::cout << std::setprecision(15) << std::fixed;
        std::cout << B[0] / (1 - A[0]) << std::endl;
    }
    return 0;
}
