// Codeforces Round #157 (Div. 2)
// Problem D, Little Elephant and Elections
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 15;
const int MOD = 1000000000 + 7;

long long f[N][N][2];
long long m, ans, temp;
long long total[N], memory[N];
bool visit[N];
int digits[N], number[N];

long long update () {
    long long result = 1;
    memcpy (memory, total, sizeof (total));
    for (int i = 1; i <= 6; ++ i) {
        result = (result * memory[number[i]]) % MOD;
        memory[number[i]] --;
        if (memory[number[i]] < 0) {
            memory[number[i]] = 0;
        }
    }
    return result;
}

void dfs (int u, int sum) {
    if (u > 6) {
        if (sum == 0) temp += update ();
        return;
    }
    for (int i = 0; i <= sum; ++ i) {
        number[u] = i;
        dfs (u + 1, sum - i);
    }
}

int trans (long long m) {
    int len = 0;
    while (m) {
        digits[++ len] = m % 10;
        m /= 10;
    }
    return len;
}

long long solve (int len, bool less, bool first, int remain) {
    if (len == 0) {
        return remain == 0;
    }
    if (less && f[len][remain][first] != -1) {
        return f[len][remain][first];
    }
    long long result = 0;
    int limit = less ? 9 : digits[len];
    for (int i = 0; i <= limit; ++ i) {
        if (i == 0 && first) continue;
        if (remain == 0 && (i == 4 || i == 7)) continue;
        result += solve (len - 1, less || i < limit, false, remain - (i == 4 || i == 7));
    }
    if (less) {
        f[len][remain][first] = result;
    }
    return result;
}

int main () {
    memset (f, -1, sizeof (f));
    cin >> m;
    int len = trans (m);
    for (int i = 0; i <= len; ++ i) {
        for (int j = i; j <= len; ++ j) {
            total[i] += solve (j, j < len, true, i);
        }
    }
    total[0] --;
    ans = 0;
    for (int i = 1; i <= len; ++ i) {
        for (int sum = 0; sum < i; ++ sum) {
            temp = 0;
            dfs (1, sum);
            ans = (ans + total[i] * temp) % MOD;
        }
    }
    cout << ans << endl;
    return 0;
}
