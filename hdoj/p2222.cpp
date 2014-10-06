#include <cstdio>
#include <cstring>

struct AcAutomation {
    static const int N = 1000000 + 10;
    static const int ROOT = 1;

    int children[N][26], fail[N];
    int terminal[N], counted[N];
    int size;

    void Clear(int node) {
        memset(children[node], 0, sizeof(children[node]));
        fail[node] = 0;
        terminal[node] = counted[node] = 0;
    }

    void Init() {
        size = ROOT;
        Clear(ROOT);
    }

    void AddString(char* string) {
        int length = strlen(string);
        int node = ROOT;
        for (int i = 0; i < length; ++ i) {
            char token = string[i] - 'a';
            if (children[node][token] == 0) {
                Clear(++ size);
                children[node][token] = size;
            }
            node = children[node][token];
        }
        terminal[node] ++;
    }

    int queue[N];
    void Build() {
        queue[1] = ROOT;
        fail[ROOT] = 0;
        for (int head = 1, tail = 1; head <= tail; ++ head) {
            int u = queue[head];
            for (int i = 0; i < 26; ++ i) {
                if (children[u][i] == 0) {
                    children[u][i] = fail[u] == 0 ? ROOT : children[fail[u]][i];
                } else {
                    int v = children[u][i];
                    queue[++ tail] = v;
                    int f = children[fail[u]][i];
                    fail[v] = f == 0 ? ROOT : f;
                }
            }
        }
    }


    int CountExistStrings(char* base) {
        int length = strlen(base);
        int node = ROOT;
        for (int i = 0; i < length; ++ i) {
            int token = base[i] - 'a';
            node = children[node][token];
            if (terminal[node] && !counted[node]) {
                counted[node] = true;
            }
        }
        int result = 0;
        for (int i = size; i >= 1; -- i) {
            int node = queue[i];
            if (terminal[node]) {
                if (counted[node]) {
                    result += terminal[node];
                }
            }
            // If we traverse through a node, then we traverse through its fail node.
            counted[fail[node]] |= counted[node];
        }
        return result;
    }

    void Debug() {
        for (int i = 0; i <= size; ++ i) {
            printf("=== Node %d: ===\n", i);
            printf("Fail: %d\n", fail[i]);
            printf("Terminal: %d\n", terminal[i]);
            for (int j = 0; j < 26; ++ j) {
                if (children[i][j]) {
                    printf("<%c, %d>", 'a' + j, children[i][j]);
                }
            } puts("");
        }
    }
};

AcAutomation automation;

const int N = 1000000 + 10;
const int Q = 10000 + 10;

char base[N], query[Q];

int main() {
    int test;
    scanf("%d", &test);
    while (test --) {
        automation.Init();
        int q;
        scanf("%d", &q);
        for (int i = 0; i < q; ++ i) {
            scanf("%s", query);
            automation.AddString(query);
        }
        automation.Build();
        scanf("%s", base);
        printf("%d\n", automation.CountExistStrings(base));
    }
    return 0;
}
