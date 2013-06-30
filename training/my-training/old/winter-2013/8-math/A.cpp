// HDU 1850, Being a Good Boy in Spring Festival
#include <cstdio>

int n;
int elements[100];

int main () {
    while (scanf ("%d", &n) != EOF && n > 0) {
        int value = 0;
        for (int i = 0; i < n; ++ i) {
            scanf ("%d", &elements[i]);
            value ^= elements[i];
        }
        int answer = 0;
        for (int i = 0; i < n; ++ i) {
            answer += (value ^ elements[i]) < elements[i];
        }
        printf ("%d\n", answer);
    }
    return 0;
}
