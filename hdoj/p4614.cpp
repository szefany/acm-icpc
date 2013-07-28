#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 60000;

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

int sum[N << 2], length[N << 2], cover[N << 2];
int n, m;

void build(int u, int l, int r) {
    sum[u] = cover[u] = 0;
    length[u] = r - l + 1;
    if (l < r) {
        int m = l + r >> 1;
        build(L(u), l, m);
        build(R(u), m + 1, r);
    }
}

void push_down(int u) {
    if (cover[u] != -1) {
        cover[L(u)] = cover[R(u)] = cover[u];
        sum[L(u)] = cover[u] * length[L(u)];
        sum[R(u)] = cover[u] * length[R(u)];
        cover[u] = -1;
    }
}

int get_sum(int u, int l, int r, int a, int b) {
    if (a > r || b < l) {
        return 0;
    }
    if (a <= l && b >= r) {
        return sum[u];
    }
    push_down(u);
    int m = l + r >> 1;
    return get_sum(L(u), l, m, a, b) + get_sum(R(u), m + 1, r, a, b);
}

void insert(int u, int l, int r, int a, int b, int v) {
    if (a > r || b < l) {
        return;
    }
    if (a <= l && b >= r) {
        cover[u] = v;
        sum[u] = length[u] * v;
        return;
    }
    push_down(u);
    int m = l + r >> 1;
    insert(L(u), l, m, a, b, v);
    insert(R(u), m + 1, r, a, b, v);
    sum[u] = sum[L(u)] + sum[R(u)];
}

int main() {
    int test;
    scanf("%d", &test);
    while (test --) {
        scanf("%d%d", &n, &m);
        build(1, 0, n - 1);
        while (m --) {
            int type;
            scanf("%d", &type);
            if (type == 1) {
                int a, b;
                scanf("%d%d", &a, &b);
                int s = get_sum(1, 0, n - 1, a, n - 1);
                if (n - a - s == 0) {
                    puts("Can not put any one.");
                } else {
                    b = std::min(b, n - a - s);
                    int l = a, r = n - 1;
                    while (l < r) {
                        int m = l + r >> 1;
                        if (m - a + 1 - get_sum(1, 0, n - 1, a, m) >= b) {
                            r = m;
                        } else {
                            l = m + 1;
                        }
                    }
                    int end = l;

                    l = a, r = end;
                    while (l < r) {
                        int m = l + r >> 1;
                        if (m - a + 1 - get_sum(1, 0, n - 1, a, m) > 0) {
                            r = m;
                        } else {
                            l = m + 1;
                        }
                    }
                    int start = l;
                    insert(1, 0, n - 1, start, end, 1);
                    printf("%d %d\n", start, end);
                }
            } else {
                int l, r;
                scanf("%d%d", &l, &r);
                int s = get_sum(1, 0, n - 1, l, r);
                insert(1, 0, n - 1, l, r, 0);
                printf("%d\n", s);
            }
        }
        puts("");
    }
    return 0;
}
