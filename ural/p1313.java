import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    static int[][] weight = new int[200][200];

    void start() throws IOException {
        int n = reader.nextInt();
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= n; ++ j) {
                weight[i][j] = reader.nextInt();
            }
        }
        for (int i = 1; i < n; ++ i) {
            int x = i, y = 1;
            while (x >= 1) {
                writer.print(weight[x][y] + " ");
                x --;
                y ++;
            }
        }
        for (int i = 1; i <= n; ++ i) {
            int x = n, y = i;
            while (y <= n) {
                writer.print(weight[x][y] + " ");
                x --;
                y ++;
            }
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
