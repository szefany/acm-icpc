#include <cstdio>
#include <vector>

const int M = 200;
const int S = 1 << 20;
const int INF = 1 << 29;

std::vector<int> elements[M];
int price[M];
int n;

int cost[S];

int main() {
    scanf("%d", &n);
    int m = 0;
    for (int i = 0; i < n; ++ i) {
        scanf("%d", price + i);
        elements[m ++].push_back(i);
    }
    int delta;
    scanf("%d", &delta);
    for (int i = m; i < m + delta; ++ i) {
        scanf("%d", price + i);
        int amount;
        scanf("%d", &amount);
        while (amount --) {
            int x;
            scanf("%d", &x);
            elements[i].push_back(x - 1);
        }
    }
    m += delta;
    int target = 0;
    int amount;
    scanf("%d", &amount);
    while (amount --) {
        int x;
        scanf("%d", &x);
        x --;
        target |= 1 << x;
    }
    for (int mask = 0; mask < 1 << n; ++ mask) {
        cost[mask] = INF;
    }
    int answer = INF;
    cost[0] = 0;
    for (int mask = 0; mask < 1 << n; ++ mask) {
        if ((target & mask) == target) {
            answer = std::min(answer, cost[mask]);
        }
        for (int i = 0; i < m; ++ i) {
            int new_mask = mask;
            for (int j = 0; j < (int)elements[i].size(); ++ j) {
                int x = elements[i][j];
                new_mask |= 1 << x;
            }
            cost[new_mask] = std::min(cost[new_mask], cost[mask] + price[i]);
        }
    }
    printf("%d\n", answer);
    return 0;
}
