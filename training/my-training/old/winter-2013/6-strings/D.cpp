// Codeforces Beta Round #86 (Div. 1 Only)
// Problem B, Petr#
#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>

const int N = 2000 + 5;

char mode[N], string[2][N];
int next[2][N], length[2];

void build (int index) {
    next[index][0] = -1;
    for (int i = 1, j = -1; i < length[index]; ++ i) {
        while (j != -1 && string[index][i] != string[index][j + 1]) {
            j = next[index][j];
        }
        if (string[index][i] == string[index][j + 1]) {
            j ++;
        }
        next[index][i] = j;
    }
}

void jump (int index, int key, int &iter) {
    while (iter != -1 && string[index][iter + 1] != key) {
        iter = next[index][iter];
    }
    iter += string[index][iter + 1] == key;
}

const int MAGIC = 9999991;
typedef std::pair <unsigned long long, int> Hash;

void add (Hash& hash, int value) {
    hash.first = hash.first * 131 + value;
    hash.second = ((long long)hash.second * 131 + value) % MAGIC;
}

struct HashMap {
    static const int SIZE = 4999997;
    int first[SIZE], next_element[SIZE], size;
    Hash values[SIZE];
    void insert (Hash value) {
        int key = (value.first * 1001 + value.second) % SIZE;
        for (int iter = first[key]; iter != 0; iter = next_element[iter]) {
            if (values[iter] == value) {
                return;
            }
        }
        size ++;
        values[size] = value;
        next_element[size] = first[key];
        first[key] = size;
    }
};

int main () {
    scanf ("%s", mode);
    for (int i = 0; i < 2; ++ i) {
        scanf ("%s", string[i]);
        length[i] = strlen (string[i]);
        build (i);
    }
    HashMap answer;
    int length_mode = strlen (mode);
    for (int i = 0, u = -1; i < length_mode; ++ i) {
        jump (0, mode[i], u);
        if (u + 1 == length[0]) {
            Hash hash = std::make_pair (0, 0);
            int start = i - std::min (length[0], length[1]) + 1;
            for (int j = start, v = -1; j < length_mode; ++ j) {
                add (hash, mode[j]);
                jump (1, mode[j], v);
                if (v + 1 == length[1]) {
                    answer.insert (hash);
                }
            }
        }
    }
    printf ("%d\n", answer.size);
    return 0;
}
