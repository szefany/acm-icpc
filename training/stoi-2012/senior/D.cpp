#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 600000;
const int M = 14;

struct Trie {
    std::vector <int> positions;
    int children[2];
} trie[N];
int n, m, node_count;

void insert (int value, int pos) {
    for (int node = 0, k = M; k >= 0; -- k) {
        int key = (value & 1 << k) > 0;
        if (trie[node].children[key] == 0) {
            trie[node].children[key] = ++ node_count;
        }
        node = trie[node].children[key];
        trie[node].positions.push_back (pos);
    }
}

bool check (int node, int l, int r) {
    if (node == 0) {
        return false;
    }
    std::vector <int>::iterator iter = lower_bound (trie[node].positions.begin(), trie[node].positions.end(), l);
    return iter != trie[node].positions.end() && *iter <= r;
}

int solve (int l, int r, int x) {
    int result = 0;
    for (int node = 0, k = M; k >= 0; -- k) {
        int key = (x & 1 << k) == 0;
        if (check (trie[node].children[key], l, r)) {
            result += 1 << k;
        } else {
            key ^= 1;
        }
        node = trie[node].children[key];
    }
    return result;
}

int main () {
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        int x;
        scanf ("%d", &x);
        insert (x, i);
    }
    while (m --) {
        int l, r, x;
        scanf ("%d%d%d", &l, &r, &x);
        printf ("%d\n", solve (l, r, x));
    }
    return 0;
}
