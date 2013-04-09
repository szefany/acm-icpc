// POJ 3415, Common Substrings
#include <iostream>
#include <cstdio>
#include <cstring>

const int N = 200000 + 5;

struct Trie {
    int index[52], prev, step, cover;
    long long sum;
} trie[N];
int node_count;

char string[N];
int k, rank[N], bucket[N];

int trans (int key) {
    return key >= 'a' ? key - 'a' : 26 + key - 'A';
}

void clear (int node) {
    memset (trie[node].index, 0, sizeof (trie[node].index));
    trie[node].prev = trie[node].step = trie[node].cover = trie[node].sum = 0;
}

void build (char* string, int length) {
    node_count = 1;
    clear (1);
    for (int i = 0, last = 1, u, node; i < length; ++ i, last = u) {
        int key = trans (string[i]);
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

void sort () {
    memset (rank, 0, sizeof (rank));
    memset (bucket, 0, sizeof (bucket));
    for (int i = 1; i <= node_count; ++ i) {
        bucket[trie[i].step] ++;
    }
    for (int i = 1; i <= node_count; ++ i) {
        bucket[i] += bucket[i - 1];
    }
    for (int i = 1; i <= node_count; ++ i) {
        rank[bucket[trie[i].step] --] = i;
    }
}

int main () {
    while (scanf ("%d", &k) != EOF && k != 0) {
        scanf ("%s", string);
        int length = strlen (string);
        build (string, length);
        sort ();
        for (int i = 0, u = 1; i < length; ++ i) {
            int key = trans (string[i]);
            u = trie[u].index[key];
            trie[u].cover ++;
        }
        for (int i = node_count; i >= 1; -- i) {
            int u = rank[i], v = trie[u].prev;
            trie[v].cover += trie[u].cover;
        }
        for (int i = 1; i <= node_count; ++ i) {
            int u = rank[i], v = trie[u].prev;
            if (trie[u].step >= k) {
                trie[u].sum = trie[v].sum + (long long)trie[u].cover * (trie[u].step - std::max (k - 1, trie[v].step));
            }
        }
        /*
        for (int i = 1; i <= node_count; ++ i) {
            printf ("%d: %d %lld\n", i, trie[i].cover, trie[i].sum);
        }
        */
        scanf ("%s", string);
        length = strlen (string);
        long long answer = 0;
        for (int i = 0, u = 1, current = 0; i < length; ++ i) {
            int key = trans (string[i]);
            if (trie[u].index[key]) {
                u = trie[u].index[key];
                current ++;
            } else {
                for (u = trie[u].prev; u && trie[u].index[key] == 0; u = trie[u].prev);
                if (u == 0) {
                    current = 0;
                    u = 1;
                } else {
                    current = trie[u].step + 1;
                    u = trie[u].index[key];
                }
            }
            if (u != 1 && current >= k) {
                int v = trie[u].prev;
                answer += trie[v].sum + (long long)trie[u].cover * (current - std::max (k - 1, trie[v].step));
            }
        }
        std::cout << answer << std::endl;
    }
    return 0;
}
