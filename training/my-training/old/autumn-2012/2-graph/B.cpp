#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 105;

vector<int> neighbors[N], children[N];
bool known[N][N], vis[N];
int color[N], counter[N][2], father[N], f[N][N * 3], from[N][N * 3];
int n, blacks, number;

bool dfs (int u, int c, int total) {
    color[u] = c;
    vis[u] = true;
    children[total].push_back (u);
    number ++;
    blacks += c == 1;
    for (int i = 0; i < neighbors[u].size(); ++ i) {
        int v = neighbors[u][i];
        if (!vis[v]) {
            if (!dfs (v, c ^ 1, total)) return false;
        }
        else if (color[v] != (c ^ 1)) {
            return false;
        }
    }
    return true;
}

int main () {
    freopen ("input.txt", "r", stdin);
    scanf ("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        int x;
        while (scanf ("%d", &x) != EOF && x) {
            known[i][x] = 1;
        }
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            if (i == j) continue;
            if (!known[i][j] || !known[j][i]) {
                neighbors[i].push_back (j);
                neighbors[j].push_back (i);
            }
        }
    }
    bool exist_answer = true;
    memset (color, -1, sizeof (color));
    int total = 0;
    for (int i = 1; i <= n && exist_answer; ++ i) {
        if (color[i] == -1) {
            total ++;
            number = 0;
            blacks = 0;
            exist_answer &= dfs (i, 1, total);
            counter[total][1] = blacks;
            counter[total][0] = number - blacks;
        }
    }
    if (!exist_answer) {
        puts ("No solution");
        return 0;
    }
    f[0][0 + N] = true;
    for (int i = 1; i <= total; ++ i) {
        for (int j = -N; j <= N; ++ j) {
            if (f[i - 1][j - counter[i][0] + counter[i][1] + N]) {
                f[i][j + N] = true;
                from[i][j + N] = 0;
            }
            if (f[i - 1][j - counter[i][1] + counter[i][0] + N]) {
                f[i][j + N] = true;
                from[i][j + N] = 1;
            }
        }
    }
    vector<int> ans[2];
    int result = N;
    for (; !f[total][result]; result ++);
    for (int i = total; i > 0; -- i) {
        int x = from[i][result];
        for (int j = 0; j < children[i].size(); ++ j) {
            int v = children[i][j];
            ans[color[v] ^ x].push_back (v);
        }
        result = result - counter[i][x] + counter[i][x ^ 1];
    }
    for (int i = 0; i < 2; ++ i) {
        printf ("%d%c", ans[i].size(), ans[i].size() == 0 ? '\n' : ' ');
        for (int j = 0; j < ans[i].size(); ++ j) {
            printf ("%d%c", ans[i][j], j == ans[i].size() - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
