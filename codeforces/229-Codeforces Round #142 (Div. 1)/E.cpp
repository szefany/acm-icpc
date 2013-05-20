#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

const int N = 1000 + 1;

std::vector<int> elements[N], all_elements;
double prob[N][N], comb[N][N];
int n, m;

int main() {
    comb[0][0] = 1;
    for (int i = 1; i < N; ++ i) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++ j) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
        }
    }
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++ i) {
        int number;
        scanf("%d", &number);
        while (number --) {
            int x;
            scanf("%d", &x);
            elements[i].push_back(x);
            all_elements.push_back(x);
        }
        std::sort(elements[i].begin(), elements[i].end(), std::greater<int>());
    }
    std::sort(all_elements.begin(), all_elements.end(), std::greater<int>());
    int left = 0, total = 0;
    for (int i = 1, iter; i <= m; ++ i) {
        for (iter = 0; iter < elements[i].size() && elements[i][iter] > all_elements[n - 1]; ++ iter) {
            total ++;
        }
        if (iter < elements[i].size() && elements[i][iter] == all_elements[n - 1]) {
            left ++;
        }
    }
    total = n - total;

    prob[0][0] = 1;
    for (int i = 1; i <= m; ++ i) {
        int size = elements[i].size();
        int must = 0, optional = 0;
        for (int iter = 0; iter < size && elements[i][iter] >= all_elements[n - 1]; ++ iter) {
            must += elements[i][iter] > all_elements[n - 1];
            optional += elements[i][iter] == all_elements[n - 1];
        }
        for (int j = 0; j <= total; ++ j) {
            if (optional == 0) {
                prob[i][j] += prob[i - 1][j] / comb[size][must];
            } else {
                if (left - 1 >= 0 && left >= total - j) {
                    double p = comb[left - 1][total - j] / comb[left][total - j];
                    prob[i][j] += p * prob[i - 1][j] / comb[size][must];
                }
                if (left - 1 >= 0 && j >= 1 && left >= total - (j - 1)) {
                    double p = 1 - comb[left - 1][total - (j - 1)] / comb[left][total - (j - 1)];
                    prob[i][j] += p * prob[i - 1][j - 1] / comb[size][must + 1];
                }
            }
        }
        left -= optional;
    }
    printf("%.10f\n", prob[m][total]);
    return 0;
}
