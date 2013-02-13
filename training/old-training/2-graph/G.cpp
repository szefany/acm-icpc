#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 500005;

vector<int> children[N], ans;
int f[N][2], kind[N];
int n;

void solve (int u) {
    for (int i = 0; i < children[u].size (); ++ i) {
        solve (children[u][i]);
    }
    f[u][1] = 1;
    for (int i = 0; i < children[u].size (); ++ i) {
        int v = children[u][i];
        f[u][1] += f[v][0];
    }
    f[u][0] = f[u][1] - 1, kind[u] = 0;
    for (int i = 0; i < children[u].size (); ++ i) {
        int v = children[u][i];
        if (f[u][1] - 1 + f[v][1] - f[v][0] > f[u][0]) {
            f[u][0] = f[u][1] - 1 + f[v][1] - f[v][0];
            kind[u] = v;
        }
    }
    return;
}

void dfs (int u, bool flag) {
    if (flag) {
        ans.push_back (u);
        for (int i = 0; i < children[u].size (); ++ i) {
            dfs (children[u][i], false);
        }
    }
    else {
        for (int i = 0; i < children[u].size (); ++ i) {
            int v = children[u][i];
            dfs (v, v == kind[u]);
        }
    }
}

int main () {
    freopen ("input.txt", "r", stdin);
    int testCount;
    scanf ("%d", &testCount);
    while (testCount --) {
        scanf ("%d", &n);
        for (int i = 1; i <= n; ++ i) {
            children[i].clear ();
        }
        for (int i = 2; i <= n; ++ i) {
            int x;
            scanf ("%d", &x);
            children[x].push_back (i);
        }
        solve (1);
        printf ("%d000\n", f[1][0]);
        ans.clear ();
        dfs (1, 0);
        sort (ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); ++ i) {
            printf ("%d%c", ans[i], i == ans.size () - 1 ? '\n' : ' ');
        }
        puts ("");
    }
    return 0;
}
