// Codeforces Round 157, Division 2
// Problem A, Little Elephant and Chess
#include <iostream>
#include <cstdio>
using namespace std;

char str[10][10];

int main () {
    bool flag = true;
    for (int i = 1; i <= 8; ++ i) {
        char buffer[10];
        scanf ("%s", buffer);
        for (int j = 1; j < 8; ++ j) {
            if (buffer[j] == buffer[j - 1]) {
                flag = false;
                break;
            }
        }
    }
    puts (flag ? "YES" : "NO");
    return 0;
}
