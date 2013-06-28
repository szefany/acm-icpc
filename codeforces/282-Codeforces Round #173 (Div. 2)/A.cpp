#include <cstdio>
#include <cstring>

int main() {
    int n, result = 0;
    scanf("%d", &n);
    while (n --) {
        char buffer[10];
        scanf("%s", buffer);
        bool plus = false;
        int length = strlen(buffer);
        for (int i = 0; i < length; ++ i) {
            plus |= buffer[i] == '+';
        }
        result += plus ? 1 : -1;
    }
    printf("%d\n", result);
    return 0;
}
