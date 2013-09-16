#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

const int N = 100000 + 10;

struct Point {
    int x, y, z;
    void input() {
        scanf("%d%d%d", &x, &y, &z);
    }
} points[N];

int order[N];
int n;

bool by_x(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool by_y(int a, int b) {
    return points[a].y < points[b].y;
}

struct Data {
    int value, count;
    Data(int value = 0, int count = 0): value(value), count(count) {}
    void update(const Data &o) {
        if (o.value > value) {
            value = o.value;
            count = o.count;
        } else if (o.value == value) {
            count += o.count;
        }
    }
} data[N];

struct Treap {
    int children[N][2], weight[N], key[N];
    Data value[N], max_value[N];
    int node_count, root;

    void clear() {
        node_count = root = 0;
        children[root][0] = children[root][1] = 0;
        max_value[0] = Data(0, 0);
        weight[root] = INT_MAX;
    }

    void update(int u) {
        if (u) {
            max_value[u] = value[u];
            max_value[u].update(max_value[children[u][0]]);
            max_value[u].update(max_value[children[u][1]]);
        }
    }

    void rotate(int &u, int r) {
        int v = children[u][r];
        children[u][r] = children[v][r ^ 1];
        children[v][r ^ 1] = u;
        update(u);
        update(v);
        u = v;
    }

    void insert(int &u, int k, const Data &d) {
        if (u == 0) {
            u = ++ node_count;
            children[u][0] = children[u][1] = 0;
            weight[u] = rand();
            key[u] = k;
            max_value[u] = value[u] = d;
            return;
        } else {
            int r = k > key[u];
            int &v = children[u][r];
            insert(v, k, d);
            if (weight[v] < weight[u]) {
                rotate(u, r);
            }
            update(u);
        }
    }

    void insert(int k, const Data &d) {
        insert(root, k, d);
    }

    Data query(int z) {
        Data result(0, 1);
        int u = root;
        while (u) {
            if (z < key[u]) {
                u = children[u][0];
            } else {
                result.update(max_value[children[u][0]]);
                result.update(value[u]);
                u = children[u][1];
            }
        }
        result.value ++;
        return result;
    }

} treap;

void solve(int l, int r) {
    if (l == r) {
        return;
    }
    int m = l + r >> 1;
    solve(l, m);
    for (int i = l; i <= r; ++ i) {
        order[i] = i;
    }
    std::sort(order + l, order + m + 1, by_y);
    std::sort(order + m + 1, order + r + 1, by_y);
    treap.clear();
    for (int i = m + 1, j = l; i <= r; ++ i) {
        while (j <= m && points[order[j]].y <= points[order[i]].y) {
            treap.insert(points[order[j]].z, data[order[j]]);
            j ++;
        }
        Data temp = treap.query(points[order[i]].z);
        if (temp.value > 1) {
            data[order[i]].update(temp);
        }
    }
    solve(m + 1, r);
}

int main() {
    int test;
    scanf("%d", &test);
    while (test --) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i) {
            points[i].input();
            data[i] = Data(1, 1);
        }
        std::sort(points, points + n, by_x);
        solve(0, n - 1);
        Data answer;
        for (int i = 0; i < n; ++ i) {
            answer.update(data[i]);
        }
        answer.count &= (1 << 30) - 1;
        printf("%d %d\n", answer.value, answer.count);
    }
    return 0;
}
