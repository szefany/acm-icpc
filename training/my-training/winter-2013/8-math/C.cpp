// HDU 3032, Nim or not Nim?
#include <cstdio>
#include <cstring>

int sg (int x) {
    long long result;
    if (x % 4 == 0) {
        result = x - 1;
    } else if (x % 4 == 3) {
        result = x + 1;
    } else {
        result = x;
    }
    return result;
}

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        int n, answer = 0;
        scanf ("%d", &n);
        for (int i = 0; i < n; ++ i) {
            int x;
            scanf ("%d", &x);
            answer ^= sg (x);
        }
        puts (answer ? "Alice" : "Bob");
    }
    return 0;
}
