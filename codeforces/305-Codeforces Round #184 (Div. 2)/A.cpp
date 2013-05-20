#include <cstdio>
#include <vector>

std::vector<int> number[6];
int main() {
    int n;
    scanf("%d", &n);
    int a = 0, b = 0, c = 0, d = 0, e = 0;
    for (int i = 0; i < n; ++ i) {
        int x;
        scanf("%d", &x);
        if (x == 100) {
            a ++;
            number[0].push_back(x);
        } else if (x >= 10 && x % 10 == 0) {
            b ++;
            number[1].push_back(x);
        } else if (x >= 10) {
            c ++;
            number[2].push_back(x);
        } else if (x > 0) {
            d ++;
            number[3].push_back(x);
        } else {
            e ++;
            number[4].push_back(x);
            number[5].push_back(x);
        }
    }
    int answer = e;
    if (a > 0) {
        answer ++;
        number[5].push_back(number[0][0]);
    }
    if (b > 0) {
        answer ++;
        number[5].push_back(number[1][0]);
    }
    if (d > 0) {
        answer ++;
        number[5].push_back(number[3][0]);
    }
    if (b == 0 && d == 0 && c > 0) {
        answer ++;
        number[5].push_back(number[2][0]);
    }
    printf("%d\n", (int)number[5].size());
    for (int i = 0; i < number[5].size(); ++ i) {
        printf("%d%c", number[5][i], i + 1 == number[5].size() ? '\n' : ' ');
    }
    return 0;
}
