#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 100 + 10;

int a[N], b[N], n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
    }
    int answer = 0;
    for (int l = 1; l <= n; ++ l) {
        for (int r = l; r <= n; ++ r) {
            for (int i = 1; i < l; ++ i) {
                b[i] = a[i];
            }
            for (int i = l; i <= r; ++ i) {
                b[i] = 1 - a[i];
            }
            for (int i = r + 1; i <= n; ++ i) {
                b[i] = a[i];
            }
            int temp = 0;
            for (int i = 1; i <= n; ++ i) {
                temp += b[i];
            }
            answer = std::max(answer, temp);
        }
    }
    printf("%d\n", answer);
    return 0;
}
