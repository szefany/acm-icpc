#include <cstdio>
#include <set>

#define foreach(i, v) for (__typeof((v).begin) i = (v).begin(); i != (v).end(); ++ i)

int get_length(int x) {
    int result = 0;
    while (x) {
        result ++;
        x /= 10;
    }
    return result;
}

const int N = 1000000 + 10;
const int L = 40;

bool visit[N];
int queue[2][N], tail[2], from[N][2];

int answer[L];

void print(int x) {
    int length = 0;
    answer[++ length] = from[x][0];
    x = from[x][1];
    while (x) {
        answer[++ length] = from[x][0];
        x = from[x][1];
    }
    for (int i = length; i >= 1; -- i) {
        putchar(answer[i] + '0');
    }
    puts("");
}

int main() {
    int n;
    scanf("%d", &n);
    if (n <= 2) {
        printf("%d\n", n);
        return 0;
    }

    visit[1] = visit[2] = true;
    queue[0][1] = 1;
    queue[0][2] = 2;
    tail[0] = 2; 
    from[1][0] = 1, from[1][1] = 0;
    from[2][0] = 2, from[2][1] = 0;
    for (int length = 1; length <= 29; ++ length) {
        int now = length & 1;
        tail[now] = 0;
        for (int i = 1; i <= tail[now ^ 1]; ++ i) {
            int x = queue[now ^ 1][i];
            int y = (x * 10 + 1) % n;
            if (!visit[y]) {
                visit[y] = true;
                queue[now][++ tail[now]] = y;
                from[y][0] = 1;
                from[y][1] = x;
                if (y == 0) {
                    print(y);
                    return 0;
                }
            }
            y = (x * 10 + 2) % n;
            if (!visit[y]) {
                visit[y] = true;
                queue[now][++ tail[now]] = y;
                from[y][0] = 2;
                from[y][1] = x;
                if (y == 0) {
                    print(y);
                    return 0;
                }
            }
        }
        if (tail[now] == 0) {
            break;
        }
    }
    puts("Impossible");
    return 0;
}
