#include <cstdio>
#include <cstring>
#include <iostream>
#include <climits>

using std::pair;
using std::make_pair;

const int N = 100000 + 1;
const int INF = INT_MAX;

int elements[N], n;

struct Splay_Tree {
    static const int N = 100000 + 10;
    bool flag[N];
    int child[N][2], size[N], father[N];
    int node_count, root;

    typedef pair<int, int> Pair;
    Pair value[N], min_value[N];

#define L(u) child[(u)][0]
#define R(u) child[(u)][1]

    void update(int u) {
        size[u] = size[L(u)] + size[R(u)] + 1;
        min_value[u] = std::min(min_value[L(u)], min_value[R(u)]);
        min_value[u] = std::min(min_value[u], value[u]);
    }

    void new_node(int &u, int f, int x, int v) {
        u = ++ node_count;
        father[u] = f;
        size[u] = 1;
        L(u) = R(u) = flag[u] = 0;
        value[u] = min_value[u] = make_pair(v, x);
    }

    void build(int l, int r, int &u, int f) {
        if (l <= r) {
            int m = l + r >> 1;
            new_node(u, f, m, elements[m]);
            build(l, m - 1, L(u), u);
            build(m + 1, r, R(u), u);
            update(u);
        }
    }

    void initialise() {
        root = node_count = 0;
        min_value[0] = make_pair(INF, INF);
        new_node(root, 0, 0, INF);
        new_node(R(root), root, n + 1, INF);
        build(1, n, L(R(root)), R(root));
        update(R(root));
        update(root);
    }

    void push_down(int u) {
        if (flag[u]) {
            std::swap(L(u), R(u));
            flag[L(u)] ^= 1;
            flag[R(u)] ^= 1;
            flag[u] = 0;
        }
    }

    void rotate(int u, int d) {
        int f = father[u], r = R(f) == u;
        int v = child[u][d];
        int w = child[v][d ^ 1];

        child[u][d] = w, father[w] = u;
        child[v][d ^ 1] = u, father[u] = v;
        father[v] = f, child[f][r] = v;
        update(u);
    }

    void splay(int u, int target) {
        push_down(u);
        while (father[u] != target) {
            int f = father[u];
            if (father[f] == target) {
                rotate(f, R(f) == u);
            } else {
                int g = father[f];
                int d = R(g) == f;
                if (child[f][d] == u) {
                    rotate(g, d);
                    rotate(f, d);
                } else {
                    rotate(f, d ^ 1);
                    rotate(g, d);
                }
            }
        }
        update(u);
        if (target == 0) {
            root = u;
        } 
    }

    int get_node(int x) {
        for (int u = root; ; ) {
            push_down(u);
            if (size[L(u)] == x) {
                return u;
            }
            if (x > size[L(u)]) {
                x -= size[L(u)] + 1;
                u = R(u);
            } else {
                u = L(u);
            }
        }
    }

    int find(Pair v) {
        int u = root;
        int result = 0;
        while (value[u] != v) {
            push_down(u);
            if (min_value[L(u)] == v) {
                u = L(u);
            } else {
                result += size[L(u)] + 1;
                u = R(u);
            }
        }
        push_down(u);
        result += size[L(u)];
        // Note the position 0
        return result;
    }

    void reverse(int l, int r) {
        splay(get_node(l - 1), 0);
        splay(get_node(r + 1), root);
        int u = L(R(root));
        flag[u] ^= 1;
    }

    int solve(int start) {
        splay(get_node(start - 1), 0);
        splay(get_node(n + 1), root);
        int u = L(R(root));
        int result = find(min_value[u]);
        reverse(start, result);
        return result;
    }
} tree;

int answer[N];

int main() {
    freopen("input", "r", stdin);
    while (scanf("%d", &n) && n > 0) {
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &elements[i]);
        }

        tree.initialise();
        for (int i = 1; i <= n; ++ i) {
            answer[i] = tree.solve(i);
        }

        for (int i = 1; i <= n; ++ i) {
            printf("%d%c", answer[i], i == n ? '\n' : ' ');
        }
    }
    return 0;
}
