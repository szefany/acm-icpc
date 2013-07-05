#include <cstdio>
#include <iostream>
#include <cstring>

const int N = 100000 + 10;
const int MOD = 1000000000 + 7;

char string[N];
int k, n;

long long power(long long x, long long y) {
    if (y == 0) {
        return 1;
    }
    long long result = power(x, y >> 1);
    result = result * result % MOD;
    if (y & 1) {
        result = result * x % MOD;
    }
    return result;
}

long long calc(long long x) {
    long long y = x + (long long)n * k + n;
    long long result = ((power(2, y) - power(2, x)) % MOD + MOD) % MOD;
    return result;
}

long long inverse(long long a) {
    return a == 1 ? 1 : (long long)(MOD - MOD / a) * inverse(MOD % a) % MOD;
}


int main() {
    scanf("%s%d", string + 1, &k);
    k --;
    long long answer = 0;
    n = strlen(string + 1);
    for (int i = 1; i <= n; ++ i) {
        if (string[i] == '0' || string[i] == '5') {
            (answer += calc(i - 1)) %= MOD;
        }
    }
    long long x = ((power(2, n) - 1) % MOD + MOD) % MOD;
    answer = answer * inverse(x) % MOD;
    std::cout << answer << std::endl;
    return 0;
}
