#include <cstdio>
#include <algorithm>

const int N = 500 + 10;

struct Data {
    int a, b, id;
    void input(int i) {
        scanf("%d%d", &a, &b);
        id = i;
    }
    bool operator < (const Data &o) const {
        return b < o.b;
    }
} data[N];

int dp[N], from[N];
int n;

int answer[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        data[i].input(i);
    }
    std::sort(data + 1, data + n + 1);

    int id = 0;
    for (int i = 1; i <= n; ++ i) {
        dp[i] = 1;
        from[i] = 0;
        for (int j = 1; j < i; ++ j) {
            if (data[j].a > data[i].a && data[j].b < data[i].b && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                from[i] = j;
            }
        }
        if (dp[i] > dp[id]) {
            id = i;
        }
    }
    printf("%d\n", dp[id]);
    int length = 0;
    for (int now = id; now; now = from[now]) {
        answer[++ length] = data[now].id;
    }
    for (int i = length; i >= 1; -- i) {
        printf("%d%c", answer[i], i == 1 ? '\n' : ' ');
    }
    return 0;
}
