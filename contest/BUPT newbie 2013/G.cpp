// Standard, BUPT Newbie 2013
#include <cstdio>
#include <vector>

#define foreach(i, v) for (__typeof ((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

using std::make_pair;

const int N = 300 + 5;
const int INF = 1 << 30;

typedef std::pair<int, int> Pair;

std::vector <Pair> neighbors[N];
bool visit[N];
int single[N], cost[N];
int n, m;

void initialise () {
    for (int i = 0; i <= n; ++ i) {
        neighbors[i].clear ();
    }
}

int solve (int x) {
    for (int i = 0; i < n; ++ i) {
        if (i != x) {
            cost[i] = INF;
            visit[i] = false;
        }
    }
    visit[x] = true;
    cost[0] = 0;
    int result = 0;
    for (int counter = 1; counter < n; ++ counter) {
        int id = -1;
        for (int i = 0; i < n; ++ i) {
            if (!visit[i] && (id == -1 || cost[i] < cost[id])) {
                id = i;
            }
        }
        if (id == -1) {
            break;
        }
        visit[id] = true;
        result += cost[id];
        foreach (iter, neighbors[id]) {
            int v = (*iter).first, w = (*iter).second;
            if (!visit[v] && cost[v] > w) {
                cost[v] = w;
            }
        }
    }
    return result;
}

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        scanf ("%d%d", &n, &m);
        initialise ();
        for (int i = 1; i <= n; ++ i) {
            scanf ("%d", &single[i]);
            neighbors[0].push_back (make_pair (i, single[i]));
            neighbors[i].push_back (make_pair (0, single[i]));
        }
        for (int i = 0; i < m; ++ i) {
            int u, v, w;
            scanf ("%d%d%d", &u, &v, &w);
            neighbors[u].push_back (make_pair (v, w));
            neighbors[v].push_back (make_pair (u, w));
        }
        n ++;
        int answer = INF;
        for (int i = 1; i < n; ++ i) {
            answer = std::min (answer, solve (i));
            // printf ("%d\n", solve (i));
        }
        printf ("%d\n", answer);
    }
    return 0;
}
