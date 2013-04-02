// Codeforces Round #106 (Div. 2)
// Problem E, Martian Strings
#include <cstdio>
#include <cstring>
#include <algorithm>

using std::max;

const int N = 100000;

char string[N], buffer[N];
int next[N], left[N], right[N];
int n, length;

void jump (int key, char* string, int& p) {
    while (p != -1 && string[p + 1] != key) {
        p = next[p];
    }
    p += string[p + 1] == key;
}

void prepare (char* string, int length) {
    next[0] = -1;
    for (int i = 1, j = -1; i < length; ++ i) {
        jump (string[i], string, j);
        next[i] = j;
    }
}

bool valid (char* buffer) {
    int buffer_length = strlen (buffer);
    if (buffer_length == 1) {
        return false;
    }
    prepare (buffer, buffer_length);
    for (int i = 0, j = -1; i < length; ++ i) {
        jump (string[i], buffer, j);
        left[i] = j;
    }
    std::reverse (buffer, buffer + buffer_length);
    prepare (buffer, buffer_length);
    for (int i = length - 1, j = -1; i >= 0; -- i) {
        jump (string[i], buffer, j);
        right[i] = j;
    }
    for (int i = 0; i < length; ++ i) {
        left[i] = i == 0 ? left[i] : max (left[i], left[i - 1]);
    }
    for (int i = length - 1; i >= 0; -- i) {
        right[i] = i + 1 == length ? right[i] : max (right[i], right[i + 1]);
    }
    for (int i = 1; i < length; ++ i) {
        if (left[i - 1] + right[i] + 2 >= buffer_length) {
            return true;
        } 
    }
    return false;
}

int main () {
    scanf ("%s%d", string, &n);
    length = strlen (string);
    int answer = 0;
    for (int i = 0; i < n; ++ i) {
        scanf ("%s", buffer);
        answer += valid (buffer);
    }
    printf ("%d\n", answer);
    return 0;
}
