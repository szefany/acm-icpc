#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 1000 + 10;

int a[N], pos[N], n;
int answer[N][2];

bool check() {
    for (int i = 1; i <= n; ++ i) {
        if (a[i] != i) {
            return false;
        }
    }
    return true;
}

void dfs(int u) {
    if (check()) {
        printf("%d\n", u);
        for (int i = u; i >= 1; -- i) {
            printf("%d %d\n", answer[i][0], answer[i][1]);
        }
        exit(0);
    }
    if (u == 3) {
        return;
    }
    for (int i = 1; i <= n; ++ i) {
        if (a[i] != i && abs(a[i] - a[i - 1]) + abs(a[i] - a[i + 1]) > 2) {
            int right = pos[i];
            answer[u + 1][0] = i;
            answer[u + 1][1] = right;
            std::reverse(a + i, a + right + 1);
            for (int j = i; j <= right; ++ j) {
                pos[a[j]] = j;
            }
            dfs(u + 1);
            std::reverse(a + i, a + right + 1);
            for (int j = i; j <= right; ++ j) {
                pos[a[j]] = j;
            }
        }
    }
    for (int i = n; i >= 1; -- i) {
        if (a[i] != i && abs(a[i] - a[i - 1]) + abs(a[i] - a[i + 1]) > 2) {
            int left = pos[i];
            answer[u + 1][0] = left;
            answer[u + 1][1] = i;
            std::reverse(a + left, a + i + 1);
            for (int j = left; j <= i; ++ j) {
                pos[a[j]] = j;
            }
            dfs(u + 1);
            std::reverse(a + left, a + i + 1);
            for (int j = left; j <= i; ++ j) {
                pos[a[j]] = j;
            }
        }
    }
}

int main() {
    freopen("input", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
        pos[a[i]] = i;
    }
    a[0] = a[n + 1] = 1 << 20;
    dfs(0);
    // dfs2(0);
    return 0;
}
