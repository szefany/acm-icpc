// Codeforces Round #163 (Div. 2)
// Problem A, Stones on the table
#include <iostream>
#include <cstdio>
using namespace std;

int n;
char buffer[100];

int main () {
    scanf ("%d%s", &n, buffer);
    int ans = 0;
    for (int i = 1; i < n; ++ i) {
        if (buffer[i] == buffer[i - 1]) {
            ans ++;
        }
    }
    cout << ans << endl;
    return 0;
}
