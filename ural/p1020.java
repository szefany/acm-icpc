import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    static final int N = 100;
    static final double PI = Math.acos(-1);
    public class Point {
        double x, y;
    }
    public static Point[] points = new Point[N];

    void start() throws IOException {
        int n = reader.nextInt();
        double r = reader.nextDouble();
        for (int i = 0; i < n; ++ i) {
            points[i] = new Point();
            points[i].x = reader.nextDouble();
            points[i].y = reader.nextDouble();
        }
        double answer = 2 * PI * r;
        for (int i = 0; i < n; ++ i) {
            int j = (i + 1) % n;
            answer += Math.sqrt(Math.pow(points[i].x - points[j].x, 2) + Math.pow(points[i].y - points[j].y, 2));
        }
        writer.printf("%.2f\n", answer);
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
