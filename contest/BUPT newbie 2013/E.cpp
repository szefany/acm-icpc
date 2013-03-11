// Frog, BUPT Newbie 2013
#include <iostream>
#include <cstdio>
#include <queue>

const int N = 30000;

int n, m;
int dist[N], extra[N], supply[N];

int main () {
    freopen ("input", "r", stdin);
    int test_count;
    scanf ("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        scanf ("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) {
            scanf ("%d", &dist[i]);
        }
        for (int i = 0; i < n; ++ i) {
            scanf ("%d", &supply[i]);
        }
        for (int i = 0; i < n; ++ i) {
            scanf ("%d", &extra[i]);
        }
        long long answer = 0;
        std::priority_queue <int> queue;
        for (int energy = 0, i = 0; i < n; ++ i) {
            energy += supply[i];
            queue.push (extra[i]);
            while (energy < dist[i] && !queue.empty()) {
                int x = queue.top();
                queue.pop();
                energy += x;
                answer += m;
            }
            if (energy < dist[i]) {
                answer = -1;
                break;
            }
            energy -= dist[i];
            answer += dist[i];
        }
        printf ("Case %d: ", t);
        if (answer == -1) {
            puts ("impossible");
        } else {
            std::cout << answer << std::endl;
        }
    }
    return 0;
}
