#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100000 + 10;

char string[N], queue[N];

int main() {
    freopen("clumsy.in", "r", stdin);
    freopen("clumsy.out", "w", stdout);
    scanf("%s", string);
    int n = strlen(string);
    int length = 0;
    for (int i = 0; i < n; ++ i) {
        if (string[i] == '(') {
            queue[++ length] = '(';
        } else if (length && queue[length] == '(') {
            length --;
        } else {
            queue[++ length] = ')';
        }
    }
    int a = 0;
    int b = 0;
    for (int i = 1; i <= length; ++ i) {
        a += queue[i] == '(';
        b += queue[i] == ')';
    }
    int answer = length / 2 + (a & 1);
    printf("%d\n", answer);
    return 0;
}
