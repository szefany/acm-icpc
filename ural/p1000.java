import java.util.*;
import java.io.*;

public class Main {

    public static void run() throws IOException {
        int a = reader.nextInt();
        int b = reader.nextInt();
        writer.println(a + b);
    }

    static InputReader reader;
    static PrintWriter writer;

    public static void main(String args[]) {
        reader = new InputReader();
        writer = new PrintWriter(System.out);
        try {
            run();
        } catch (IOException ex) {
        }
        writer.flush();
        writer.close();
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
