// UVA 11889, Benefit
#include <cstdio>
#include <algorithm>

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        int a, b;
        scanf ("%d%d", &a, &b);
        if (b % a != 0) {
            puts ("NO SOLUTION");
        } else {
            int answer = b / a;
            for (int x = std::__gcd (answer, a); x > 1; x = std::__gcd (answer, a)) {
                answer *= x;
                a /= x;
            }
            printf ("%d\n", answer);
        }
    }
    return 0;
}