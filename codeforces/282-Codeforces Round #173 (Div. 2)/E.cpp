#include <cstdio>
#include <iostream>

const int N = 100000;
const int D = 40;
const int T = N * D;

int children[T][2], covered[T];
int size;

long long elements[N], prefix[N];
int n;

void insert (long long value) {
    for (int i = D - 1, u = 0; i >= 0; -- i) {
        int x = (value & (1LL) << i) > 0;
        if (children[u][x] == 0) {
            children[u][x] = ++ size;
        }
        u = children[u][x];
        covered[u] ++;
    }
}

void erase (long long value) {
    for (int i = D - 1, u = 0; i >= 0; -- i) {
        int x = (value & (1LL) << i) > 0;
        u = children[u][x]; 
        covered[u] --;
    }
}

long long get_value (long long value) {
    long long result = 0;
    for (int i = D - 1, u = 0; i >= 0; -- i) {
        int x = (value & (1LL) << i) > 0;
        int v = children[u][x ^ 1];
        if (v && covered[v]) {
            result += (1LL) << i;
        } else {
            x ^= 1;
        }
        u = children[u][x ^ 1];
    }
    return result;
}

int main () {
    scanf ("%d", &n);
    insert (0);
    for (int i = 0; i < n; ++ i) {
        std::cin >> elements[i];
        prefix[i] = i == 0 ? elements[i] : prefix[i - 1] ^ elements[i];
        insert (prefix[i]);
    }

    long long answer = get_value (0), current = 0;
    for (int i = n - 1; i >= 0; -- i) {
        current ^= elements[i];
        erase (prefix[i]);
        answer = std::max (answer, get_value (current));
    }
    std::cout << answer << std::endl;
    return 0;
}
