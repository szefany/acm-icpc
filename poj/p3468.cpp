#include <cstdio>
#include <cstring>

struct Splay_Tree {
    static const int SIZE = 100000 + 10;
    int child[SIZE][2], size[SIZE], father[SIZE], key[SIZE];
    long long value[SIZE], sum[SIZE], flag[SIZE];
    int node_count, root;

#define L(u) child[(u)][0]
#define R(u) child[(u)][1]

    void update(int u) {
        sum[u] = sum[L(u)] + sum[R(u)] + value[u];
        size[u] = size[L(u)] + size[R(u)] + 1;
    }

    void new_node(int &u, int f, int k, int v) {
        // node u, with father node f, key k, value v
        u = ++ node_count;
        father[u] = f;
        value[u] = sum[u] = v;
        size[u] = 1;
        key[u] = k;
        L(u) = R(u) = flag[u] = 0;
    }

    void build(int l, int r, int &u, int f) {
        // Interval [l, r], node u, with father node f
        if (l <= r) {
            int m = l + r >> 1;
            new_node(u, f, m, elements[m]);
            build(l, m - 1, L(u), u);
            build(m + 1, r, R(u), u);
            update(u);
        }
    }

    void initialise(int *a, int length) {
        n = length;
        for (int i = 1; i <= n; ++ i) {
            elements[i] = a[i];
        }
        root = node_count = 0;
        new_node(root, 0, 0, 0);
        new_node(R(root), root, n + 1, 0);
        build(1, n, L(R(root)), R(root));
        update(R(root));
        update(root);
    }

    void push_down(int u) {
        if (flag[u]) {
            for (int i = 0; i < 2; ++ i) {
                int v = child[u][i];
                if (v) {
                    flag[v] += flag[u];
                    value[v] += flag[u];
                    sum[v] += (long long)flag[u] * size[v];
                }
            }
            flag[u] = 0;
        }
    }

    void rotate(int u, int d) {
        int f = father[u], r = child[f][1] == u;
        int v = child[u][d];
        int w = child[v][d ^ 1];
        // If they have been pushed down, the following two lines could be commented
        // push_down(f);
        // push_down(u);

        child[u][d] = w, father[w] = u;
        child[v][d ^ 1] = u, father[u] = v;
        father[v] = f, child[f][r] = v;
        update(u);
    }

    void splay(int u, int target) {
        // keep splaying node u until its father is target
        push_down(u);
        while (father[u] != target) {
            int f = father[u];
            if (father[f] == target) {
                rotate(f, child[f][1] == u);
            } else {
                int g = father[f];
                int d = child[g][1] == f;
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

    int get_node(int k) {
        // get node with key k
        for (int u = root; u; u = child[u][k > key[u]]) {
            if (key[u] == k) {
                return u;
            }
            push_down(u);
        }
    }

    long long query(int l, int r) {
        splay(get_node(l - 1), 0);
        splay(get_node(r + 1), root);
        return sum[L(R(root))];
    }

    void add_value(int l, int r, int delta) {
        splay(get_node(l - 1), 0);
        splay(get_node(r + 1), root);
        int u = L(R(root));
        flag[u] += delta;
        value[u] += delta;
        sum[u] += (long long)delta * size[u];
        update(R(root));
        update(root);
    }

    void debug() {
        for (int i = 1; i <= node_count; ++ i) {
            printf("%d %d %d %d\n", i, child[i][0], key[i], size[i]);
        }
    }
} tree;

const int N = 100000 + 1;

int elements[N], n, m;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &elements[i]);
    }
    tree.initialise(elements, n);
    while (m --) {
        char buffer[2];
        scanf("%s", buffer);
        if (*buffer == 'Q') {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%lld\n", tree.query(l, r));
        } else {
            int l, r, delta;
            scanf("%d%d%d", &l, &r, &delta);
            tree.add_value(l, r, delta);
        }
    }
    return 0;
}
