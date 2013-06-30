#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 1000000 + 1;

int sum[N], left[N], a[N];
long long answer[N];
int n;

int lowbit(int x) {
    return x & -x;
}

void insert(int x) {
    while (x <= n) {
        sum[x] ++;
        x += lowbit(x);
    }
}

int get_sum(int x) {
    int result = 0;
    while (x) {
        result += sum[x];
        x -= lowbit(x);
    }
    return result;
}

bool visit[N];

int main() {
    while (scanf("%d", &n) && n > 0) {
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &a[i]);
        }
        memset(sum, 0, sizeof(sum));
        memset(left, 0, sizeof(left));
        memset(visit, 0, sizeof(visit));
        for (int i = 1; i <= n; ++ i) {
            insert(i - left[a[i]]);
            left[a[i]] = i;
        }

        int count = 0;

        answer[0] = 0;
        for (int i = 1; i <= n; ++ i) {
            answer[i] = answer[i - 1] + get_sum(n) - get_sum(i - 1) - count;
            if (!visit[a[n - i + 1]]) {
                count ++;
                visit[a[n - i + 1]] = true;
            }
        }

        int q;
        scanf("%d", &q);
        while (q --) {
            int x;
            scanf("%d", &x);
            std::cout << answer[x] << '\n';
        }
    }
    return 0;
}
