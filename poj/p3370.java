import java.util.*;
import java.io.*;

public class Main {
    static final int N = 100000 + 1;
    static int[] elements = new int[N];
    static int[] position = new int[N];

    InputReader reader;
    PrintWriter writer;

    public void run() {
        try {
            int n, c;
            while (true) {
                c = reader.nextInt();
                n = reader.nextInt();
                if (n == 0 && c == 0) {
                    return;
                }
                for (int i = 0; i <= c; ++ i) {
                    position[i] = -1;
                }
                position[0] = 0;
                for (int i = 1; i <= n; ++ i) {
                    elements[i] = reader.nextInt();
                }
                int sum = 0, left = 0, right = 0;
                for (int i = 1; i <= n; ++ i) {
                    sum = (sum + elements[i]) % c;
                    if (position[sum] != -1) {
                        left = position[sum];
                        right = i;
                        break;
                    }
                    position[sum] = i;
                }
                for (int i = left + 1; i < right; ++ i) {
                    writer.print(i + " ");
                    writer.flush(); // NOTE THIS
                }
                writer.println(right);
                writer.flush();
            }
        } catch (IOException ex) {
        }
        writer.close();
    }

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
}
