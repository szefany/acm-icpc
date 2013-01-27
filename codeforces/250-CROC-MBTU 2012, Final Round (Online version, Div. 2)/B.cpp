// CROC-MBTU 2012, Final Round (Online version, Div. 2)
// Problem B, Restoring IPv6
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        char buffer[100];
        scanf ("%s", buffer);
        int len = strlen (buffer);
        int colon = 0;
        for (int j = 0; j < len; ++ j) {
            colon += (j > 0 && buffer[j] == ':');
            if (j + 1 < len && buffer[j] == ':' && buffer[j + 1] == ':') {
                j ++;
            }
        }
        if (strcmp (buffer, "::") == 0) {
            puts ("0000:0000:0000:0000:0000:0000:0000:0000");
            continue;
        }
        colon += buffer[len - 1] != ':';
        int block = 8 - colon;
        bool first = true;
        for (int i = 0; i < len; ) {
            if (i < len && buffer[i] == ':' && buffer[i + 1] == ':') {
                if (!first) {
                    putchar (':');
                }
                for (int j = 1; j <= block; ++ j) {
                    printf ("%s", "0000");
                    if (j < block) {
                        putchar (':');
                    }
                }
                i += 2;
                first = false;
                continue;
            }
            if (buffer[i] == ':') {
                i ++;
            }
            int j = i;
            while (j < len && buffer[j] != ':') {
                j ++;
            }
            if (!first) {
                putchar (':');
            }
            first = false;
            for (int k = 4 - (j - i); k > 0; -- k) {
                putchar ('0');
            }
            for (int k = i; k < j; ++ k) {
                putchar (buffer[k]);
            }
            i = j;
        }
        puts ("");
    }
    return 0;
}
