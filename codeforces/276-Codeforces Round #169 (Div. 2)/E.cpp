// Codeforces Round #169 (Div. 2)
// Problem E, Little Girl and Problem on Trees
#include <cstdio>
#include <vector>

#define foreach(i, v) for (__typeof ((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 100000 + 5;

std::vector <int> neighbors[N], values[N];
int depth[N], belong[N], degree[N], length[N];
int n, q, root_covered, root;

int dfs (int u, int f, int number) {
    depth[u] = depth[f] + 1;
    belong[u] = number;
    int result = depth[u];
    foreach (iter, neighbors[u]) {
        int v = *iter;
        if (v != f) {
            result = dfs (v, u, number);
        }
    }
    return result;
}

int lowbit (int x) {
    return x & -x;
}

void add_value (int u, int x, int value) {
    for (; x <= length[u]; x += lowbit (x)) {
        values[u][x] += value;
    }
}

int get_value (int u, int x) {
    int result = 0;
    for (; x > 0; x -= lowbit (x)) {
        result += values[u][x];
    }
    return result;
}

void add (int u, int l, int r, int value) {
    l = std::max (l, 1);
    r = std::min (r, length[u]);
    add_value (u, l, value);
    add_value (u, r + 1, -value);
}

void insert (int u, int value, int d) {
    if (depth[u] <= d) {
        root_covered += value;
        if (d > depth[u]) {
            add_value (0, std::min (length[0], d - depth[u]), value);
            if (u != root) {
                add (belong[u], 1, d - depth[u], -value);
            }
        }
    }
    if (u != root) {
        add (belong[u], depth[u] - d, d + depth[u], value);
    }
}

int main () {
    scanf ("%d%d", &n, &q);
    for (int i = 1; i < n; ++ i) {
        int u, v;
        scanf ("%d%d", &u, &v);
        neighbors[u].push_back (v);
        neighbors[v].push_back (u);
        degree[u] ++;
        degree[v] ++;
    }
    root = -1;
    for (int i = 1; i <= n; ++ i) {
        if (root == -1 || degree[i] > degree[root]) {
            root = i;
        }
    }
    int number = 0, max_length = 0;
    foreach (iter, neighbors[root]) {
        number ++;
        length[number] = dfs (*iter, root, number);
        values[number].resize (length[number] + 1);
        max_length = std::max (max_length, length[number]);
    }
    length[0] = max_length;
    values[0].resize (length[0] + 1);
    while (q --) {
        int type;
        scanf ("%d", &type);
        if (type == 0) {
            int u, value, d;
            scanf ("%d%d%d", &u, &value, &d);
            insert (u, value, d);
            /*
            for (int i = 2; i <= 6; ++ i) {
                printf ("%d: %d\n", i, get_value (0, length[0]) - get_value (0, depth[i] - 1) + get_value (belong[i], depth[i]));
            }
            */
        } else {
            int u, answer;
            scanf ("%d", &u);
            if (u == root) {
                answer = root_covered;
            } else {
                answer = get_value (0, length[0]) - get_value (0, depth[u] - 1) + get_value (belong[u], depth[u]);
            }
            printf ("%d\n", answer);
        }
    }
    return 0;
}
