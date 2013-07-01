#include <cstdio>
#include <algorithm>
#include <iostream>
#include <iomanip>

const int N = 2000 + 10;
const long double INF = 1E20;
const long double EPS = 1E-14;

struct data {
    int score_small, score_large, time_small, time_large;
    long double prob;
    void input() {
        std::cin >> score_small >> score_large >> time_small >> time_large >> prob;
        // scanf("%d%d%d%d%Lf", &score_small, &score_large, &time_small, &time_large, &prob);
        prob = 1 - prob;
    }
    bool operator < (const data &other) const {
        return time_large * (1 - prob) * other.prob < other.time_large * (1 - other.prob) * prob;
    }
} problems[N];

long double score[N][N], penalty[N][N];
int n, m;

int sgn(long double x) {
    return x < -EPS ? -1 : x > EPS;
}

void judge(long double &dest_1, long double &dest_2, long double src_1, long double src_2) {
    int flag = sgn(src_1 - dest_1);
    if (flag > 0 || flag == 0 && src_2 < dest_2) {
        dest_1 = src_1;
        dest_2 = src_2;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        problems[i].input();
    }
    std::sort(problems + 1, problems + n + 1);

    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j <= m; ++ j) {
            score[i][j] = -INF;
            penalty[i][j] = INF;
        }
    }

    score[0][0] = penalty[0][0] = 0;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 0; j <= m; ++ j) {
            score[i][j] = score[i - 1][j];
            penalty[i][j] = penalty[i - 1][j];
            if (j >= 1) {
                judge(score[i][j], penalty[i][j], score[i][j - 1], penalty[i][j - 1]);
            }
            long double p, s;
            int t;
            s = problems[i].score_small;
            t = problems[i].time_small;
            if (j >= t) {
                judge(score[i][j], penalty[i][j], score[i - 1][j - t] + s, penalty[i - 1][j - t] + t);
            }

            p = problems[i].prob;
            s = problems[i].score_small + p * problems[i].score_large;
            t = problems[i].time_small + problems[i].time_large;
            if (j >= t) {
                judge(score[i][j], penalty[i][j], score[i - 1][j - t] + s, \
                    (penalty[i - 1][j - t] + problems[i].time_small) * (1 - p) + p * j);
            }
        }
    }
    std::cout << std::fixed << std::setprecision(10) << score[n][m] << " " << penalty[n][m] << '\n';
    // printf("%.10Lf %.10Lf\n", score[n][m], penalty[n][m]);
    return 0;
}
