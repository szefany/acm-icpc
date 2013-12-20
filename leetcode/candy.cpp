class Solution {
public:
    struct Person {
        int position, rating;
        Person(int p = 0, int r = 0):
            position(p), rating(r) {
        }
        bool operator < (const Person& o) const {
            return rating > o.rating || rating == o.rating && position < o.position;
        }
    };
    int candy(vector<int> &ratings) {
        int n = ratings.size();
        if (n <= 1) {
            return n;
        }
        priority_queue<Person> heap;
        for (int i = 0; i < n; ++ i) {
            heap.push(Person(i, ratings[i]));
        }
        
        int *candies = new int [n];
        for (int i = 0; i < n; ++ i) {
            candies[i] = 0;
        }
        int answer = 0;
        for (int i = 0; i < n; ++ i) {
            Person now = heap.top();
            heap.pop();
            int pos = now.position;
            int needs = 1;
            if (pos > 0 && candies[pos - 1] && ratings[pos - 1] < ratings[pos]) {
                needs = max(needs, candies[pos - 1] + 1);
            }
            if (pos != n - 1 && candies[pos + 1] && ratings[pos + 1] < ratings[pos]) {
                needs = max(needs, candies[pos + 1] + 1);
            }
            candies[pos] = needs;
            answer += needs;
        }
        return answer;
    }
};
