import java.util.*;
import java.math.*;
import java.io.*;

public class Main {

    void start() throws IOException {
        int[] answer = new int [50];
        int n = reader.nextInt(), size = 0;
        if (n == 1) {
            writer.println(1);
            return;
        }
        if (n == 0) {
            writer.println(10);
            return;
        }
        for (int i = 9; i >= 2; -- i) {
            while (n % i == 0) {
                size ++;
                answer[size] = i;
                n /= i;
            }
        }
        if (n > 1) {
            writer.print(-1);
        } else {
            for (int i = size; i >= 1; -- i) {
                writer.print(answer[i]);
            }
        }
        writer.println();
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

    double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }
}
