#include <cstdio>

const int N = 3000;

int a[N], n;

int main() {
    scanf("%d", &n);
    int count = 0;
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
        for (int j = 0; j < i; ++ j) {
            count += a[j] > a[i];
        }
    }
    double a = 0, b = 0;
    for (int i = 1; i <= count; ++ i) {
        double x = b + 1;
        double y = a + 3;
        a = x;
        b = y;
    }
    printf("%.8f\n", a);
    return 0;
}
