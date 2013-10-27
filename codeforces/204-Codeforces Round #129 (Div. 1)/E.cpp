#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>

const int N = 200000 + 10;
const int M = N << 1;

int children[M][27], prev[M], step[M], times[M], order[M], cover[M];
int node_count, last;

void clear(int u) {
    memset(children[u], 0, sizeof(children[u]));
    prev[u] = step[u] = 0;
}

void copy_data(int to, int from) {
    memcpy(children[to], children[from], sizeof(children[from]));
    prev[to] = prev[from];
    step[to] = step[from];
    cover[to] = cover[from];
}

void initialise() {
    node_count = 1;
    last = 1;
    clear(1);
}

int get_key(char token) {
    return token == '#' ? 26 : token - 'a';
}

void insert(char token, int id) {
    int key = get_key(token);
    int u = ++ node_count, node;
    clear(u);
    step[u] = step[last] + 1;
    cover[u] = id;
    for (node = last; node && children[node][key] == 0; node = prev[node]) {
        children[node][key] = u;
    }
    if (node == 0) {
        prev[u] = 1;
    } else {
        int v = children[node][key];
        if (step[v] == step[node] + 1) {
            prev[u] = v;
        } else {
            int nv = ++ node_count;
            copy_data(nv, v);
            step[nv] = step[node] + 1;
            prev[u] = prev[v] = nv;
            for (; node && children[node][key] == v; node = prev[node]) {
                children[node][key] = nv;
            }
        }
    }
    last = u;
}

bool cmp(int a, int b) {
    return step[a] < step[b];
}

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

std::vector<int> neighbors[M];
std::string strings[N];
int top[M];
int n, m;

std::set<int>* merge(std::set<int>* a, std::set<int>* b) {
    if (a->size() > b->size()) {
        std::swap(a, b);
    }
    b->insert((*a).begin(), (*a).end());
    delete a;
    return b;
}

std::set<int>* dfs_1(int u) {
    std::set<int>* set = new std::set<int>();
    if (cover[u] != -1) {
        set->insert(cover[u]);
    }
    foreach(iter, neighbors[u]) {
        int v = *iter;
        set = merge(set, dfs_1(v));
    }
    times[u] = set->size();
    return set;
}

void dfs_2(int u, int current_top) {
    if (times[u] >= m) {
        current_top = u;
    }
    top[u] = current_top;
    foreach(iter, neighbors[u]) {
        int v = *iter;
        dfs_2(v, current_top);
    }
}

long long solve(int id) {
    long long result = 0;
    for (int i = 0, length = 0, u = 1; i < strings[id].length(); ++ i) {
        int key = get_key(strings[id][i]);
        if (children[u][key]) {
            u = children[u][key];
            length ++;
        } else {
            while (u && children[u][key] == 0) {
                u = prev[u];
            }
            if (u == 0) {
                u = 1;
                length = 0;
            } else {
                length = step[u] + 1;
                u = children[u][key];
            }
        }
        int p = top[u];
        if (p > 1) {
            int now = p == u ? length : step[p];
            result += now;
        }
    }
    return result;
}

int main() {
    freopen("input", "r", stdin);
    initialise();
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++ i) {
        std::cin >> strings[i];
        for (int j = 0; j < strings[i].length(); ++ j) {
            insert(strings[i][j], i);
        }
        insert('#', -1);
    }

    for (int i = node_count; i >= 1; -- i) {
        neighbors[prev[i]].push_back(i);
    }
    dfs_1(1);
    dfs_2(1, 0);

/*
    for (int i = 1; i <= node_count; ++ i) {
        printf("%d: ", i);
        for (int j = 0; j < 27; ++ j) {
            if (children[i][j]) {
                printf("(%d, %d)", j, children[i][j]);
            } 
        }
        printf("%d\n", times[i]);
    }
*/

    for (int i = 1; i <= n; ++ i) {
        std::cout << solve(i) << (i == n ? '\n' : ' ');
    }
    return 0;
}
