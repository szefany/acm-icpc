#include <cstdio>
#include <cstring>

const int N = 1000 + 10;

int answer[N];

int main() {
    freopen("input", "r", stdin);
    char has[20];
    scanf("%s", has + 1);
    int m;
    scanf("%d", &m);

    for (int start = 1; start <= 10; ++ start) {
        if (has[start] == '0') {
            continue;
        }
        int last = start;
        answer[0] = start;
        int sum[2];
        sum[0] = start;
        sum[1] = 0;
        bool flag = true;
        for (int counter = 1; counter < m; ++ counter) {
            int now = counter & 1;
            int weight = -1;
            for (int i = 1; i <= 10; ++ i) {
                if (last != i && has[i] == '1' && sum[now] + i > sum[now ^ 1]) {
                    weight = i;
                    break;
                }
            }
            if (weight == -1) {
                flag = false;
                break;
            }
            sum[now] += weight;
            last = weight;
            answer[counter] = weight;
        }
        if (flag) {
            puts("YES");
            for (int i = 0; i < m; ++ i) {
                printf("%d%c", answer[i], i + 1 == m ? '\n' : ' ');
            }
            return 0;
        }
    }
    puts("NO");
    return 0;
}
