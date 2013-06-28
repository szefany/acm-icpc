#include <cstdio>

const int N = 1000000;

int a[N], b[N];
int n;

int main() {
    freopen("input", "r", stdin);
    scanf("%d", &n);
    long long delta = 0;
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", a + i, b + i);
        delta += a[i];
    }
    int pivot = 0;
    while (pivot < n && delta > 500) {
        putchar('G');
        delta -= 1000;
        pivot ++;
    }
    while (pivot < n) {
        putchar('A');
        pivot ++;
    }
    puts("");
    return 0;
}
