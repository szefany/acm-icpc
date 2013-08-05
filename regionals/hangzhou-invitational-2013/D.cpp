#include <cstdio>
#include <cstring>
#include <map>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 50000 + 10;

struct HashMap {
    static const int SIZE = 97;
    double ZERO;

    int first[SIZE], key[SIZE], next[SIZE], size;
    double value[SIZE];

    void clear() {
        size = ZERO = 0;
        memset(first, 0, sizeof(first));
    }
    void insert(int k, double v) {
        int hash = k % SIZE;
        for (int iter = first[hash]; iter; iter = next[iter]) {
            if (key[iter] == k) {
                value[iter] = v;
                return;
            }
        }
        size ++;
        key[size] = k;
        value[size] = v;
        next[size] = first[hash];
        first[hash] = size;
    }
    bool find(int k) {
        int hash = k % SIZE;
        for (int iter = first[hash]; iter; iter = next[iter]) {
            if (key[iter] == k) {
                return true;
            }
        }
        return false;
    }
    double& operator [] (int k) {
        int hash = k % SIZE;
        for (int iter = first[hash]; iter; iter = next[iter]) {
            if (key[iter] == k) {
                return value[iter];
            }
        }
        return ZERO;
    }
};
HashMap transfer[N];

double p[N][7], answer[N];
int c[N][7];
int n, m;

int main() {
    while (scanf("%d%d", &n, &m) != EOF && n + m > 0) {
        memset(answer, 0, sizeof(answer));
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= n; ++ i) {
            transfer[i].clear();
            int row = 0;
            for (int j = 1; j <= m; ++ j) {
                scanf("%d", &c[i][j]);
                row += c[i][j];
            }
            if (i == n) {
                transfer[i].insert(i, 1);
                transfer[i].insert(n + 1, 0);
            } else {
                double sum = 0;
                for (int j = i - 1; j > 0 && i - j <= m; -- j) {
                    double temp = 0.3 * c[i][i - j] / (1 + row);
                    transfer[i].insert(j, temp);
                    sum += temp;
                }
                for (int j = i + 1; j <= n && j - i <= m; ++ j) {
                    double temp = 0.7 * c[i][j - i] / (1 + row);
                    transfer[i].insert(j, temp);
                    sum += temp;
                }
                transfer[i].insert(i, -sum);
                transfer[i].insert(n + 1, -1);
            }
        }
        /*
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= n + 1; ++ j) {
                printf("%.2f ", transfer[i][j]);
            } puts("");
        }
        */
        for (int i = 1; i <= n; ++ i) {
            double current = transfer[i][i];
            for (int j = i; j <= n && transfer[i].find(j); ++ j) {
                transfer[i][j] /= current;
            }
            transfer[i][n + 1] /= current;
            for (int j = i + 1; j <= n && transfer[j].find(i); ++ j) {
                double temp = transfer[j][i];
                for (int k = i; k <= n && transfer[j].find(k) && transfer[i].find(k); ++ k) {
                    transfer[j][k] -= transfer[i][k] * temp;
                }
                transfer[j][n + 1] -= transfer[i][n + 1] * temp;
            }
        }
        
        for (int i = n; i >= 1; -- i) {
            double &result = transfer[i][n + 1];
            for (int j = 1; j <= transfer[i].size; ++ j) {
                int x = transfer[i].key[j];
                double y = transfer[i].value[j];
                if (x != n + 1) {
                    result -= answer[x] * y;
                }
            }
            answer[i] = result / transfer[i][i];
        }
        printf("%.2f\n", answer[1]);
    }
    return 0;
}
