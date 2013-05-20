import java.util.*;
import java.math.*;
import java.io.*;

public class Main {

    void start() throws IOException {
        int n = reader.nextInt(), answer;
        if (n >= 1) {
            answer = n * (n + 1) / 2;
        } else if (n == 0) {
            answer = 1;
        } else if (n == -1) {
            answer = 0;
        } else {
            answer = (-2 + n) * (-n - 2 + 1) / 2;
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
