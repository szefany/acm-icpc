#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100 + 10;

char string[N], total[N];

int main() {
    scanf("%s", string);
    int length = strlen(string);
    int result = 0;
    for (int i = 0; i < length; i += 2) {
        total[result ++] = string[i];
    }
    std::sort(total, total + result);
    for (int i = 0; i < result; ++ i) {
        printf("%c%c", total[i], i + 1 == result ? '\n' : '+');
    }
    return 0;
}
