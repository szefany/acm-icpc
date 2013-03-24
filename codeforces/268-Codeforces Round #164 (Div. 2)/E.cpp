#include <cstdio>
#include <algorithm>

const int N = 50000;

int length[N], probability[N], rank[N];
int n;

bool cmp(int x, int y) {
    return (100 - probability[y]) * length[x] * probability[x] > (100 - probability[x]) * length[y] * probability[y];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        rank[i] = i;
        scanf("%d%d", &length[i], &probability[i]);
    }
    std::sort(rank, rank + n, cmp);
    double answer = 0, current = 0;
    for (int i = 0; i < n; ++ i) {
        int u = rank[i];
        answer += length[u] + (double)(100 - probability[u]) / 100 * current;
        current += (double)probability[u] / 100 * length[u];
    }
    printf("%.10f\n", answer);
    return 0;
}
