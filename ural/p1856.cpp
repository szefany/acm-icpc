#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

const int N = 1000 + 10;
const int M = N * N * 2;

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

struct Edge {
    int a, b, next;
    Edge(int a = 0, int b = 0, int next = 0):
        a(a), b(b), next(next) {
    }
} g[M];
int first[N][N], edge_count;

int next[N][2];
int n;

struct Data {
    int a, b, state;
    Data(int a = 0, int b = 0, int state = 0):
        a(a), b(b), state(state) {
    }
} queue[M];

bool visit[N][N][2];
char count[N][N][2];

void push(int a, int b, int state, int& tail) {
    if (!visit[a][b][state]) {
        visit[a][b][state] = true;
        queue[++ tail] = Data(a, b, state);
    }
}

void add_edge(int a, int b, int c, int d) {
    edge_count ++;
    g[edge_count] = Edge(c, d, first[a][b]), first[a][b] = edge_count;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 0; j < 2; ++ j) {
            scanf("%d", &next[i][j]);
        }
    }

    for (int a = 1; a <= n; ++ a) {
        for (int b = a; b <= n; ++ b) {
            for (int i = 0; i < 2; ++ i) {
                int c = next[a][i];
                int d = next[b][i];
                if (c > d) {
                    std::swap(c, d);
                }
                add_edge(c, d, a, b);
            }
        }
    }

    int tail = 0;
    for (int i = 1; i <= n; ++ i) {
        for (int state = 0; state < 2; ++ state) {
            push(i, i, state, tail);
        }
    }
    for (int head = 1; head <= tail; ++ head) {
        int a = queue[head].a;
        int b = queue[head].b;
        int state = queue[head].state;
        for (int iter = first[a][b]; iter; iter = g[iter].next) {
            int c = g[iter].a;
            int d = g[iter].b;
            if (state == 1) {
                push(c, d, state ^ 1, tail);
            } else {
                count[c][d][state ^ 1] ++;
                if (count[c][d][state ^ 1] == 2) {
                    push(c, d, state ^ 1, tail);
                }
            }
        }
    }

    bool flag = true;
    for (int i = 1; i <= n && flag; ++ i) {
        for (int j = i + 1; j <= n && flag; ++ j) {
            if (!visit[i][j][0]) {
                flag = false;
            }
        }
    }
    puts(flag ? "War" : "Peace");
    return 0;
}
