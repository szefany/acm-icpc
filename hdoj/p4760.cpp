#include <cstdio>
#include <cstring>

typedef unsigned long long Long;

const int N = 240000;
const int D = 17;

int children[N][2], node_count;
Long mask[N][D];

const int M = 1024;

unsigned address[M][16];
int amount[M], length[M][16];

unsigned get_address() {
    unsigned a, b, c, d;
    scanf("%u.%u.%u.%u", &a, &b, &c, &d);
    return a << 24 | b << 16 | c << 8 | d;     
}

void insert(unsigned addr, int length, int id) {
    int u = 0;
    for (int i = 31, j = 0; j < length; ++ j, -- i) {
        int key = (1U << i & addr) > 0;
        if (children[u][key] == 0) {
            children[u][key] = ++ node_count;
        }
        u = children[u][key];
    }
    mask[u][id >> 6] |= 1ULL << (id & 63);
}

void erase(unsigned addr, int length, int id) {
    int u = 0;
    for (int i = 31, j = 0; j < length; ++ j, -- i) {
        int key = (1U << i & addr) > 0;
        u = children[u][key];
    }
    mask[u][id >> 6] &= ~(1ULL << (id & 63));
}

void solve(unsigned addr, Long* result) {
    int u = 0;
    for (int i = 0; i < D; ++ i) {
        result[i] = 0;
    }
    for (int i = 31; i >= 0; -- i) {
        int key = (1U << i & addr) > 0;
        if (children[u][key]) {
            u = children[u][key];
        } else {
            break;
        }
        for (int j = 0; j < D; ++ j) {
            result[j] |= mask[u][j];
        }
    }
}

Long mask_a[D], mask_b[D];

int main() {
    char command[2];
    while (scanf("%s", command) != EOF) {
        if (*command == 'E') {
            int id;
            scanf("%d", &id);
            id --;
            scanf("%d", amount + id);
            for (int i = 0; i < amount[id]; ++ i) {
                address[id][i] = get_address();
                scanf("/%d", &length[id][i]);
                insert(address[id][i], length[id][i], id);
            }
        } else if (*command == 'D') {
            int id;
            scanf("%d", &id);
            id --;
            for (int i = 0; i < amount[id]; ++ i) {
                erase(address[id][i], length[id][i], id);
            }
        } else {
            unsigned a = get_address();
            unsigned b = get_address();
            solve(a, mask_a);
            solve(b, mask_b);
            bool found = false;
            for (int i = 0; i < D && !found; ++ i) {
                found |= (mask_a[i] & mask_b[i]) > 0;
            }
            puts(found ? "F" : "D");
        }
    }
    return 0;
}
