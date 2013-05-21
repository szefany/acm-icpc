#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>

const int N = 50000 + 1;

int key[N], child[N][2], dist[N], rightmost[N], node_count;
int value[N], root[N], n;

#define L(u) child[(u)][0]
#define R(u) child[(u)][1]

int merge(int u, int v) {
    if (u == 0 || v == 0) {
        return u ^ v;
    }
    if (key[u] < key[v]) {
        std::swap(u, v);
    }
    R(u) = merge(R(u), v);
    if (dist[L(u)] < dist[R(u)]) {
        std::swap(L(u), R(u));
    }
    dist[u] = dist[R(u)] + 1;
    return u;
}

int pop(int u) {
    u = merge(L(u), R(u));
    return u;
}

void initialise() {
    node_count = 0;
    memset(key, 0, sizeof(key));
    memset(dist, 0, sizeof(dist));
    memset(root, 0, sizeof(root));
    memset(child, 0, sizeof(child));
    memset(rightmost, 0, sizeof(rightmost));
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int main() {
    while (scanf("%d", &n) && n > 0) {
        initialise();
        int length = 0;
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &value[i]);
            node_count ++;
            key[node_count] = value[i];
            dist[node_count] = -1;

            length ++;
            root[length] = node_count;
            rightmost[length] = i;

            while (length > 1 && key[root[length]] < key[root[length - 1]]) {
                length --;
                root[length] = merge(root[length], root[length + 1]);
                if ((rightmost[length + 1] - rightmost[length] & 1) && (rightmost[length] - rightmost[length - 1] & 1)) {
                    root[length] = pop(root[length]);
                }
                rightmost[length] = rightmost[length + 1];
            }
        }
        long long answer = 0;
        for (int i = 1, current = 1; i <= length; ++ i) {
            for (int j = current; j <= rightmost[i]; ++ j) {
                answer += abs(value[j] - key[root[i]]);
            }
            current = rightmost[i] + 1;
        }
        printf("%lld\n", answer);
    }
    return 0;
}
