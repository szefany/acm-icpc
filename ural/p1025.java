import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    static final int N = 100 + 10;
    static int[] weight = new int[N];

    void start() throws IOException {
        int n = reader.nextInt();
        for (int i = 0; i < n; ++ i) {
            weight[i] = reader.nextInt();
        }
        Arrays.sort(weight, 0, n);
        int answer = 0;
        for (int i = 0; i <= n >> 1; ++ i) {
            answer += weight[i] + 1 >> 1;
        }
        writer.println(answer);
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
