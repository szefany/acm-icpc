import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    static int[][] count = new int[10][100];

    void start() throws IOException {
        int n = reader.nextInt();
        for (int i = 1; i <= n; ++ i) {
            writer.print(i);
            if (i < n) {
                writer.print(" ");
            } else {
                writer.println();
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
