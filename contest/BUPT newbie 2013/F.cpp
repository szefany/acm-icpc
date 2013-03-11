// Rythm, BUPT Newbie 2013
#include <cstdio>

const int N = 1000;

int elements[N], next[N];
int n;

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        scanf ("%d", &n);
        for (int i = 0, prev = -1; i < n; ++ i) {
            int value;
            scanf ("%d", &value);
            if (prev != -1) {
                elements[i - 1] = value - prev;
            }
            prev = value;
        }
        n --;
        int answer = 0;
        for (int x = 0; x < n; ++ x) {
            next[x] = x - 1;
            for (int i = x + 1, j = x - 1; i < n; ++ i) {
                while (j >= x && elements[i] != elements[j + 1]) {
                    j = next[j];
                }
                j += (elements[i] == elements[j + 1]);
                next[i] = j;
            }
            for (int i = 0, j = x - 1, temp = 0; i + 1 < x && j < n; ++ i) {
                while (j >= x && elements[i] != elements[j + 1]) {
                    j = next[j];
                }
                j += (elements[i] == elements[j + 1]);
                temp = j - x + 1;
                if (temp > answer) {
                    answer = temp;
                }
            }
        }
        if (answer < 4) {
            puts ("0");
        } else {
            printf ("%d\n", answer + 1);
        }
    }
    return 0;
}
