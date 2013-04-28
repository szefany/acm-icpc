#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

const int N = 1000 + 1;
const int INF = 1 << 20;

char grid[N][N];
int left[N][N], right[N][N], height[N][N], toleft[N][N], toright[N][N];
int n, m;

int elements[N];

struct segment {
    static const int SIZE = N << 1;
    int left[SIZE], right[SIZE], max_value[SIZE], min_value[SIZE], child[SIZE][2], cover[SIZE];
    int size, root;
    
    void build(int &u, int l, int r) {
        u = ++ size;
        left[u] = l;
        right[u] = r;
        cover[u] = 0;
        max_value[u] = min_value[u] = -INF;
        if (l < r) {
            int m = l + r >> 1;
            build(child[u][0], l, m);
            build(child[u][1], m + 1, r);
        }
    }
    
    inline void initialise(int l, int r) {
        size = root = 0;
        build(root, l, r);
    }
    
    inline void update(int u) {
        int l = child[u][0];
        int r = child[u][1];
        min_value[u] = std::min(min_value[l], min_value[r]);
        max_value[u] = std::max(max_value[l], max_value[r]);
    }
    
    void push_down(int u) {
        for (int i = 0; i < 2; ++ i) {
            int v = child[u][i];
            min_value[v] = max_value[v] = cover[v] = cover[u];
        }
        cover[u] = 0;
    }
    
    void insert(int u, int l, int r, int v) {
        if (l <= left[u] && r >= right[u]) {
            if (v > max_value[u]) {
                min_value[u] = max_value[u] = cover[u] = v;
                return;
            }
            if (v <= min_value[u] || left[u] == right[u]) {
                return;
            }
        }
        if (cover[u]) {
            push_down(u);
        }
        int m = left[u] + right[u] >> 1;
        if (l <= m) {
            insert(child[u][0], l, r, v);
        }
        if (r > m) {
            insert(child[u][1], l, r, v);
        }
        update(u);
    }
    
    void query(int u) {
        if (cover[u]) {
            for (int i = left[u]; i <= right[u]; ++ i) {
                elements[i] = cover[u];
            }
            return;
        }
        if (left[u] < right[u]) {
            query(child[u][0]);
            query(child[u][1]);
        }
    }
    
    void push(int l, int r, int v) {
        insert(root, l, r, v);
    }
} tree;

int answer[N << 2];

int main() {
    freopen("input", "r", stdin);
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++ i) {
            scanf("%s", grid[i] + 1);
        }
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= m; ++ j) {
                height[i][j] = grid[i][j] == '#' ? 0 : height[i - 1][j] + 1;
                toleft[i][j] = grid[i][j] == '#' ? 0 : toleft[i][j - 1] + 1;
                if (grid[i][j] == '#') {
                    left[i][j] = 0;
                } else if (height[i][j] == 1) {
                    left[i][j] = toleft[i][j];
                } else {
                    left[i][j] = std::min(left[i - 1][j], toleft[i][j]);
                }
            }
        }
        for (int i = 1; i <= n; ++ i) {
            for (int j = m; j >= 1; -- j) {
                toright[i][j] = grid[i][j] == '#' ? 0 : toright[i][j + 1] + 1;
                if (grid[i][j] == '#') {
                    right[i][j] = 0;
                } else if (height[i][j] == 1) {
                    right[i][j] = toright[i][j];
                } else {
                    right[i][j] = std::min(right[i - 1][j], toright[i][j]);
                }
            }
        }
        
        for (int i = 0; i <= n + m << 1; ++ i) {
            answer[i] = 0;
        }
        for (int i = 1; i <= n; ++ i) {
            tree.initialise(1, m);
            for (int j = 1; j <= m; ++ j) {
                if (grid[i][j] != '#') {
                    int leftmost = j - left[i][j] + 1;
                    int rightmost = j + right[i][j] - 1;
                    int upmost = i - height[i][j] + 1;
                    tree.push(leftmost, rightmost, - leftmost - upmost);
                }
            }
            tree.query(tree.root);
            for (int j = 1; j <= m; ++ j) {
                if (grid[i][j] != '#') {
                    int temp = elements[j];
                    if (temp != -INF) {
                        int perimeter = (temp + i + j + 2 << 1);
                        answer[perimeter] ++;
                    }
                }
            }
        }
        for (int i = 1; i <= n + m << 1; ++ i) {
            if (answer[i]) {
                printf("%d x %d\n", answer[i], i);
            }
        }
    }
    return 0;
}
