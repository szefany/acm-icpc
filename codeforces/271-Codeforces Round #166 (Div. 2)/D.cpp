#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

char str[1500 + 5];
bool bad[26];
int n;

const int HASH = 9999991;
typedef pair <unsigned long long, int> Hash;
map <Hash, int> counter;

int main () {
    char buffer[1500 + 5];
    scanf ("%s", str);
    scanf ("%s", buffer);
    for (int i = 0; i < 26; ++ i) {
        if (buffer[i] == '0') {
            bad[i] = true;
        }
    }
    int length = strlen (str), k;
    scanf ("%d", &k);
    for (int i = 0; i < length; ++ i) {
        int sum = 0;
        Hash hash = make_pair (0, 0);
        for (int j = i; j < length; ++ j) {
            hash.first = hash.first * 131 + str[j];
            hash.second = ((long long)hash.second * 131 + str[j]) % HASH;
            sum += bad[str[j] - 'a'];
            if (sum <= k) {
                counter[hash] ++;
            }
            else {
                break;
            }
        }
    }
    int answer = 0;
    for (map <Hash, int>::iterator iter = counter.begin(); iter != counter.end(); iter ++, answer ++);
    cout << answer << endl;
    return 0;
}
