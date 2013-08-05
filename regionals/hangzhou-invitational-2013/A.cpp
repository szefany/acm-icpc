#include <cstdio>
#include <cstring>

const int N = 200 + 10;

double dp[N], buffer[N];
int count[N];
int n, m, l, r;

struct Matrix {
    static const int N = 200 + 10;
    double element[N][N];
    int n;
    Matrix(int size = 0) {
        n = size;
        memset(element, 0, sizeof(element));
    }

    double* operator [] (int i) {
        return element[i];
    }

    const double* operator [] (int i) const {
        return element[i];
    }

    void print() {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                printf("%.2f ", element[i][j]);
            } puts("");
        }
    }
    void diagonal(int size) {
        n = size;
        memset(element, 0, sizeof(element));
        for (int i = 0; i < n; ++ i) {
            element[i][i] = 1;
        }
    }
};

Matrix buffer2;
void multi(Matrix &a, Matrix &b) {
    buffer2.n = n;
    memset(buffer2.element, 0, sizeof(buffer2.element));

    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            buffer2[0][i] += a[0][j] * b[j][i];
        }
    }
    for (int i = 1; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            int prev = j == 0 ? n - 1 : j - 1;
            buffer2[i][j] = buffer2[i - 1][prev];
        }
    }
    a = buffer2;
}

Matrix result;
void power(Matrix &base, int times) {
    result.diagonal(n);
    while (times) {
        int x = times & 1;
        if (x) {
            multi(result, base);
        }
        multi(base, base);
        times >>= 1;
    }
    base = result;
}

int main() {
    while (scanf("%d%d%d%d", &n, &m, &l, &r) != EOF) {
        if (n + m + l + r == 0) {
            break;
        }
        memset(count, 0, sizeof(count));
        for (int i = 1; i <= m; ++ i) {
            int x;
            scanf("%d", &x);
            count[x] ++;
        }
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (int i = 1; i <= 100; ++ i) {
            if (count[i] == 0) {
                continue;
            }
            Matrix temp(n);
            for (int j = 0; j < n; ++ j) {
                temp[j][(j + i) % n] += 0.5;
                temp[j][((j - i) % n + n) % n] += 0.5;
            }
            power(temp, count[i]);
            memcpy(buffer, dp, sizeof(dp));
            for (int j = 0; j < n; ++ j) {
                dp[j] = 0;
                for (int k = 0; k < n; ++ k) {
                    dp[j] += temp[j][k] * buffer[k];
                }
            }
        }
        double answer = 0;
        for (int i = l - 1; i < r; ++ i) {
            answer += dp[i];
        }
        printf("%.4f\n", answer);
    }
    return 0;
}
