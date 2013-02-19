#include <cstdio>
#include <cstring>

bool visit[30];

int main () {
    int test_count;
    scanf ("%d", &test_count), getchar();
    while (test_count --) {
        memset (visit, 0, sizeof (visit));  
        char buffer[500];
        gets (buffer);
        int length = strlen (buffer);
        for (int i = 0; i < length; ++ i) {
            int key = buffer[i];
            if (key >= 'A' && key <= 'Z') {
                key = key - 'A';
                visit[key] = true;
            } else if (key >= 'a' && key <= 'z') {
                key = key - 'a';
                visit[key] = true;
            }
        }
        bool flag = false;
        for (int i = 0; i < 26; ++ i) {
            if (!visit[i]) {
                putchar ('a' + i);
                flag = true;
                break;
            }
        }
        if (!flag) {
            putchar ('~');
        }
        puts ("");
    }
    return 0;
}
