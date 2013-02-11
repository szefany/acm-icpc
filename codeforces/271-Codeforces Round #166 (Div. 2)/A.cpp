#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
using namespace std;

int n;

bool check (int x) {
    string str;
    stringstream buffer;
    buffer << x;
    buffer >> str;
    for (int i = 0; i < str.length(); ++ i) {
        for (int j = i + 1; j < str.length(); ++ j) {
            if (str[i] == str[j]) {
                return false;
            }
        }
    }
    return true;
}

int main () {
    cin >> n;
    for (int i = n + 1; ; ++ i) {
        if (check (i)) {
            cout << i << endl;
            return 0;
        }
    }
}
