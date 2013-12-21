class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        unordered_set<int> numbers;
        for (int i = 0; i < num.size(); ++ i) {
            int x = num[i];
            numbers.insert(x);
        }
        int answer = 0;
        for (int i = 0; i < num.size(); ++ i) {
            int x = num[i];
            if (numbers.find(x) != numbers.end()) {
                numbers.erase(x);
                int count = 1;
                for (int y = x + 1; numbers.find(y) != numbers.end(); ++ y) {
                    count ++;
                    numbers.erase(y);
                }
                for (int y = x - 1; numbers.find(y) != numbers.end(); -- y) {
                    count ++;
                    numbers.erase(y);
                }
                answer = max(answer, count);
            }
        }
        return answer;
    }
};
