#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <iostream>

const int N = 1000 + 10;

std::map<std::string, int> name;
std::vector<int> neighbors[N];
int ancestor[N];
int n, answer;

int find(int u) {
    int root = u;
    while (root != ancestor[root]) {
        root = ancestor[root];
    }
    while (u != root) {
        int temp = ancestor[u];
        ancestor[u] = root;
        u = temp;
    }
    return root;
}

void joint(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) {
        ancestor[u] = v;
    }
}

bool visit[N];

void dfs(int u, int depth) {
    answer = std::max(answer, depth);
    visit[u] = true;
    for (int i = 0; i < neighbors[u].size(); ++ i) {
        int v = neighbors[u][i];
        if (!visit[v]) {
            dfs(v, depth + 1);
        }
    }
}

int dist[N], queue[N + N];
void spfa(int vs, int &t, int &answer) {
    static const int Q = N + 10;
    memset(dist, 1, sizeof(dist));
    memset(visit, 0, sizeof(visit));
    queue[1] = vs;
    visit[vs] = true;
    dist[vs] = 0;
    for (int head = 0, tail = 1; head < tail; ) {
        head = head % Q + 1;
        int u = queue[head];
        visit[u] = false;
        for (int i = 0; i < neighbors[u].size(); ++ i) {
            int v = neighbors[u][i];
            if (dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                if (!visit[v]) {
                    visit[v] = true;
                    tail = tail % Q + 1;
                    queue[tail] = v;
                }
            }
        }
    }
    t = -1;
    for (int i = 0; i < n; ++ i) {
        if (t == -1 || dist[i] > dist[t]) {
            t = i;
        }
    }
    answer = std::max(answer, dist[t]);
}

int main() {
    while (scanf("%d", &n) && n > 0) {
        for (int i = 0; i < n; ++ i) {
            neighbors[i].clear();
            ancestor[i] = i;
        }
        name.clear();
        for (int i = 0; i < n; ++ i) {
            char buffer[15];
            scanf("%s", buffer);
            name[buffer] = i;
        }
        int m;
        scanf("%d", &m);
        while (m --) {
            char buffer[2][15];
            scanf("%s %s", buffer[0], buffer[1]);
            int u = name[buffer[0]];
            int v = name[buffer[1]];
            neighbors[u].push_back(v);
            neighbors[v].push_back(u);
            joint(u, v);
        }

        int counter = 0;
        for (int i = 0; i < n; ++ i) {
            counter += find(i) == i;
        }
        if (counter > 1) {
            printf("-1\n");
            continue;
        }
        answer = 0;
        /*
        for (int i = 0; i < n; ++ i) {
            memset(visit, 0, sizeof(visit));
            dfs(i, 0);
        }
        */
        for (int i = 0; i < n; ++ i) {
            int temp;
            spfa(i, temp, answer);
        }
        printf("%d\n", answer);
    } 
    return 0;
}
