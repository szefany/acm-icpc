#include <cstdio>
#include <cstring>
#include <map>
#include <cassert>
#include <string>

const int N = 500;

char a[N], b[N];
int children[N][2], type[N];
int node_count;

#define L(u) children[(u)][0]
#define R(u) children[(u)][1]

/*  types:
    0 ~ (n - 1): variables
    -1: !
    -2: &
    -3: |
    -4: ^
*/

int get_type(char token) {
    int result = 0;
    if (token == '!') {
        result = -1;
    } else if (token == '&') {
        result = -2;
    } else if (token == '|') {
        result = -3;
    } else if (token == '^') {
        result = -4;
    }
    assert(result < 0);
    return result;
}

std::map<std::string, int> variables;
int counter;

int get_id(std::string name) {
    if (variables.find(name) == variables.end()) {
        variables[name] = counter ++;
    }
    return variables[name];
}

bool is_letter(char token) {
    return token >= 'a' && token <= 'z' || token >= 'A' && token <= 'Z';
}

const char opers[5] = "^|&";

void build(int &u, int l, int r, char* string) {
    if (l > r) {
        return;
    }
    if (u == 0) {
        u = ++ node_count;
        children[u][0] = children[u][1] = 0;
    }
    int pivot = -1;
    for (int count = 0; count < 3 && pivot == -1; ++ count) {
        for (int i = l, sum = 0; i <= r && pivot == -1; ++ i) {
            if (string[i] == '(') {
                sum ++;
            } else if (string[i] == ')') {
                sum --;
            }
            if (sum == 0 && string[i] == opers[count]) {
                pivot = i;
            }
        }
    }
    if (pivot != -1) {
        type[u] = get_type(string[pivot]);
        build(L(u), l, pivot - 1, string);
        build(R(u), pivot + 1, r, string);
    } else if (string[l] == '!') {
        type[u] = get_type(string[l]);
        build(L(u), l + 1, r, string);
    } else if (string[l] == '(') {
        build(u, l + 1, r - 1, string);
    } else {
        char buffer[15];
        int length = 0;
        for (int i = l; i <= r; ++ i) {
            buffer[length ++] = string[i];
        }
        buffer[length ++] = '\0';
        type[u] = get_id(buffer);
    }
}

int solve(int u, int mask) {
    if (type[u] >= 0) {
        return (1 << type[u] & mask) > 0;
    }
    if (type[u] == -1) {
        return solve(L(u), mask) ^ 1;
    }
    int a = solve(L(u), mask);
    int b = solve(R(u), mask);
    int result = -1;
    if (type[u] == -2) {
        result = a & b;
    } else if (type[u] == -3) {
        result = a | b;
    } else if (type[u] == -4) {
        result = a ^ b;
    }
    assert(result >= 0);
    return result;
}

char buffer[N];

void trans(char* string) {
    int length = strlen(string);
    int len = 0;
    for (int i = 0; i < length; ++ i) {
        if (string[i] != ' ') {
            buffer[len ++] = string[i];
        }
    }
    buffer[len ++] = '\0';
    strcpy(string, buffer);
}

int main() {
    while (gets(a) && a[0] != '\0') {
        gets(b);
        trans(a);
        trans(b);

        int root[2] = {0};
        node_count = counter = 0;
        variables.clear();
        build(root[0], 0, strlen(a) - 1, a);
        build(root[1], 0, strlen(b) - 1, b);

        bool flag = true;
        for (int mask = 0; mask < 1 << counter && flag; ++ mask) {
            int a = solve(root[0], mask);
            int b = solve(root[1], mask);
            flag &= a == b;
        }
        puts(flag ? "TRUE" : "FALSE");
    }
    return 0;
}
