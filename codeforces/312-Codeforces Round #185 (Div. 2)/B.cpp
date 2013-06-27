#include <cstdio>

int main() {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    double p = (double)a / b;
    double q = (double)c / d;
    double answer = p / (p + q - p * q);
    printf("%.10f\n", answer);
    return 0;
}
