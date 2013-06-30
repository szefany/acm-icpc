#include <cstdio>
#include <map>

std::map<char, int> power;

int solve() {
    bool b = false, c = false;
    int n, result = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        char buffer[2];
        scanf("%s", buffer);
        result += power[buffer[0]];
        if (buffer[0] == 'B') {
            b = true;
        } else if (buffer[0] == 'C') {
            c = true;
        }
    }
    if (!b || !c) {
        result --;
    }
    return std::max(1, result);
}

int main() {
    power['A'] = 16;
    power['B'] = 7;
    power['C'] = 8;
    power['D'] = power['E'] = 1;
    power['F'] = 2;
    power['G'] = 3;
    int test;
    scanf("%d", &test);
    while (test --) {
        int x = solve();
        int y = solve();
        if (x == y) {
            puts("tie");
        } else {
            puts(x > y ? "red" : "black");
        }
    }
    return 0;
}
