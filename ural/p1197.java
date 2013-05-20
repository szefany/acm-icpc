import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    static int D[][] = {{-1, 2}, {-1, -2}, {-2, -1}, {-2, 1}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    void start() throws IOException {
        int test = reader.nextInt();
        while (test -- > 0) {
            String s = reader.next();
            int x = s.charAt(0) - 'a' + 1;
            int y = s.charAt(1) - '1' + 1;
            int answer = 0;
            for (int i = 0; i < 8; ++ i) {
                int dx = x + D[i][0];
                int dy = y + D[i][1];
                if (dx >= 1 && dx <= 8 && dy >= 1 && dy <= 8) {
                    answer ++;
                }
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
