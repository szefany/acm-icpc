import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    static final int N = 20;
    static int[] weight = new int[N];

    void start() throws IOException {
        int n = reader.nextInt();
        for (int i = 0; i < n; ++ i) {
            weight[i] = reader.nextInt();
        }
        int answer = 1 << 30;
        int[] sum = new int[2];
        for (int mask = 0; mask < 1 << n; ++ mask) {
            sum[0] = sum[1] = 0;
            for (int i = 0; i < n; ++ i) {
                if ((1 << i & mask) != 0) {
                    sum[0] += weight[i];
                } else {
                    sum[1] += weight[i];
                }
            }
            int temp = Math.max(sum[0] - sum[1], sum[1] - sum[0]);
            if (temp < answer) {
                answer = temp;
            }
        }
        writer.println(answer);
        writer.flush();
    }

    public void run() {
        try {
            start();
        } catch (IOException ex) {
        }
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

    double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }
}
