import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    static int[][] count = new int[10][100];

    void start() throws IOException {
        int n = reader.nextInt();
        int m = n >> 1;

        count[0][0] = 1;
        for (int i = 1; i <= m; ++ i) {
            for (int j = 0; j <= i * 9; ++ j) {
                for (int k = 0; k <= 9; ++ k) {
                    if (j >= k) {
                        count[i][j] += count[i - 1][j - k];
                    }
                }
            }
        }
        int answer = 0;
        for (int i = 0; i <= m * 9; ++ i) {
            answer += count[m][i] * count[m][i];
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
