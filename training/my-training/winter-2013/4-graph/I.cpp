// POJ 3687, Labeling Balls
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

const int N = 200;

std::vector <int> neighbors[N];
int answer[N], degree[N];
int n, m;

struct cmp {
    bool operator () (int x, int y) {
        return x < y;
    }
};

void initialise () {
    memset (degree, 0, sizeof (degree));
    for (int i = 0; i < n; ++ i) {
        neighbors[i].clear();
    }
}

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        scanf ("%d%d", &n, &m);
        initialise ();
        for (int i = 0; i < m; ++ i) {
            int u, v;
            scanf ("%d%d", &u, &v);
            u --, v --;
            neighbors[v].push_back (u);
            degree[u] ++;
        }
        std::priority_queue <int, std::vector <int>, cmp> queue;
        for (int i = 0; i < n; ++ i) {
            if (degree[i] == 0) {
                queue.push (i);
            }
        }
        int counter = 0;
        for (int number = n; !queue.empty(); number --) {
            int u = queue.top();
            queue.pop();
            answer[u] = number;
            counter ++;
            for (int i = 0; i < neighbors[u].size(); ++ i) {
                int v = neighbors[u][i];
                degree[v] --;
                if (degree[v] == 0) {
                    queue.push (v);
                }
            }
        }
        if (counter < n) {
            puts ("-1");
        } else {
            for (int i = 0; i < n; ++ i) {
                printf ("%d%c", answer[i], i == n - 1 ? '\n' : ' ');
            }
        }
    }
    return 0;
}
