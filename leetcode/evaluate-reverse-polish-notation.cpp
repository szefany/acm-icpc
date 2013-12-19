class Solution {
public:
    static const int ERROR = INT_MIN;
    
    bool is_operator(string token) {
        return token.length() == 1 && \
            (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/');
    }
    
    int eval(int a, int b, char token) {
        int result = ERROR;
        if (token == '+') {
            result = a + b;
        } else if (token == '-') {
            result = a - b;
        } else if (token == '*') {
            result = a * b;
        } else if (token == '/') {
            result = a / b;
        }
        assert(result != ERROR);
        return result;
    }
    
    int toNumber(string token) {
        int result;
        stringstream buffer;
        buffer << token;
        buffer >> result;
        return result;
    }
    
    int evalRPN(vector<string> &tokens) {
        stack<int> s;
        for (int i = 0; i < tokens.size(); ++ i) {
            string key = tokens[i];
            if (is_operator(key)) {
                int b = s.top();
                s.pop();
                int a = s.top();
                s.pop();
                s.push(eval(a, b, key[0]));
            } else {
                s.push(toNumber(key));
            }
        }
        return s.top();
    }
};
