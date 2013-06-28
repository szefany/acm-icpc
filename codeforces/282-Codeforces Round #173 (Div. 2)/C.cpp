#include <cstdio>
#include <cstring>

const int N = 1000000 + 10;

char a[N], b[N];

int main() {
    scanf("%s", a);
    scanf("%s", b);
    int len_1 = strlen(a);
    int len_2 = strlen(b);
    bool flag = len_1 == len_2;
    bool has_a = false, has_b = false;
    for (int i = 0; i < len_1; ++ i) {
        has_a |= a[i] == '1';
        has_b |= b[i] == '1';
    }
    flag &= (has_a == has_b);
    puts(flag ? "YES" : "NO");
    return 0;
}
