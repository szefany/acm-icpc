#include <cstdio>
#include <cstring>
#include <iostream>

typedef int Matrix[2][2];

const Matrix args = {{1, 1}, {1, 0}};

struct data {
    Matrix matrix;
    int n, m;
    data(): n(0), m(0) {
        memset(matrix, 0, sizeof(matrix));
    }
    data(const Matrix &other, int n, int m): n(n), m(m) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                matrix[i][j] = other[i][j];
            }
        }
    }
    void diagonal(int size) {
        n = m = size;
        for (int i = 0; i < size; ++ i) {
            for (int j = 0; j < size; ++ j) {
                matrix[i][j] = i == j ? 1 : 0;
            }
        }
    }
};

Matrix buffer;
void multi(data &base, data &other, int MOD) {
    memset(buffer, 0, sizeof(buffer));
    for (int i = 0; i < base.n; ++ i) {
        for (int j = 0; j < base.m; ++ j) {
            if (base.matrix[i][j]) {
                for (int k = 0; k < other.m; ++ k) {
                    buffer[i][k] += (long long)base.matrix[i][j] * other.matrix[j][k] % MOD;
                    if (buffer[i][k] > MOD) {
                        buffer[i][k] -= MOD;
                    }
                }
            }
        }
    }
    base = data(buffer, base.n, other.m);
}

void power(data &base, long long times, int MOD) {
    data result;
    result.diagonal(base.n);
    while (times) {
        int x = times & 1;
        if (x) {
            multi(result, base, MOD);
        }
        multi(base, base, MOD);
        times >>= 1;
    }
    base = result;
}

const int MOD = 1000000000 + 7;

int power(int x, int t, int MOD) {
    int result = 1;
    while (t) {
        if (t & 1) {
            result = (long long)result * x % MOD;
        }
        x = (long long)x * x % MOD;
        t >>= 1;
    }
    return result;
}

int main() {
    freopen("input", "r", stdin);
    int a, b, n;
    while (std::cin >> a >> b >> n) {
        if (n == 0) {
            std::cout << a << '\n';
            continue;
        } else if (n == 1) {
            std::cout << b << '\n';
            continue;
        }
        data temp(args, 2, 2);
        power(temp, n - 2, MOD - 1);

        Matrix g = {{1, 0}, {1, 0}};
        data init(g, 2, 2);
        multi(temp, init, MOD - 1);

        int temp1 = power(a, temp.matrix[1][0], MOD);
        int temp2 = power(b, temp.matrix[0][0], MOD);
        int answer = (long long)temp1 * temp2 % MOD;
        printf("%d\n", answer);
    }
    return 0;
}
