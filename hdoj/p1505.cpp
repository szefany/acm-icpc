#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 1000 + 10;

int height[N], queue[N][2];
int n, m;

int main() {
    freopen("input", "r", stdin);
    int test;
    scanf("%d", &test);
    while (test --) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= m; ++ i) {
            height[i] = 0;
        }
        int answer = 0;
        for (int i = 1; i <= n; ++ i) {
            queue[0][0] = queue[0][1] = 0;
            int length = 0;
            for (int j = 1; j <= m; ++ j) {
                char buffer[2];
                scanf("%s", buffer);
                if (*buffer == 'F') {
                    height[j] ++;
                } else {
                    height[j] = 0;
                }
                while (length >= 0) {
                    int h = queue[length][0];
                    int x = queue[length][1];
                    if (height[j] >= h) {
                        length ++;
                        queue[length][0] = height[j];
                        queue[length][1] = j;
                        break;
                    } else {
                        answer = std::max(answer, h * (j - x));
                        length --;
                    }
                }
            }
            for (int j = length; j > 0; -- j) {
                int h = queue[j][0];
                int x = queue[j][1];
                answer = std::max(answer, h * (m - x + 1));
            }
        }
        printf("%d\n", answer * 3);
    }
    return 0;
}
