// HDU 3247, Resource Archiver
#include <cstdio>
#include <cstring>
#include <bitset>
#include <queue>
#include <climits>

const int N = 70000;

struct Trie {
    int index[2], prev, mask;
    bool virus;
} trie[N];

int n, m, node_count;

void clear (int node) {
    memset (trie[node].index, 0, sizeof (trie[node].index));
    trie[node].prev = trie[node].mask = 0;
    trie[node].virus = false;
}

void inititalise () {
    node_count = 1;
    clear (1);
}

void insert (char* string, int index) {
    int length = strlen (string), u = 1;
    for (int i = 0; i < length; ++ i) {
        int key = string[i] - '0';
        if (trie[u].index[key] == 0) {
            clear (++ node_count);
            trie[u].index[key] = node_count;
        }
        u = trie[u].index[key];
    }
    if (index < 0) {
        trie[u].virus = true;
    } else {
        trie[u].mask |= 1 << index;
    }
}

int queue[N];
void build_label () {
    queue[0] = 1;
    for (int head = 0, tail = 0, node; head <= tail; ++ head) {
        int u = queue[head];
        for (int i = 0; i < 2; ++ i) {
            if (trie[u].index[i] == 0) {
                trie[u].index[i] = u == 1 ? 1 : trie[trie[u].prev].index[i];
            } else {
                int v = queue[++ tail] = trie[u].index[i];
                if (u == 1) {
                    trie[v].prev = 1;
                } else {
                    for (node = trie[u].prev; node && trie[node].index[i] == 0; node = trie[node].prev);
                    trie[v].prev = node == 0 ? 1 : trie[node].index[i];
                }
                trie[v].virus |= trie[trie[v].prev].virus;
                trie[v].mask |= trie[trie[v].prev].mask;
            }
        }
    }
}

struct data {
    int mask, index;
    data () {}
    data (int index, int mask): mask (mask), index (index) {}
};

std::bitset <1 << 10> in_queue[N];
int dp[N][1 << 10];

int main () {
    while (scanf ("%d%d", &n, &m) != EOF && n + m > 0) {
        inititalise ();
        char buffer[1000];
        for (int i = 0; i < n; ++ i) {
            scanf ("%s", buffer);
            insert (buffer, i);
        }
        for (int i = 0; i < m; ++ i) {
            scanf ("%s", buffer);
            insert (buffer, -1);
        }
        build_label ();
        for (int mask = 0; mask < 1 << n; ++ mask) {
            for (int i = 1; i <= node_count; ++ i) {
                dp[i][mask] = -1;
            }
        }
        int answer = INT_MAX;
        std::queue <data> q;
        q.push (data (1, 0));
        dp[1][0] = 0, in_queue[1][0] = 1;
        while (!q.empty()) {
            int u = q.front().index, mask = q.front().mask;
            q.pop();
            in_queue[u][mask] = 0;
            if (mask == (1 << n) - 1 && dp[u][mask] < answer) {
                answer = dp[u][mask];
            }
            for (int i = 0; i < 2; ++ i) {
                int v = trie[u].index[i];
                if (trie[v].virus) {
                    continue;
                }
                int& target = dp[v][mask | trie[v].mask];
                if (target == -1 || target > dp[u][mask] + 1) {
                    target = dp[u][mask] + 1;
                    if (!in_queue[v][mask | trie[v].mask]) {
                        in_queue[v][mask | trie[v].mask] = 1;
                        q.push (data (v, mask | trie[v].mask));
                    }
                }
            }
        }
        printf ("%d\n", answer);
    }
    return 0;
}
