// UVA 11021, Tribles
#include <cstdio>

const int N = 2000;

double probability[N], a[N];
int n, m, k;

int main () {
    freopen ("input", "r", stdin);
    int test_count;
    scanf ("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        scanf ("%d%d%d", &n, &k, &m);
        for (int i = 0; i < n; ++ i) {
            scanf ("%lf", &a[i]);
        }
        probability[m] = a[0];
        for (int i = m - 1; i >= 1; -- i) {
            probability[i] = 0;
            double p = 1;
            for (int j = 0; j < n; ++ j, p *= probability[i + 1]) {
                probability[i] += a[j] * p;
            }
        }
        double answer;
        if (m == 0 && k > 0) {
            answer = 0;
        } else {
            answer = 1;
            for (int i = 0; i < k; ++ i) {
                answer *= probability[1];
            }
        }
        printf ("Case #%d: %.7f\n", t, answer);
    }
    return 0;
}
