import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    public static final int N = 2000;
    public static BigInteger[][] dp = new BigInteger[N][N];

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int k = in.nextInt();

        dp[1][0] = BigInteger.ZERO;
        dp[1][1] = BigInteger.valueOf(k - 1);
        for (int i = 2; i <= n; ++ i) {
            dp[i][0] = dp[i - 1][1];
            dp[i][1] = dp[i - 1][1].add(dp[i - 1][0]).multiply(BigInteger.valueOf(k - 1));
        }
        System.out.println(dp[n][0].add(dp[n][1]));
    }
}
