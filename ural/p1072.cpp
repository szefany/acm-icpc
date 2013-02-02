// ural 1072, Routing
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 100;

struct data {
    data () {}
    data (int _v, int _from): v(_v), from(_from) {}
    int v, from;
};

data queue[N * 10];
long long ip[N][6], subnet[N][6];
int counter[N];
bool g[N][N], visit[N];
int n;

int main () {
    scanf ("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf ("%d", &counter[i]);
        for (int j = 1; j <= counter[i]; ++ j) {
            for (int k = 24; k >= 0; k -= 8) {
                long long x;
                scanf ("%lld%*c", &x);
                ip[i][j] += x << k;
            }
            for (int k = 24; k >= 0; k -= 8) {
                long long x;
                scanf ("%lld%*c", &x);
                subnet[i][j] += x << k;
            }
        }
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = i + 1; j <= n; ++ j) {
            for (int k = 1; k <= counter[i] && !g[i][j]; ++ k) {
                for (int l = 1; l <= counter[j] && !g[i][j]; ++ l) {
                    if ((ip[i][k] & subnet[i][k]) == (ip[j][l] & subnet[j][l])) {
                        g[i][j] = g[j][i] = true;
                    }
                }
            }
        }
    }
    int vs, vt, pivot = -1;
    scanf ("%d%d", &vs, &vt);
    queue[1] = data (vs, 0), visit[vs] = true;
    for (int head = 1, tail = 1; head <= tail; ++ head) {
        int u = queue[head].v;
        if (u == vt) {
            pivot = head;
            break;
        }
        for (int i = 1; i <= n; ++ i) {
            if (!visit[i] && g[u][i]) {
                visit[i] = true;
                queue[++ tail] = data (i, head);
            }
        }
    }
    if (pivot == -1) {
        puts ("No");
        return 0;
    }
    vector<int> ans;
    for (; pivot != 0; pivot = queue[pivot].from) {
        ans.push_back (queue[pivot].v);
    }
    puts ("Yes");
    for (int i = ans.size() - 1; i >= 0; -- i) {
        printf ("%d%c", ans[i], i == 0 ? '\n' : ' ');
    }
    return 0;
}
