class Solution {
public:
    int minCut(string s) {
        int n = s.length();
        if (n == 0) {
            return 0;
        }
        
        getRadius(s);
        dp.resize(n);
        for (int i = 0; i < n; ++ i) {
            dp[i] = INF;
            if (isPalindrome(0, i)) {
                dp[i] = 0;
            } else {
                for (int j = 1; j <= i; ++ j) {
                    if (isPalindrome(j, i)) {
                        dp[i] = min(dp[i], dp[j - 1] + 1);
                    }
                }
            }
        }
        return dp[n - 1];
    }
private:
    static const int INF = 1 << 30;
    vector<int> radius, dp;
    #define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)
    
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

