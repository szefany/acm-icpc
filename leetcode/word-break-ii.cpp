class Solution {
#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

public:
    void solve(string& s, int n, unordered_set<string>& dict, vector<string>& answer, bool *available) {
        if (n < 0) {
            return;
        }
        string buffer = "";
        for (int i = n; i >= 0; -- i) {
            buffer = s[i] + buffer;
            if (dict.find(buffer) != dict.end() && (i == 0 || available[i - 1])) {
                vector<string> temp;
                solve(s, i - 1, dict, temp, available);
                if (i == 0) {
                    answer.push_back(buffer);
                } else {
                    foreach(iter, temp) {
                        answer.push_back((*iter) + " " + buffer);
                    }
                }
            }
        }
    }
    
    vector<string> wordBreak(string s, unordered_set<string> &dict) {
        int length = s.length();
        bool *available = new bool [length + 1];
        for (int i = 0; i < length; ++ i) {
            available[i] = false;
        }
        for (int i = 0; i < length; ++ i) {
            if (i == 0 || available[i - 1]) {
                string buffer = "";
                for (int j = i; j < length; ++ j) {
                    buffer += s[j];
                    if (dict.find(buffer) != dict.end()) {
                        available[j] = true;
                    }
                }
            }   
        }
        vector<string> answer;
        if (!available[length - 1]) {
            return answer;
        }
        solve(s, length - 1, dict, answer, available);
        return answer;
    }
};
