#include <cstdio>
#include <cstring>
#include <iostream>

typedef int Matrix[2][2];

const int table[4] = {1000000007, 222222224, 183120, 240};
const Matrix args = {{3, 1}, {1, 0}};
const Matrix init = {{1, 0}, {0, 0}};

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

long long solve(long long n, int MOD) {
    if (n < 3) {
        return n == 2 ? 3 : n; 
    }
    data base(args, 2, 2), target(init, 2, 1);
    power(base, n - 1, MOD);
    multi(base, target, MOD);
    return base.matrix[0][0];
}

int main() {
    /*
    long long a[2] = {0, 1};
    for (int i = 2; ; ++ i) {
        long long temp = (a[0] + a[1] * 3) % MOD;
        if (temp == 1 && a[1] == 0) {
            printf ("%d\n", i - 1);
            break;
        }
        a[0] = a[1], a[1] = temp;
    }
    */
    freopen("input", "r", stdin);
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        long long n;
        std::cin >> n;
        for (int i = 3; i >= 0; -- i) {
            n = solve(n, table[i]);
        }
        std::cout << n << '\n';
    }
    return 0;
}
