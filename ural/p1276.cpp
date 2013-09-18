#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 50;

long long comb[N][N];
int amount[4];
int n, k;

long long combine(int a, int b) {
    return b == 0 ? 1 : comb[a][b];
}

int main() {
    comb[0][0] = 1;
    for (int i = 1; i < N; ++ i) {
        comb[i][0] = 1;
        for (int j = 1; j < N; ++ j) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
        }
    }
    scanf("%d%d", &n, &k);
    char string[3];
    scanf("%s", string);
    for (int i = 0; i < n; ++ i) {
        char buffer[3];
        scanf("%s", buffer);
        if (strcmp(buffer, "AA") == 0) {
            amount[0] ++;
        } else if (strcmp(buffer, "AB") == 0) {
            amount[1] ++;
        } else if (strcmp(buffer, "BA") == 0) {
            amount[2] ++;
        } else {
            amount[3] ++;
        }
    }
    long long answer = 0;
    if (strcmp(string, "BA") == 0) {
        // A ... B
        for (int x = 0; x <= amount[1]; ++ x) {
            int y = x - 1;
            if (y < 0 || y > amount[2]) {
                continue;
            }
            int c = x;
            int d = x;
            for (int z = 0; z <= amount[0]; ++ z) {
                int p = k - x - y - z;
                if (p < 0 || p > amount[3]) {
                    continue;
                }
                answer += combine(c + z - 1, z) * combine(d + p - 1, p);
            }
        }
    } else if (strcmp(string, "AB") == 0) {
        // B ... A
        for (int y = 0; y <= amount[2]; ++ y) {
            int x = y - 1;
            if (x < 0 || x > amount[1]) {
                continue;
            }
            int c = y;
            int d = y;
            for (int z = 0; z <= amount[0]; ++ z) {
                int p = k - x - y - z;
                if (p < 0 || p > amount[3]) {
                    continue;
                }
                answer += combine(c + z - 1, z) * combine(d + p - 1, p);
            }
        }
    } else if (strcmp(string, "AA") == 0) {
        // A ... A
        for (int x = 0; x <= amount[1]; ++ x) {
            int y = x;
            if (y < 0 || y > amount[2]) {
                continue;
            }
            int c = x + 1;
            int d = x;
            for (int z = 0; z <= amount[0]; ++ z) {
                int p = k - x - y - z;
                if (p < 0 || p > amount[3]) {
                    continue;
                }
                answer += combine(c + z - 1, z) * combine(d + p - 1, p);
            }
        }
    } else {
        // B ... B
        for (int x = 0; x <= amount[1]; ++ x) {
            int y = x;
            if (y < 0 || y > amount[2]) {
                continue;
            }
            int c = x;
            int d = x + 1;
            for (int z = 0; z <= amount[0]; ++ z) {
                int p = k - x - y - z;
                if (p < 0 || p > amount[3]) {
                    continue;
                }
                answer += combine(c + z - 1, z) * combine(d + p - 1, p);
            }
        }
    }
    if (answer == 0) {
        puts("NO");
    } else {
        puts("YES");
        std::cout << answer << '\n';
    }
    return 0;
}
