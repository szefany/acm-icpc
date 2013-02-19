#include <iostream>
#include <cstdio>
#include <cstring>

const int N = 400000;

long long row[N], col[N];

int main () {
    int n, q;
    scanf ("%d%d", &n, &q);
    for (int i = 0; i < q; ++ i) {
        char buffer[10];
        int index, value;
        scanf ("%s%d%d", buffer, &index, &value);
        if (*buffer == 'R') {
            row[index] += value;
        } else {
            col[index] += value;
        }
    }
    long long a = 0, b = 0;
    for (int i = 1; i <= n; ++ i) {
        a = std::max (a, row[i]);
        b = std::max (b, col[i]);
    }
    std::cout << a + b << std::endl;
    return 0;
}
