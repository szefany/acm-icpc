// Codeforces Round #163 (Div. 2)
// Problem B, Queue at the School
#include <iostream>
#include <cstdio>
using namespace std;

int n, m;
char buffer[100];

int main () {
    scanf ("%d%d%s", &n, &m, buffer);
    while (m --) {
        for (int i = 0; i < n - 1; ++ i) {
            if (buffer[i] == 'B' && buffer[i + 1] == 'G') {
                swap (buffer[i], buffer[i + 1]);
                i ++;
            }
        }
    }
    puts (buffer);
    return 0;
}
