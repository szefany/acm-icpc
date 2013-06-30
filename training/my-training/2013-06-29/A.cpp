#include <cstdio>
#include <algorithm>

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    int c = std::__gcd(a, b);
    int d = a * b / c;
    int answer = 0;
    for (int i = c + 1; i < d; ++ i) {
        bool flag = true;
        for (int j = 2; j * j <= i; ++ j) {
            if (i % j == 0) {
                flag = false;
            }
        }
        answer += flag;
    }
    printf("I'm confident!%d\n", answer);
    return 0;
}
