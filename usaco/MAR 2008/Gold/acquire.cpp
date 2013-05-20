#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 50000 + 1;

struct Data {
    long long a, b;
    Data() {}
    Data(long long a, long long b): a(a), b(b) {}
};

bool cmp(const Data &p, const Data &q) {
    return p.a > q.a;
}

Data buffer[N], data[N];
int n;

struct Range {
    int x, begin, end;
    Range() {}
    Range(int x, int begin, int end): x(x), begin(begin), end(end) {}
} queue[N];

long long dp[N];

long long calc(int x, int y) {
    return dp[x] + data[x + 1].a * data[y].b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%lld%lld", &buffer[i].a, &buffer[i].b);
    }
    std::sort(buffer + 1, buffer + n + 1, cmp);

    int size = 0;
    data[++ size] = buffer[1];
    for (int i = 2; i <= n; ++ i) {
        if (buffer[i].b > data[size].b) {
            data[++ size] = buffer[i];
        }
    }

    memset(dp, 60, sizeof(dp));
    dp[0] = 0;
    int head = 1, tail = 1;
    queue[1] = Range(0, 1, size);

    for (int i = 1; i <= size; ++ i) {
        while (queue[head].end < i) {
            head ++;
        }
        int x = queue[head].x;
        dp[i] = calc(x, i);

        while (head <= tail) {
            queue[tail].begin = std::max(i + 1, queue[tail].begin);
            int x = queue[tail].x, y = queue[tail].begin;
            if (calc(x, y) >= calc(i, y)) {
                tail --;
            } else {
                break;
            }
        }
        if (head > tail) {
            queue[++ tail] = Range(i, i, size);
        } else {
            int x = queue[tail].x, lower = queue[tail].begin, upper = queue[tail].end;
            while (lower < upper) {
                int middle = lower + upper + 1 >> 1;
                if (calc(x, middle) >= calc(i, middle)) {
                    upper = middle - 1;
                } else {
                    lower = middle;
                }
            }
            queue[tail].end = lower;
            if (lower < size) {
                queue[++ tail] = Range(i, lower + 1, size);
            }
        }
    }
    printf("%lld\n", dp[size]);
    return 0;
}
