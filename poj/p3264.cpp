// POJ 3264, Balanced Lineup
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 50005;
const int INF = 1 << 20;

struct Tree {
    int l, r, lch, rch, min_key, max_key;
} T[N * 2];
int node_count, root;
int n, q;
int elements[N], answer[2];

#define L T[u].lch
#define R T[u].rch

void build (int &u, int l, int r) {
    u = ++ node_count;
    T[u].l = l, T[u].r = r;
    if (l == r) {
        T[u].min_key = T[u].max_key = elements[l];
        return;
    }
    build (L, l, l + r >> 1);
    build (R, l + r + 2 >> 1, r);
    T[u].min_key = min (T[L].min_key, T[R].min_key);
    T[u].max_key = max (T[L].max_key, T[R].max_key);
}

void query (int u, int l, int r) {
    if (l <= T[u].l && r >= T[u].r) {
        answer[0] = min (answer[0], T[u].min_key);
        answer[1] = max (answer[1], T[u].max_key);
        return;
    }
    if (l < T[R].l) {
        query (L, l, r);
    }
    if (r > T[L].r) {
        query (R, l, r);
    }
}

int main () {
    scanf ("%d%d", &n, &q);
    for (int i = 1; i <= n; ++ i) {
        scanf ("%d", &elements[i]);
    }
    build (root, 1, n);
    while (q --) {
        int u, v;
        scanf ("%d%d", &u, &v);
        answer[0] = INF;
        answer[1] = -INF;
        query (root, u, v);
        printf ("%d\n", answer[1] - answer[0]);
    }
    return 0;
}
