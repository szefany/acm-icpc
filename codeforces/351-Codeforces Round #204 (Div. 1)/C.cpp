#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 50;

int a[N], b[N], transfer[N][N];
int n, m;
int INF;

int buffer[N][N];
void get_transfer(int start) {
    memset(buffer, 127, sizeof(buffer));
    INF = buffer[0][0];
    buffer[0][start] = 0;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 0; j < n + n; ++ j) {
            if (j) {
                buffer[i][j] = std::min(buffer[i][j], buffer[i - 1][j - 1] + a[i]);
            }
            if (j + 1 < n + n) {
                buffer[i][j] = std::min(buffer[i][j], buffer[i - 1][j + 1] + b[i]);
            }
        }
    }
    memcpy(transfer + start, buffer + n, sizeof(transfer[0]));
}

struct Matrix {
    int element[N][N];

    Matrix() {
        memset(element, 127, sizeof(element));
    }

    const int* operator [] (int i) const {
        return element[i];
    }

    int* operator [] (int i) {
        return element[i];
    }

    void diagonal() {
        for (int i = 0; i < N; ++ i) {
            element[i][i] = 0;
        }
    }
};

void multi(Matrix &a, const Matrix &b) {
    memset(buffer, 127, sizeof(buffer));
    for (int i = 0; i < N; ++ i) {
        for (int j = 0; j < N; ++ j) {
            if (a[i][j] != INF) {
                for (int k = 0; k < N; ++ k) {
                    if (b[j][k] != INF) {
                        buffer[i][k] = std::min(buffer[i][k], a[i][j] + b[j][k]);
                    }
                }
            }
        }
    }
    memcpy(a.element, buffer, sizeof(buffer));
}

void power(Matrix &a, int times) {
    Matrix base = a;
    Matrix result;
    result.diagonal();
    while (times) {
        if (times & 1) {
            multi(result, base);
        }
        multi(base, base);
        times >>= 1;
    }
    a = result;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", b + i);
    }
    for (int i = 0; i < n + n; ++ i) {
        get_transfer(i);
    }

    Matrix base;
    memcpy(base.element, transfer, sizeof(transfer));
    power(base, m);
    printf("%d\n", base[0][0]);
    return 0;
}
