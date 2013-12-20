class Solution {
public:
    static const int INF = INT_MAX;
    #define L(u) ((u) << 1)
    #define R(u) ((u) << 1 | 1)

    void build(int u, int left, int right, int *min_value, int *sum_gas, int *sum_cost) {
        if (left == right) {
            min_value[u] = sum_gas[left] - sum_cost[left];
        } else {
            int middle = left + right >> 1;
            build(L(u), left, middle, min_value, sum_gas, sum_cost);
            build(R(u), middle + 1, right, min_value, sum_gas, sum_cost);
            min_value[u] = min(min_value[L(u)], min_value[R(u)]);
        }
    }
    
    int query_min(int u, int left, int right, int a, int b, int *min_value) {
        if (a > right || b < left) {
            return INF;
        }
        if (a <= left && b >= right) {
            return min_value[u];
        }
        int middle = left + right >> 1;
        return min(query_min(L(u), left, middle, a, b, min_value), query_min(R(u), middle + 1, right, a, b, min_value));
    }
    
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        int n = gas.size();
        for (int i = 0; i < n; ++ i) {
            gas.push_back(gas[i]);
            cost.push_back(cost[i]);
        }
        n <<= 1;
        
        int *sum_gas = new int [n];
        int *sum_cost = new int [n];
        for (int i = 0; i < n; ++ i) {
            sum_gas[i] = gas[i];
            sum_cost[i] = cost[i];
            if (i > 0) {
                sum_gas[i] += sum_gas[i - 1];
                sum_cost[i] += sum_cost[i - 1];
            }
        }
        int *min_value = new int [n << 2];
        build(1, 0, n - 1, min_value, sum_gas, sum_cost);
        
        for (int i = 0; i < n >> 1; ++ i) {
            int value = 0;
            if (i > 0) {
                value += sum_gas[i - 1] - sum_cost[i - 1];
            }
            if (value <= query_min(1, 0, n, i, i + n - 1, min_value)) {
                return i;
            }
        }
        return -1;
    }
};
