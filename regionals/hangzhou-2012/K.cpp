#include <cstdio>
#include <cstring>
#include <cmath>

const int N = 60;

int x[N], y[N], n;
int dist[N], link[N];
bool visit[N];

int get_dist(int a, int b) {
#define sqr(x) ((x) * (x))
    return sqr(x[a] - x[b]) + sqr(y[a] - y[b]);
}

int main() {
    while (scanf("%d", &n) && n > 0) {
        int s, t;
        scanf("%d%d", &s, &t);
        for (int i = 1; i <= n; ++ i) {
            scanf("%d%d", x + i, y + i);
        }
        memset(dist, 1, sizeof(dist));
        memset(visit, 0, sizeof(visit));
        memset(link, 0, sizeof(link));
        dist[s] = dist[t] = 0;
        for (int counter = 1; counter <= n; ++ counter) {
            int id = -1;
            for (int i = 1; i <= n; ++ i) {
                if (!visit[i] && (id == -1 || dist[i] < dist[id])) {
                    id = i;
                }
            }
            if (id == -1) {
                break;
            }
            visit[id] = true;
            for (int i = 1; i <= n; ++ i) {
                if (!visit[i] && get_dist(id, i) < dist[i]) {
                    dist[i] = get_dist(id, i);
                }
            }
        }
        double answer = sqrt(get_dist(s, t));
        for (int i = 1; i <= n; ++ i) {
            answer += sqrt(dist[i]);
        }
        printf("%.2f\n", answer);
    }
    return 0;
}
