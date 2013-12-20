class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
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
        return available[length - 1];
    }
};
