#include <cstdio>
#include <algorithm>

const int N = 100000;
const int INF = 1 << 29;

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

Pair from[N];
int left[N], right[N], order[N], minimal[N];
int n, m;

bool by_right(int a, int b) {
    return right[a] < right[b];
}

bool by_left(int a, int b) {
    return left[a] < left[b];
}

int answer[N];

int main() {
    scanf("%d", &m);
    while (scanf("%d%d", &left[n], &right[n]) != EOF) {
        if (left[n] == 0 && right[n] == 0) {
            break;
        }
        // left[n] = std::max(0, left[n]);
        // right[n] = std::min(m, right[n]);
        order[n] = n;
        n ++;
    }
    std::sort(order, order + n, by_right);
    for (int i = 1; i <= m; ++ i) {
        minimal[i] = INF;
    }
    minimal[0] = 0;
    for (int i = 0; i < n; ++ i) {
        int u = order[i];
        int x = INF;
        int y = 0;
        int l = std::max(0, left[u]);
        int r = std::min(m, right[u]);
        for (int j = l; j < r; ++ j) {
            if (minimal[j] + 1 < x) {
                x = minimal[j] + 1;
                y = j;
            }
        }
        for (int j = l + 1; j <= r; ++ j) {
            if (x < minimal[j]) {
                minimal[j] = x;
                from[j] = make_pair(u, y);
            }
        }
    }
    if (minimal[m] == INF) {
        puts("No solution");
    } else {
        printf("%d\n", minimal[m]);
        int length = 0;
        for (int i = m; i; i = from[i].second) {
            answer[length ++] = from[i].first;
        }
        std::sort(answer, answer + length, by_left);
        for (int i = 0; i < length; ++ i) {
            printf("%d %d\n", left[answer[i]], right[answer[i]]);
        }
    }
    return 0;
}
