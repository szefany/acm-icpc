#include <cstdio>
#include <cstring>
#include <iostream>
 
const int N = 1000000 + 10;
const int INF = 100;
const int MOD = 1000000000 + 7;
 
int children[N][2], queue[N], match[N], father[N];
int node_count;
char priority[N], string[N];
 
char trans(char token) {
    if (token == '~') {
        return 1;
    }
    if (token == '&') {
        return 2;
    }
    if (token == '|') {
        return 3;
    }
    return 0;
}
 
#define L(u) (children[(u)][0])
#define R(u) (children[(u)][1])
 
int solve(int left, int right, int start) {
    if (string[left] == '(' && string[right] == ')' && match[right] == left) {
        return solve(left + 1, right - 1, start);
    }
    int last = start;
    priority[start] = INF;
    int pivot = left;
    while (pivot <= right) {
        while (pivot <= right && (string[pivot] == 'x' || string[pivot] >= '0' && string[pivot] <= '9')) {
            pivot ++;
        }
        if (pivot > right) {
            break;
        }
        int next;
        if (string[pivot] == '(') {
            next = ++ node_count;
            solve(pivot + 1, match[pivot] - 1, node_count);
            priority[next] = 0;
            pivot = match[pivot] + 1;
        } else {
            next = ++ node_count;
            priority[next] = trans(string[pivot]);
            pivot ++;
        }
        while (last != start && priority[next] > priority[last]) {
            last = father[last];
        }
        L(next) = R(last);
        R(last) = next;
        father[next] = last;
        last = next;
    }
    return R(start);
}
 
long long dp[N][2];
 
void get_answer(int u) {
    if (u == 0) {
        dp[0][0] = dp[0][1] = 1;
        return;
    }
    get_answer(L(u));
    get_answer(R(u));
    if (priority[u] == 0) {
        dp[u][0] = dp[R(u)][0];
        dp[u][1] = dp[R(u)][1];
    } else if (priority[u] == 1) {
        dp[u][0] = dp[R(u)][1];
        dp[u][1] = dp[R(u)][0];
    } else if (priority[u] == 2) {
        dp[u][1] = dp[L(u)][1] * dp[R(u)][1] % MOD;
        dp[u][0] = dp[L(u)][0] * dp[R(u)][0] % MOD;
        (dp[u][0] += dp[L(u)][0] * dp[R(u)][1]) %= MOD;
        (dp[u][0] += dp[L(u)][1] * dp[R(u)][0]) %= MOD;
    } else {
        dp[u][0] = dp[L(u)][0] * dp[R(u)][0] % MOD;
        dp[u][1] = dp[L(u)][1] * dp[R(u)][1] % MOD;
        (dp[u][1] += dp[L(u)][0] * dp[R(u)][1]) %= MOD;
        (dp[u][1] += dp[L(u)][1] * dp[R(u)][0]) %= MOD;
    }
}
 
int main() {
    scanf("%s", string + 1);
    int n = strlen(string + 1);
     
    int length = 0;
    for (int i = 1; i <= n; ++ i) {
        if (string[i] == '(') {
            queue[++ length] = i;
        } else if (string[i] == ')') {
            int x = queue[length --];
            match[i] = x;
            match[x] = i;
        }
    }
     
    int root = solve(1, n, 0);
     
    /*
    for (int u = 1; u <= node_count; ++ u) {
        printf("%d: %d %d %d %d\n", u, father[u], priority[u], L(u), R(u));
    }
    */
    get_answer(root);   
    std::cout << dp[root][1] << std::endl;
    return 0;
}
