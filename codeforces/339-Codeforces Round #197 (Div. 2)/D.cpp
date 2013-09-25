#include <cstdio>
#include <cstring>

const int N = 150000;

int elements[N];

const int S = N << 2;

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

int depth[S], value[S];
int n, m;

void update(int u) {
    if (depth[u] & 1) {
        value[u] = value[L(u)] | value[R(u)];
    } else {
        value[u] = value[L(u)] ^ value[R(u)];
    }
}

void build(int u, int l, int r, int d) {
    depth[u] = d;
    if (l == r) {
        value[u] = elements[l];
    } else {
        int m = l + r >> 1;
        build(L(u), l, m, d - 1);
        build(R(u), m + 1, r, d - 1);
        update(u);
    }
}

void modify(int u, int l, int r, int x, int v) {
    if (l == r) {
        value[u] = v;
    } else {
        int m = l + r >> 1;
        if (x <= m) {
            modify(L(u), l, m, x, v);
        } else {
            modify(R(u), m + 1, r, x, v);
        }
        update(u);
    }
}

int main() {
    freopen("input", "r", stdin);
    int d;
    scanf("%d%d", &d, &m);
    n = 1 << d;
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", elements + i);
    }
    build(1, 1, n, d);
    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        modify(1, 1, n, a, b);
        printf("%d\n", value[1]);
    }
    return 0;
}
