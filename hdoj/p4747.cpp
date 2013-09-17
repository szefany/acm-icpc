#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using std::min;
using std::max;

const int N = 200000 + 10;

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;
std::vector<Pair> positions;

bool visit[N];
int a[N], next[N], mex[N];
int n;

const int S = N << 2;

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

long long sum[S];
int max_value[S], mark[S], length[S];

void update(int u) {
    sum[u] = sum[L(u)] + sum[R(u)];
    max_value[u] = max(max_value[L(u)], max_value[R(u)]);
}

void build(int u, int l, int r) {
    if (l > r) {
        return;
    }
    mark[u] = -1;
    length[u] = r - l + 1;
    if (l == r) {
        sum[u] = max_value[u] = mex[l];
        return;
    }
    int m = l + r >> 1;
    build(L(u), l, m);
    build(R(u), m + 1, r);
    update(u);
}

void push_down(int u) {
    if (mark[u] != -1) {
        max_value[L(u)] = max_value[R(u)] = mark[L(u)] = mark[R(u)] = mark[u];
        sum[L(u)] = (long long)mark[u] * length[L(u)];
        sum[R(u)] = (long long)mark[u] * length[R(u)];
        mark[u] = -1;
    }
}

int find_leftmost(int u, int l, int r, int a, int b, int x) {
    if (a > r || b < l || max_value[u] < x) {
        return INT_MAX;
    }
    if (l == r) {
        return l;
    }
    push_down(u);
    int m = l + r >> 1;
    int result = find_leftmost(L(u), l, m, a, b, x);
    if (result <= n) {
        return result;
    }
    return find_leftmost(R(u), m + 1, r, a, b, x);
}

void insert(int u, int l, int r, int a, int b, int x) {
    if (a > r || b < l) {
        return;
    }
    if (a <= l && b >= r) {
        max_value[u] = x;
        sum[u] = (long long)x * length[u];
        mark[u] = x;
        return;
    }
    push_down(u);
    int m = l + r >> 1;
    insert(L(u), l, m, a, b, x);
    insert(R(u), m + 1, r, a, b, x);
    update(u);
}

long long query(int u, int l, int r, int a, int b) {
    if (a > r || b < l) {
        return 0;
    }
    if (a <= l && b >= r) {
        return sum[u];
    }
    push_down(u);
    int m = l + r >> 1;
    return query(L(u), l, m, a, b) + query(R(u), m + 1, r, a, b);
}

int main() {
    while (scanf("%d", &n) != EOF && n > 0) {
        positions.clear();
        memset(visit, 0, sizeof(visit));
        for (int i = 1, now = 0; i <= n; ++ i) {
            scanf("%d", a + i);
            a[i] = min(a[i], n + 1);
            positions.push_back(make_pair(a[i], i));
            visit[a[i]] = true;
            while (visit[now]) {
                now ++;
            }
            mex[i] = now;
        }
        std::sort(positions.begin(), positions.end());
        for (int i = 0; i < positions.size(); ++ i) {
            if (i + 1 < positions.size() && positions[i].first == positions[i + 1].first) {
                next[positions[i].second] = positions[i + 1].second;
            } else {
                next[positions[i].second] = n + 1;
            }
        }
        build(1, 1, n);
        long long result = 0;
        for (int i = 1; i <= n; ++ i) {
            result += query(1, 1, n, i, n);
            int x = find_leftmost(1, 1, n, i + 1, n, a[i]);
            int y = next[i];
            if (x <= y - 1) {
                insert(1, 1, n, x, y - 1, a[i]);
            }
        }
        std::cout << result << '\n';
    }
    return 0;
}
