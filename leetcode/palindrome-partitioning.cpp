class Solution {
public:
    vector<vector<string> > partition(string s) {
        vector<vector<string> > answer;
        int n = s.length();
        if (n == 0) {
            return answer;
        }
        
        getRadius(s);
        available.resize(n);
        for (int i = 0; i < n; ++ i) {
            available[i] = false;
        }
        for (int i = 0; i < n; ++ i) {
            if (isPalindrome(0, i)) {
                available[i] = true;
            } else {
                for (int j = 1; j <= i; ++ j) {
                    if (available[j - 1] && isPalindrome(j, i)) {
                        available[i] = true;
                        break;
                    }
                }
            }
        }
        solve(s, s.length() - 1, answer);
        return answer;
    }
private:
    vector<int> radius;
    vector<bool> available;
    #define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)
    
    void solve(string& s, int n, vector<vector<string> >& answer) {
        if (n < 0) {
            return;
        }
        string buffer = "";
        for (int i = n; i >= 0; -- i) {
            buffer = s[i] + buffer;
            if (!isPalindrome(i, n) || (i > 0 && !available[i - 1])) {
                continue;
            }
            if (i == 0) {
                vector<string> temp;
                temp.push_back(buffer);
                answer.push_back(temp);
            } else {
                int current_size = answer.size();
                solve(s, i - 1, answer);
                for (int iter = current_size; iter < answer.size(); ++ iter) {
                    answer[iter].push_back(buffer);
                }
            }
        }
    }
    
    bool isPalindrome(int left, int right) {
        int length = right - left + 1;
        int middle = left + right >> 1;
        int pivot = (length & 1) ? middle * 2 + 2 : middle * 2 + 3;
        return radius[pivot] >= length;
    }
    void getRadius(string& s) {
        string buffer = "$#";
        for (int i = 0; i < s.length(); ++ i) {
            buffer += s[i];
            buffer += "#";
        }
        int length = buffer.length();
        radius.resize(length);
        for (int i = 1, max_value = 0, id = -1; i < length; ++ i) {
            radius[i] = max_value <= i ? 1 : min(radius[2 * id - i], max_value - i);
            while (buffer[i - radius[i]] == buffer[i + radius[i]]) {
                radius[i] ++;
            }
            if (i + radius[i] > max_value) {
                max_value = i + radius[i];
                id = i;
            }
        }
    }
};
