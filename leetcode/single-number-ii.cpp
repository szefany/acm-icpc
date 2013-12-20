class Solution {
public:
    int singleNumber(int A[], int n) {
        int *count = new int [32];
        
        int answer = 0;
        for (int pivot = 0; pivot < 32; ++ pivot) {
            count[pivot] = 0;
            for (int i = 0; i < n; ++ i) {
                count[pivot] += A[i] >> pivot & 1;
            }
            if (count[pivot] % 3) {
                answer |= 1 << pivot;
            }
        }
        return answer;
    }
};
