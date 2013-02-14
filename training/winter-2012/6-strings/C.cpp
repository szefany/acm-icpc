// Codeforces Beta Round #94 (Div. 1 Only)
// Problem B, String
#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 200000 + 5;

struct Trie {
    int index[26];
    int prev, step;
    long long sum, self;
} trie[N];
int node_count;

char string[N], answer[N];
int rank[N], length;

void build (char* string) {
    node_count = 1;
    for (int i = 0, last = 1, u, node; i < length; ++ i, last = u) {
        int key = string[i] - 'a';
        u = ++ node_count;
        trie[u].step = trie[last].step + 1;
        for (node = last; node && trie[node].index[key] == 0; node = trie[node].prev) {
            trie[node].index[key] = u;
        }
        if (node == 0) {
            trie[u].prev = 1;
            continue;
        }
        int v = trie[node].index[key];
        if (trie[v].step == trie[node].step + 1) {
            trie[u].prev = v;
        } else {
            int nv = ++ node_count;
            trie[nv] = trie[v];
            trie[nv].step = trie[node].step + 1;
            trie[u].prev = trie[v].prev = nv;
            for (; node && trie[node].index[key] == v; node = trie[node].prev) {
                trie[node].index[key] = nv;
            }
        }
    }
}

bool cmp (int x, int y) {
    return trie[x].step < trie[y].step;
}

void debug () {
    for (int i = 1; i <= node_count; ++ i) {
        printf ("%d:  prev = %d\n", i, trie[i].prev);
        for (int j = 0; j < 26; ++ j) {
            if (trie[i].index[j]) {
                printf ("%c %d\n", (char)('a' + j), trie[i].index[j]);
            }
        } puts ("");
    }
}

int main () {
    freopen ("input", "r", stdin);
    scanf ("%s", string);
    length = strlen (string);
    build (string);
    for (int i = 0, u = 1; i < length; ++ i) {
        int key = string[i] - 'a';
        u = trie[u].index[key];
    }
    for (int i = 1; i <= node_count; ++ i) {
        rank[i] = i;
    }
    std::sort (rank + 1, rank + node_count + 1, cmp);
    for (int i = 0, u = 1; i < length; ++ i) {
        int key = string[i] - 'a';
        u = trie[u].index[key];
        trie[u].self ++;
    }
    for (int i = node_count; i >= 1; -- i) {
        int u = rank[i];
        trie[trie[u].prev].self += trie[u].self;
    }
    for (int i = node_count; i >= 1; -- i) {
        int u = rank[i];
        trie[u].sum = trie[u].self;
        for (int j = 0; j < 26; ++ j) {
            int v = trie[u].index[j];
            trie[u].sum += trie[v].sum;
        }
        // printf ("%d %d\n", u, trie[u].sum);
    }
    // debug ();
    int m, total = 0;
    bool valid = true;
    scanf ("%d", &m);
    for (int u = 1; m > 0; ) {
        if (u != 1) {
            m -= trie[u].self;
            if (m <= 0) {
                break;
            }
        }
        int pivot = -1;
        for (int i = 0; i < 26; ++ i) {
            int v = trie[u].index[i];
            if (trie[v].sum < m) {
                m -= trie[v].sum;
            } else {
                pivot = i;
                break;
            }
        }
        if (pivot < 0) {
            valid = false;
            break;
        }
        answer[total ++] = 'a' + pivot;
        u = trie[u].index[pivot];
    }
    puts (valid ? answer : "No such line." );
    return 0;
}
