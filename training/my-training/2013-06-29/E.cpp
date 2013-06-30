#include <cstdio>
#include <cstring>
#include <vector>

const int N = 200000 + 10;

std::vector<int> children[N];
long long dp[N][2], total;
int energy[N];
int n;

int func(int x) {
    int result = 0;
    while (x) {
        x >>= 1;
        result ++;
    }
    return result;
}

void dfs(int u) {
    for (int iter = 0; iter < (int)children[u].size(); ++ iter) {
        int v = children[u][iter];
        dfs(v);
    }
    dp[u][0] = 0;
    dp[u][1] = energy[u];
    for (int iter = 0; iter < (int)children[u].size(); ++ iter) {
        int v = children[u][iter];
        dp[u][0] += std::max(dp[v][0], dp[v][1] + func(energy[u]));
        dp[u][1] += dp[v][0] + func(energy[v]);
    }
}

int state[N];

void dfs2(int u, int s) {
    state[u] = s;
    if (s == 1) {
        for (int iter = 0; iter < (int)children[u].size(); ++ iter) {
            int v = children[u][iter];
            dfs2(v, 0);
        }
    } else {
        for (int iter = 0; iter < (int)children[u].size(); ++ iter) {
            int v = children[u][iter];
            int t = dp[v][1] + func(energy[u]) > dp[v][0];
            dfs2(v, t);
        }
    }
}

int main() {
    freopen("input", "r", stdin);
    scanf("%d%lld", &n, &total);
    int root = -1;
    for (int i = 1; i <= n; ++ i) {
        int x;
        scanf("%d%d", &x, energy + i);
        children[x].push_back(i);
        if (x == 0) {
            root = i;
        }
    }
    dfs(root);
    long long value = std::max(dp[root][0], dp[root][1]);
    long long number = total / value;
    if (number * value < total) {
        number ++;
    }
    printf("%lld %lld\n", value, number);
    dfs2(root, dp[root][1] > dp[root][0]);
    std::vector<int> answer;
    for (int i = 1; i <= n; ++ i) {
        if (state[i]) {
            answer.push_back(i);
        }
    }
    for (int i = 0; i < (int)answer.size(); ++ i) {
        printf("%d%c", answer[i], i + 1 == (int)answer.size() ? '\n' : ' ');
    }
    return 0;
}
