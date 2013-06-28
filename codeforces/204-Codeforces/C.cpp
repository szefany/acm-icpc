#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

const int N = 222222;
const int M = 26;

char a[N], b[N];
int next[N], position[M];
long long left[N], right[N];
int n;

int queue[N];
int current[M];

double process() {
    memset(next, 1, sizeof(next));
    memset(position, 1, sizeof(position));
    memset(left, 0, sizeof(left));
    for (int i = n; i > 0; -- i) {
        int key = b[i] - 'A';
        next[i] = position[key];
        position[key] = i;
    }
    for (int key = 0; key < M; ++ key) {
        int length = 0;
        for (int u = position[key]; u <= n; u = next[u]) {
            queue[++ length] = u;
        }
        for (int i = 1; i <= length; ++ i) {
            int u = queue[i];
            left[u] = u + (i == 1 ? 0 : left[queue[i - 1]]);
        }
    }

    for (int token = 0; token < M; ++ token) {
        current[token] = position[token];
    }
    double result = 0;
    for (int i = 1; i <= n; ++ i) {
        int key = a[i] - 'A';
        if (current[key] < i) {
            while (next[current[key]] < i) {
                current[key] = next[current[key]];
            }
            result += (long long)(n - i + 1) * left[current[key]];
        }
    }
    return result;
}

int main() {
    scanf("%d", &n);
    scanf("%s%s", a + 1, b + 1);

    double total = 0;
    for (long long i = 1; i <= n; ++ i) {
        total += i * i;
    }

    double count = 0;
    count += process();
    std::reverse(a + 1, a + n + 1);
    std::reverse(b + 1, b + n + 1);
    count += process();
    for (int i = 1; i <= n; ++ i) {
        if (a[i] == b[i]) {
            count += (long long)i * (n - i + 1);
        }
    }
    printf("%.10f\n", count / total);
    return 0;
}
