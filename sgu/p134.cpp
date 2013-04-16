#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 20000;

std::vector<int> neighbors[N], indices;

int n, answer;
int size[N];

void dfs(int u, int p) {
    size[u] = 1;
    for (int i = 0; i < neighbors[u].size(); ++ i) {
        int v = neighbors[u][i];
        if (v != p) {
            dfs(v, u);
            size[u] += size[v];
        }
    }
    int temp = n - size[u];
    for (int i = 0; i < neighbors[u].size(); ++ i) {
        int v = neighbors[u][i];
        if (v != p) {
            temp = std::max(temp, size[v]);
        }
    }
    if (temp < answer) {
        answer = temp;
        indices.clear();
        indices.push_back(u);
    } else if (temp == answer) {
        indices.push_back(u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        u --, v --;
        neighbors[u].push_back(v);
        neighbors[v].push_back(u);
    }
    answer = 1 << 30;
    dfs(0, -1);
    std::sort(indices.begin(), indices.end());
    printf("%d %d\n", answer, (int)indices.size());
    for (int i = 0; i < indices.size(); ++ i) {
        printf("%d%c", indices[i] + 1, i + 1 == indices.size() ? '\n' : ' ');
    }
    return 0;
}
