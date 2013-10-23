import java.util.*;
import java.math.*;

class Data {
    public BigInteger a, b;
    Data() {}
    Data(BigInteger _a, BigInteger _b) {
        a = _a;
        b = _b;
    }
    Data(int _a, int _b) {
        a = BigInteger.valueOf(_a);
        b = BigInteger.valueOf(_b);
    }
    void flush() {
        if (a.compareTo(BigInteger.ZERO) == 0) {
            b = BigInteger.ONE;
        } else {
            BigInteger g = a.gcd(b);
            a = a.divide(g);
            b = b.divide(g);    
        }
    }
    
    Data add(Data other) {
        BigInteger c = other.a;
        BigInteger d = other.b;
        BigInteger x = a.multiply(d).add(b.multiply(c));
        BigInteger y = b.multiply(d);
        Data result = new Data(x, y);
        result.flush();        
        return result;
    }
    
    Data multiply(int x) {
        Data result = new Data(a.multiply(BigInteger.valueOf(x)), b);
        result.flush();
        return result;
    }
    
    Data multiply(Data other) {
        Data result = new Data(a.multiply(other.a), b.multiply(other.b));
        result.flush();
        return result;
    }
}

public class Main {
    public static final int N = 2000 + 10;
    static BigInteger[] a = new BigInteger[N];
    static BigInteger[] b = new BigInteger[N];

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        int k = in.nextInt();
        
        a[0] = BigInteger.valueOf(m);
        b[0] = BigInteger.valueOf(1);
        for (int i = 1; i <= k; ++ i) {
            a[i] = a[i - 1].multiply(BigInteger.valueOf(n - 2)).add(b[i - 1].multiply(BigInteger.valueOf(n)));
            b[i] = b[i - 1].multiply(BigInteger.valueOf(n));
        }
        if (a[k].compareTo(BigInteger.ZERO) == 0) {
            b[k] = BigInteger.ONE;
        } else {
            BigInteger g = a[k].gcd(b[k]);
            a[k] = a[k].divide(g);
            b[k] = b[k].divide(g);
        }
        System.out.println(a[k] + "/" + b[k]);
    }
}
