import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    static int D[][] = {{-1, 2}, {-1, -2}, {-2, -1}, {-2, 1}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    void start() throws IOException {
        int test = reader.nextInt();
        while (test -- > 0) {
            long n = reader.nextLong();
            n = (n - 1) * 2;
            long m = (long)Math.floor(Math.sqrt(n * 1.0));
            if (m * (m + 1) == n) {
                writer.print(1 + " ");
            } else {
                writer.print(0 + " ");
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
