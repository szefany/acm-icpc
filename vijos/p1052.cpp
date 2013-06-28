#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

const int N = 100 + 10;

long double matrix[N][N], answer[N];
int n;

int main() {
    freopen("input", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n + 1; ++ j) {
            std::cin >> matrix[i][j];
        }
    }
    for (int i = 1; i <= n; ++ i) {
        int pivot = i;
        for (int k = i + 1; k <= n; ++ k) {
            if (fabs(matrix[k][i]) > fabs(matrix[pivot][i])) {
                pivot = k;
                break;
            }
        }
        if (pivot != i) {
            for (int j = i; j <= n + 1; ++ j) {
                std::swap(matrix[i][j], matrix[pivot][j]);
            }
        }
        for (int j = n + 1; j >= i; -- j) {
            matrix[i][j] /= matrix[i][i];
        }
        for (int j = i + 1; j <= n; ++ j) {
            for (int k = n + 1; k >= i; -- k) {
                matrix[j][k] -= matrix[i][k] * matrix[j][i];
            }
        }
    }
    for (int i = n; i >= 1; -- i) {
        for (int j = i + 1; j <= n; ++ j) {
            matrix[i][n + 1] -= matrix[i][j] * answer[j];
        }
        answer[i] = matrix[i][n + 1] / matrix[i][i];
    }
    for (int i = 1; i <= n; ++ i) {
        int result = round(answer[i]);
        std::cout << result << (i == n ? '\n' : ' ');
    }
    return 0;
}
