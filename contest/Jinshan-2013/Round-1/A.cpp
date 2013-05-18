#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>

const int N = 1000000 + 1;

int sum[N];

bool is_prime[N], visit[N];

void get_prime() {
    for (int i = 2; i < N; ++ i) {
        is_prime[i] = true;
    }
    for (int i = 2; i < N; ) {
        is_prime[i] = true;
        for (int j = i + i; j < N; j += i) {
            is_prime[j] = false;
        }
        for (i ++; i < N && !is_prime[i]; ++ i);
    }
}

int main() {
    get_prime();
    for (int i = 1; i < N; ++ i) {
        sum[i] = sum[i - 1];
        if (is_prime[i]) {
            std::stringstream buffer;
            std::string string;
            buffer << i;
            buffer >> string;
            int temp = 0;
            for (int j = 0; j < string.length(); ++ j) {
                temp += string[j] - 48;
            }
            if (is_prime[temp]) {
                sum[i] ++;
            }
        }
    }
    int test, t = 0;
    scanf("%d", &test);
    while (test --) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("Case #%d: %d\n", ++ t, sum[r] - sum[l - 1]);
    }
    return 0;
}
