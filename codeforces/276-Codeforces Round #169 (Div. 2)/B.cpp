// Codeforces Round #169 (Div. 2)
// Problem B, Little Girl and Game
#include <cstdio>
#include <cstring>

int counter[26];
char string[1000];

int main () {
    scanf ("%s", string);
    int length = strlen (string);
    for (int i = 0; i < length; ++ i) {
        counter[string[i] - 'a'] ++;
    }
    int number = 0;
    for (int i = 0; i < 26; ++ i) {
        number += counter[i] % 2;
    }
    puts (number == 0 || number % 2 == 1 ? "First" : "Second");
    return 0;
}
