// Codeforces Round #157, division 2
// Problem B, Little Elephant and Magic Square
#include <iostream>
#include <cstdio>
using namespace std;

int a[5][5];

int main () {
    for (int i = 1; i <= 3; ++ i) {
        for (int j = 1; j <= 3; ++ j) {
            scanf ("%d", &a[i][j]);
        }
    }
    for (int x = 1; x <= 100000; ++ x) {
        a[1][1] = x;
        int sum = a[1][1] + a[1][2] + a[1][3];
        a[2][2] = sum - a[2][1] - a[2][3];
        a[3][3] = sum - a[3][1] - a[3][2];
        if (a[1][1] + a[2][2] + a[3][3] == sum && a[1][3] + a[2][2] + a[3][1] == sum) {
            break;
        }
    }
    for (int i = 1; i <= 3; ++ i) {
        for (int j = 1; j <= 3; ++ j) {
            printf ("%d%c", a[i][j], j == 3 ? '\n' : ' ');
        }
    }
    return 0;
}
