#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

char buffer[1000005];
int ans[1000005];

int main () {
    scanf ("%s", buffer);
    int len = strlen (buffer), counter = 0;
    for (int i = 0; i < len; ++ i) {
        if (buffer[i] == 'r') {
            ans[++ counter] = i + 1;
        }
    }
    for (int i = len - 1; i >= 0; -- i) {
        if (buffer[i] == 'l') {
            ans[++ counter] = i + 1;
        }
    }
    for (int i = 1; i <= counter; ++ i) {
        printf ("%d\n", ans[i]);
    }
    return 0;
}

