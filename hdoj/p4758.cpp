#include <cstdio>
#include <cstring>

const int N = 100 + 10;
const int M = N << 1;

int children[M][2], fail[M], state[M];
int node_count;

void clear(int u) {
    children[u][0] = children[u][1] = 0;
    fail[u] = state[u] = 0;
}

void initialise() {
    node_count = 1;
    clear(1);
}

int get_key(char token) {
    return token == 'R';
}

void insert(char* string, int s) {
    int length = strlen(string);
    int u = 1;
    for (int i = 0; i < length; ++ i) {
        int key = get_key(string[i]);
        if (children[u][key] == 0) {
            clear(++ node_count);
            children[u][key] = node_count;
        }
        u = children[u][key];
    }
    state[u] |= s;
}

int queue[M];
void get_label() {
    queue[0] = 1;
    for (int head = 0, tail = 0; head <= tail; ++ head) {
        int u = queue[head];
        for (int i = 0; i < 2; ++ i) {
            if (children[u][i] == 0) {
                children[u][i] = fail[u] == 0 ? 1 : children[fail[u]][i];
            } else {
                int v = children[u][i];
                queue[++ tail] = v;
                int node = children[fail[u]][i];
                fail[v] = node == 0 ? 1 : node;
                state[v] |= state[fail[v]];
            }
        }
    }
}

const int MOD = 1000000000 + 7;

inline void add(int &a, int b) {
    a += b;
    if (a >= MOD) {
        a -= MOD;
    }
}

char a[N], b[N];
int dp[N][N][M][4];
int n, m;

int main() {
    int test;
    scanf("%d", &test);
    while (test --) {
        scanf("%d%d", &m, &n);
        n ++, m ++;

        initialise();
        scanf("%s%s", a, b);
        insert(a, 1);
        insert(b, 2);
        get_label();

        memset(dp, 0, sizeof(dp));
        dp[1][1][1][0] = 1;
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= m; ++ j) {
                for (int k = 1; k <= node_count; ++ k) {
                    for (int mask = 0; mask < 4; ++ mask) {
                        if (i < n) {
                            int node = children[k][0];
                            add(dp[i + 1][j][node][mask | state[node]], dp[i][j][k][mask]);
                        }
                        if (j < m) {
                            int node = children[k][1];
                            add(dp[i][j + 1][node][mask | state[node]], dp[i][j][k][mask]);
                        }
                    }
                }
            }
        }
        int answer = 0;
        for (int i = 1; i <= node_count; ++ i) {
            add(answer, dp[n][m][i][3]);
        }
        printf("%d\n", answer);
    }
    return 0;
}
