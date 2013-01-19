// Codeforces Round #157, Division 2
// Problem C, Little Elephant and Bits
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char buffer[100005];

int main () {
    scanf ("%s", buffer);
    int len = strlen (buffer);
    bool flag = false;
    for (int i = 0; i < len; ++ i) {
        if (flag) {
            putchar (buffer[i]);
            continue;
        }
        if (i < len - 1 && buffer[i] == '0') {
            flag = true;
            continue;
        }
        if (i == len - 1) {
            continue;
        }
        putchar (buffer[i]);
    }
    puts ("");
    return 0;
}
