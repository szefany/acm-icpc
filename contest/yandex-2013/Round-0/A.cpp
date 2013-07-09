#include <cstdio>

int main() {
    int score[2] = {0};
    int n, m;
    scanf("%d%d", &n, &m);
    while (n --) {
        int x, y;
        scanf("%d%d", &x, &y);
        x --;
        if (y == -1) {
            score[x] ++;
        } else if (y <= m) {
            score[x] += 2;
        } else {
            score[x] += 3;
        }
    }
    printf("%d:%d\n", score[0], score[1]);
    return 0;
}
