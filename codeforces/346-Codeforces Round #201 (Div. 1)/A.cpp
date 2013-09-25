#include <cstdio>
#include <algorithm>

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int max_value = 0;
        int result = 0;
        for (int i = 0; i < n; ++ i) {
          int x;
          scanf("%d", &x);
          max_value = std::max(max_value, x);
          result = std::__gcd(result, x);
        }
        max_value = max_value / result - n;
        puts((max_value & 1) ? "Alice" : "Bob");
    }
    return 0;
}
