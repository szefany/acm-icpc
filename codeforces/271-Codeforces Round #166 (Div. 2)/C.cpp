#include <iostream>
#include <cstdio>
using namespace std;

int n, k;
int answer[1000000 + 5];

int main () {
    cin >> n >> k;
    if (3 * k > n) {
        cout << -1 << endl;
        return 0;
    }
    for (int i = 1; i <= k; ++ i) {
        answer[i] = i;
    }
    for (int i = k + 1, j = 2; i <= k * 2; ++ i) {
        answer[i] = j;
        j = j + 1 > k ? 1 : j + 1;
    }
    for (int i = k * 2 + 1, j = 1; i <= 3 * k; ++ i, ++ j) {
        answer[i] = j;
    }
    for (int i = 3 * k + 1; i <= n; ++ i) {
        answer[i] = 1;
    }
    for (int i = 1; i <= n; ++ i) {
        printf ("%d%c", answer[i], i == n ? '\n' : ' ');
    }
    return 0;
}
