#include <cstdio>

int main() {
    int n, m;
    while (scanf("%d", &n) != EOF) {
        int sum = 0;
        for (int i = 0; i < n; ++ i) {
            int x;
            scanf("%d", &x);
            sum += x;
        } 
        scanf("%d", &m);
        for (int i = 0; i < m; ++ i) {
            scanf("%*d");
        }
        if (m == n) {
            puts(sum == 0 ? "0.00" : "inf");
        } else {
            double answer = (double)sum / (n - m);
            printf("%.2f\n", answer);
        }
    }
    return 0;
}
