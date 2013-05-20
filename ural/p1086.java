import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    static final int N = 20000;
    static final int M = 200000;
    static boolean[] visit = new boolean[M];
    static int[] primes = new int[N];

    void start() throws IOException {
        int count = 0;
        for (int i = 2; i < M && count < N; ) {
            primes[++ count] = i;
            for (int j = i; j < M; j += i) {
                visit[j] = true;
            }
            for (i ++; i < M && visit[i] == true; i ++);
        }
        int test = reader.nextInt();
        while (test -- > 0) {
            int n = reader.nextInt();
            writer.println(primes[n]);
        }
    }

    public void run() {
        try {
            start();
        } catch (IOException ex) {
        }
        writer.flush();
        writer.close();
    }
    
    InputReader reader;
    PrintWriter writer;
    
    Main() {
        reader = new InputReader();
        writer = new PrintWriter(System.out);
    }

    public static void main(String args[]) {
        new Main().run();
    }
}

class InputReader {
    BufferedReader reader;
    StringTokenizer tokenizer;

    InputReader() {
        reader = new BufferedReader(new InputStreamReader(System.in));
        tokenizer = new StringTokenizer("");
    }
    
    String next() throws IOException {
        while (!tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }

    Integer nextInt() throws IOException {
        return Integer.parseInt(next());
    }
    
    Long nextLong() throws IOException {
        return Long.parseLong(next());
    }

    Double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }
}
