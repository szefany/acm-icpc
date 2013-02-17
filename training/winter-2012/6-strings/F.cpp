// URAL 1706, Cipher Message 2
#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 8000;

struct Trie {
    int index[26], prev, step, size;
} trie[N * 3];
int node_count;

char string[N], buffer[N];
int k;

void clear (int node) {
    memset (trie[node].index, 0, sizeof (trie[node].index));
    trie[node].prev = trie[node].step = trie[node].size = 0;
}

void initialise () {
    node_count = 1;
    clear (1);
}

void build (char* string, int length) {
    for (int i = 0, last = 1, u, node; i < length; ++ i, last = u) {
        int key = string[i] - 'a';
        u = ++ node_count;
        clear (u);
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

int solve () {
    int* rank = new int [node_count + 1];
    for (int i = 1; i <= node_count; ++ i) {
        rank[i] = i;
    }
    std::sort (rank + 1, rank + node_count + 1, cmp);
    int result = 0;
    for (int i = node_count; i >= 1; -- i) {
        int u = rank[i];
        result += trie[u].step - trie[trie[u].prev].step;
    }
    return result;
}

int main () {
    scanf ("%d%s", &k, string);
    int length = strlen (string);
    for (int i = 0; i < length; ++ i) {
        initialise ();
        int size = 0;
        for (int j = 0, pivot = i; j < k; ++ j, (++ pivot) %= length) {
            buffer[size ++] = string[pivot];
        }
        build (buffer, size);
        int answer = solve ();
        printf ("%d%c", answer, i == length - 1 ? '\n' : ' ');
    }
    return 0;
}
