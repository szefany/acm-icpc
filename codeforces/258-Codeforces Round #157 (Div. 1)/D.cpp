#include <cstdio>

const int N = 1000 + 1;

double probability[N][N], memory[N], sum[N], dp[N][2];
int element[N];
int n, m;

int main() {
    freopen("input", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", &element[i]);
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            probability[i][j] = element[i] > element[j];
        }
    }
    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --, b --;
        for (int i = 0; i < n; ++ i) {
            if (i == a || i == b) {
                continue;
            }
            probability[a][i] = probability[b][i] = (probability[a][i] + probability[b][i]) * 0.5;
            probability[i][a] = probability[i][b] = (probability[i][a] + probability[i][b]) * 0.5;
        }
        probability[a][b] = probability[b][a] = 0.5;
    }
    double answer = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            answer += probability[i][j];
        }
    }
    printf("%.10f\n", answer);
    /*
    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        for (int i = 1; i <= n; ++ i) {
            memory[i] = probability[a][i];
        }
        for (int i = 1; i <= n; ++ i) {
            probability[a][i] = probability[a][i] * 0.5 + probability[b][i] * 0.5;
        }
        for (int i = 1; i <= n; ++ i) {
            probability[b][i] = probability[b][i] * 0.5 + memory[i] * 0.5;
        }
    }

    
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            printf("%.2f ", probability[i][j]);
        } puts("");
    }
    
    double answer = 0;
    for (int i = n; i >= 1; -- i) {
        for (int j = 1; j <= n; ++ j) {
            answer = sum[j - 1];
        }
        for (int j = 1; j <= n; ++ j) {
            dp[j][0] *= 1 - probability[i][j];
            dp[j][1] = 1 - dp[j][0];
            sum[j] += dp[j][1];
        }
    }
    printf("%.10f\n", answer);
    */
    return 0;
}
