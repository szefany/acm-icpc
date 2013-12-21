class Solution {
public:
    typedef pair<string, int> Info;
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        if (start == end) {
            return 1;
        }
        unordered_set<string> searched;
        queue<Info> queue;
        queue.push(make_pair(start, 1));
        searched.insert(start);
        
        while (!queue.empty()) {
            string now = queue.front().first;
            int steps = queue.front().second;
            queue.pop();
            for (int i = 0; i < now.length(); ++ i) {
                char origin = now[i];
                for (char token = 'a'; token <= 'z'; ++ token) {
                    if (token != now[i]) {
                        now[i] = token;
                        if (now == end) {
                            return steps + 1;
                        }
                        if (searched.find(now) == searched.end() && dict.find(now) != dict.end()) {
                            queue.push(make_pair(now, steps + 1));
                            searched.insert(now);
                        }
                        now[i] = origin;
                    }
                }
            }
        }
        return 0;
    }
};
