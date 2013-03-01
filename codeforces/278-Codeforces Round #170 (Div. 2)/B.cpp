// Codeforces Round #170 (Div. 2)
// Problem B, New Problem
#include <cstdio>
#include <cstring>

bool words[26 * 26], letter[26];

int main () {
    int n;
    scanf ("%d", &n);
    for (int i = 0; i < n; ++ i) {
        char buffer[30];
        scanf ("%s", buffer);
        int length = strlen (buffer);
        for (int i = 0; i < length; ++ i) {
            int first = buffer[i] - 'a';
            letter[first] = true;
            if (i + 1 < length) {
                int second = buffer[i + 1] - 'a';
                words[first * 26 + second] = true;
            }
        }
    }
    for (int i = 0; i < 26; ++ i) {
        if (!letter[i]) {
            putchar (i + 'a');
            return 0;
        }
    }
    for (int i = 0; i < 26 * 26; ++ i) {
        if (!words[i]) {
            putchar (i / 26 + 'a');
            putchar (i % 26 + 'a');
            puts ("");
            break;
        }
    }
    return 0;
}
