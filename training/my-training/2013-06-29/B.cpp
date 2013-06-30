#include <cstdio>
#include <vector>

const int N = 200000 + 10;

std::vector<int> children[N];
long long sum[N], a[N], b[N];
int n;

void dfs(int u, int p) {
    sum[u] = b[u];
    for (int iter = 0; iter < (int)children[u].size(); ++ iter) {
        int v = children[u][iter];
        dfs(v, u);
        sum[u] += sum[v];
    }
}

int main() {
    freopen("input", "r", stdin);
    scanf("%d%lld", &n, &a[0]);
    for (int i = 1; i <= n; ++ i) {
        int x;
        scanf("%d%lld%lld", &x, a + i, b + i);
        children[x].push_back(i);
    }

    dfs(0, -1);
    long long answer = -1;
    int id = -1;
    for (int i = 0; i <= n; ++ i) {
        if (sum[i] + a[i] > answer) {
            answer = sum[i] + a[i];
            id = i;
        }
    }
    printf("%d\n", id);
    return 0;
}
