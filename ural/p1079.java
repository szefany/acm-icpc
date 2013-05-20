import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    static final int N = 100000;
    static int[] weight = new int[N];

    void start() throws IOException {
        weight[0] = 0;
        weight[1] = 1;
        for (int i = 1; i * 2 < N; ++ i) {
            weight[i * 2] = weight[i];
            if (i * 2 + 1 < N) {
                weight[i * 2 + 1] = weight[i] + weight[i + 1];
            }
        }
        while (true) {
            int n = reader.nextInt();
            if (n == 0) {
                break;
            }
            int answer = -1;
            for (int i = 0; i <= n; ++ i) {
                answer = Math.max(answer, weight[i]);
            }
            writer.println(answer);
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
