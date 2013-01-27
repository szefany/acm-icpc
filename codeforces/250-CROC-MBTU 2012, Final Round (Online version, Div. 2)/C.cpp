// CROC-MBTU 2012, Final Round (Online version, Div. 2)
// Problem C, Movie Critics
#include <iostream>
#include <cstdio>
using namespace std;

const int N = 100005;

int n, m;
int a[N], ans[N];

int main () {
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        scanf ("%d", &a[i]);
    }
    for (int i = 1; i <= n; ) {
        int j = i;
        while (j <= n && a[i] == a[j]) {
            j ++;
        }
        if (i == 1 && j <= n) {
            ans[a[i]] ++;
        }
        if (j > n && i > 1) {
            ans[a[i]] ++;
        }
        if (i > 1 && j <= n) {
            ans[a[i]] += 1 + (a[i - 1] == a[j]);
        }
        i = j;
    }
    int pivot = -1;
    for (int i = 1; i <= m; ++ i) {
        if (pivot == -1 || ans[i] > ans[pivot]) {
            pivot = i;
        }
    }
    printf ("%d\n", pivot);
    return 0;
}
