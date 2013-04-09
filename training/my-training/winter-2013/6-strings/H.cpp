// POJ 3630, Phone List
#include <cstdio>
#include <cstring>

const int N = 100000 + 5;
struct Trie {
    int index[10];
    bool finish, has_children;
} trie[N];
int node_count;

void clear (int node) {
    memset (trie[node].index, 0, sizeof (trie[node].index));
    trie[node].finish = trie[node].has_children = false;
}

void initialise () {
    node_count = 0;
    clear (0);
}

bool insert (char* string) {
    int length = strlen (string);
    int node = 0;
    for (int i = 0; i < length; ++ i) {
        int key = string[i] - '0';
        if (trie[node].index[key] == 0) {
            clear (++ node_count);
            trie[node].index[key] = node_count;
            trie[node].has_children = true;
        }
        node = trie[node].index[key];
        if (trie[node].finish) {
            return false;
        }
    }
    if (trie[node].has_children) {
        return false;
    }
    trie[node].finish = true;
    return true;
}

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        initialise ();
        int n;
        scanf ("%d", &n);
        bool valid = true;
        for (int i = 0; i < n; ++ i) {
            char buffer[10];
            scanf ("%s", buffer);
            valid &= insert (buffer);
        }
        puts (valid ? "YES" : "NO");
    }
    return 0;
}
