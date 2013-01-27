// CROC-MBTU 2012, Final Round (Online version, Div. 2)
// Problem A, Paper Work
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int N = 105;

int elements[N];
int n;

int main () {
    scanf ("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf ("%d", &elements[i]);
    }
    vector<int> ans;
    for (int i = 1; i <= n; ) {
        int j = i, counter = 0;
        while (j <= n && counter + (elements[j] < 0) <= 2) {
            counter += elements[j] < 0;
            j ++;
        }
        ans.push_back (j - i);
        i = j;
    }
    printf ("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); ++ i) {
        printf ("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
    }
    return 0;
}
