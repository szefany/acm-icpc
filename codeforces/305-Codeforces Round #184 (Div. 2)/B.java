import java.util.Scanner;
import java.math.BigInteger;

public class Main {
    static long[] x = new long[100];
    static long p, q;
    static int n;

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        p = in.nextLong();
        q = in.nextLong();
        n = in.nextInt();
        for (int i = 1; i <= n; ++ i) {
            x[i] = in.nextLong();
        }
        BigInteger a = BigInteger.ONE, b = BigInteger.valueOf(x[n]);
        for (int i = n - 1; i >= 1; -- i) {
            BigInteger na = b;
            BigInteger nb = b.multiply(BigInteger.valueOf(x[i])).add(a);
            a = na;
            b = nb;
        }
        BigInteger p1 = BigInteger.valueOf(p);
        BigInteger q1 = BigInteger.valueOf(q);
        if (p == 0 && b.equals(BigInteger.ZERO)) {
            System.out.println("YES");
        } else {
            if (a.compareTo(q1) < 0) {
                BigInteger temp;
                temp = a; a = q1; q1 = temp;
                temp = b; b = p1; p1 = temp;
            }
            if (a.mod(q1) == BigInteger.ZERO && b.mod(p1) == BigInteger.ZERO && a.divide(q1).equals(b.divide(p1))) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
    }
}
