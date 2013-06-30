// URAL 1517, Freedom of Choice
#include <cstdio>
#include <cstring>

const int N = 200000 + 5;

struct Node {
    int index[26];
    int step, prev;
} trie[N];
int node_count;

char string[N];
int length;

void build () {
    node_count = 1;
    for (int i = 0, last = 1, u, node; i < length; ++ i, last = u) {
        int key = string[i] - 'A';
        u = ++ node_count;
        trie[u].step = trie[last].step + 1;
        for (node = last; node && !trie[node].index[key]; node = trie[node].prev) {
            trie[node].index[key] = u;
        }
        if (!node) {
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
            trie[v].prev = trie[u].prev = nv;
            for (; node && trie[node].index[key] == v; node = trie[node].prev) {
                trie[node].index[key] = nv;
            }
        }
    }
}

int main () {
    scanf ("%d", &length);
    scanf ("%s", string);
    build ();
    scanf ("%s", string);
    int answer = 0, pivot = 0;
    for (int i = 0, u = 1, current = 0; i < length; ++ i) {
        int key = string[i] - 'A';
        if (trie[u].index[key]) {
            current ++;
            u = trie[u].index[key];
        } else {
            for (; u && !trie[u].index[key]; u = trie[u].prev);
            if (u == 0) {
                u = 1;
                current = 0;
            } else {
                current = trie[u].step + 1;
                u = trie[u].index[key];
            }
        }
        if (current > answer) {
            answer = current;
            pivot = i;
        }
    }
    for (int i = pivot - answer + 1; i <= pivot; ++ i) {
        putchar (string[i]);
    } puts ("");
    return 0;
}
