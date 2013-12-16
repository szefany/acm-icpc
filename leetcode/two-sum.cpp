class Solution {
public:
    typedef pair<int, int> Pair;
    vector<int> twoSum(vector<int> &numbers, int target) {
        vector<int> result;
        int n = numbers.size();
        vector<Pair> final(n);
        for (int i = 0; i < n; ++ i) {
            final[i] = make_pair(numbers[i], i + 1);
        }
        sort(final.begin(), final.end());
        
        for (int i = 0, pivot = n - 1; i < n; ++ i) {
            int current = final[i].first;
            while (pivot > 0 && current + final[pivot].first > target) {
                pivot --;
            }
            if (current + final[pivot].first == target) {
                result.push_back(final[i].second);
                result.push_back(final[pivot].second);
                sort(result.begin(), result.end());
                return result;
            }
        }
        result.push_back(-1); // NO FOUND
        return result;
    }
};
