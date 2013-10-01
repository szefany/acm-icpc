#include <cstdio>
#include <cstring>
#include <bitset>
#include <vector>

const int N = 10000 + 10;
const int D = 20;

long long belongs[N][D];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        int amount;
        scanf("%d", &amount);
        while (amount --) {
            int x;
            scanf("%d", &x);
            belongs[x][i / 60] |= (1LL) << (i % 60);
        }
    }
    int q;
    scanf("%d", &q);
    while (q --) {
        int a, b;
        scanf("%d%d", &a, &b);
        bool found = false;
        for (int i = 0; i <= n / 60 && !found; ++ i) {
            found |= (belongs[a][i] & belongs[b][i]) > 0;
        }
        puts(found ? "Yes" : "No");
    }
    return 0;
}
