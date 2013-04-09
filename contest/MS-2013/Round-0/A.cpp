#include <cstdio>
#include <string>
#include <map>
#include <iostream>
#include <vector>
using std::string;

std::map<string, string> dict;
std::vector<string> sentence;
int n, m;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

void split(string buffer, std::vector<string> &a) {
    buffer += " ";
    while (buffer.size()) {
        int pos = buffer.find_first_of(" ");
        a.push_back(buffer.substr(0, pos));
        buffer.erase(0, pos + 1);
    }
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        scanf("%d%d", &n, &m);
        dict.clear();
        while (m --) {
            string a, b;
            std::cin >> a >> b;
            dict[a] = b;
        }

        sentence.clear();
        string buffer;
        getline(std::cin, buffer);
        getline(std::cin, buffer);
        split(buffer, sentence);

        for (int i = 0; i < n - 1; ++ i) {
            foreach(iter, sentence) {
                if (dict.find(*iter) != dict.end()) {
                    (*iter) = dict[*iter];
                }
            }
        }
        printf("Case #%d: ", t);
        foreach(iter, sentence) {
            std::cout << *iter << (iter + 1 == sentence.end() ? '\n' : ' ');
        }
    }
    return 0;
}
