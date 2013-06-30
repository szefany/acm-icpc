#include <cstdio>
#include <cstring>

char string[5000];

int main () {
    scanf ("%s", string);
    bool same = true;
    int length = strlen (string);
    for (int i = 1; i < length; ++ i) {
        same &= string[i] == string[i - 1];
    }
    if (same) {
        printf ("%d\n", length);
        return 0;
    }
    int sum = 0;
    for (int i = 0; i < length; ++ i) {
        sum ^= string[i] - 'a' + 1;
    }
    printf ("%d\n", sum == 0 ? 2 : 1);
    return 0;
}
