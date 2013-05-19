import java.util.Scanner;
import java.math.BigInteger;

public class Main {
    static int[] count = new int[10];

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int n;
        while (true) {
            n = in.nextInt();
            if (n == 0) {
                break;
            }
            int sum = 0;
            for (int i = 1; i <= n; ++ i) {
                count[i] = in.nextInt();
                sum += count[i];
            }
            BigInteger answer = BigInteger.ONE;
            for (int i = 1; i <= sum; ++ i) {
                answer = answer.multiply(BigInteger.valueOf(i));
            }
            for (int i = 1; i <= n; ++ i) {
                for (int j = 1; j <= count[i]; ++ j) {
                    int temp = count[i] - j + 1;
                    for (int k = i + 1; k <= n; ++ k) {
                        if (count[k] >= j) {
                            temp ++;
                        }
                    }
                    answer = answer.divide(BigInteger.valueOf(temp));
                }
            }
            System.out.println(answer);
        }
    }
}
