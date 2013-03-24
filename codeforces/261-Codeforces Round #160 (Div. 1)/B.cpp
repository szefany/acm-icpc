#include <cstdio>
#include <iostream>
#include <iomanip>

const int N = 50 + 1;

typedef unsigned long long Long;

Long number[N][N];
long double multi[N];
int elements[N];
int n, m;

int main() {
    scanf("%d", &n);
    number[0][0] = 1;
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &elements[i]);
    }
    scanf("%d", &m);

    multi[0] = 1;
    for (int i = 1; i <= n; ++ i) {
        multi[i] = multi[i - 1] * i;
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = n; j >= 1; -- j) {
            for (int k = elements[i]; k <= m; ++ k) {
                number[j][k] += number[j - 1][k - elements[i]];
            }
        }
    }

    long double answer = 0;
    for (int i = 1; i <= n; ++ i) {
        Long counter = 0;
        for (int j = 0; j <= m; ++ j) {
            counter += number[i][j];
        }
        answer += counter * multi[i] * multi[n - i];
    }
    std::cout << std::setprecision(10) << answer / multi[n] << std::endl;
    return 0;
}
