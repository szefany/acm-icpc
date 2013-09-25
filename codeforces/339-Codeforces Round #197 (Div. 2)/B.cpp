#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 100000 + 10;

int a[N];
int n, m;

int main() {
    freopen("input", "r", stdin);
    scanf("%d%d", &n, &m);
    long long answer = 0;
    for (int i = 1, prev = 1; i <= m; ++ i) {
        int x;
        scanf("%d", &x);
        if (x != prev) {
            answer += (x - prev + n) % n;
        }
        prev = x;
    }
    std::cout << answer << std::endl;
    return 0;
}
