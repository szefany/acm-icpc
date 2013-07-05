#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

const int N = 100 + 10;
const int MOD = 1000000000 + 7;

std::vector<int> neighbors[N];
int n, m;

int length;
bool visit[N], is_one[N];

void dfs(int u) {
    visit[u] ++;
    length ++;
    for (int i = 0; i < neighbors[u].size(); ++ i) {
        int v = neighbors[u][i];
        if (!visit[v]) {
            dfs(v);
        }
    }
}

bool judge_cycle(int u, int p) {
    bool result = false;
    visit[u] = true;
    for (int i = 0; i < neighbors[u].size(); ++ i) {
        int v = neighbors[u][i];
        if (!visit[v]) {
            result |= judge_cycle(v, u);
        } else if (v != p) {
            result = true;
        }
    }
    return result;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++ i) {
        int x;
        scanf("%d", &x);
        neighbors[i].push_back(x);
        neighbors[x].push_back(i);
    }
    for (int i = 1; i <= n; ++ i) {
        std::sort(neighbors[i].begin(), neighbors[i].end());
        neighbors[i].resize(unique(neighbors[i].begin(), neighbors[i].end()) - neighbors[i].begin());
    }
    
    for (int i = 1; i <= n; ++ i) {
        if ((int)neighbors[i].size() > 2) {
            puts("0");
            return 0;
        }
    }
    if (n == 2) {
        puts("1");
        return 0;
    }
    
    bool cycle = false;
    memset(visit, 0, sizeof(visit));
    for (int i = 1; i <= n; ++ i) {
        if (!visit[i]) {
            cycle |= judge_cycle(i, -1);
        }
    }
    if (cycle) {
        memset(visit, 0, sizeof(visit));
        length = 0;
        dfs(1);
        int answer = length == n ? 2 : 0;
        printf("%d\n", answer);
        return 0;
    }
    
    memset(visit, 0, sizeof(visit));
    int two = 0;
    int one = 0;
    for (int i = 1; i <= n; ++ i) {
        if (!visit[i]) {
            length = 0;
            dfs(i);
            if (length == 1) {
                one ++;
                is_one[i] = true;
            } else {
                two ++;
            }
        }
    }
    
    if (!is_one[1]) {
        two --;
    } else {
        one --;
    }
    
    long long answer = 1;
    for (int i = 1; i <= one + two; ++ i) {
        (answer *= i) %= MOD;
    }
    for (int i = 1; i <= two; ++ i) {
        (answer *= 2) %= MOD;
    }
    if (!is_one[1]) {
        (answer *= 2) %= MOD;
    }
    std::cout << answer << std::endl;
    return 0;
}
