import java.util.*;
import java.io.*;
import java.math.*;

class Edge {
    int from, to, flow, capa, next;
    BigInteger cost;
    Edge() {}
    Edge(int u, int v, int _capa, BigInteger _cost, int n) {
        from = u;
        to = v;
        flow = 0;
        capa = _capa;
        cost = _cost;
        next = n;
    }
}

public class Main {
    static final int N = 200 + 10;
    static final int M = N * N * 3;
    static final int INF = 1 << 29;

    static Edge[] g = new Edge[M];
    static int[] first = new int[N];
    static int vs, vt, edge_count;

    static void add_edge(int u, int v, int capa, BigInteger cost) {
        edge_count ++;
        g[edge_count] = new Edge(u, v, capa, cost, first[u]); first[u] = edge_count;
        g[M - edge_count] = new Edge(v, u, 0, cost.multiply(BigInteger.valueOf(-1)), first[v]); first[v] = M - edge_count;
    }

    static final int Q = N + 10;
    static int[] queue = new int[N + N];
    static int[] link = new int[N];
    static BigInteger[] dist = new BigInteger[N];
    static boolean[] visit = new boolean[N];

    static void MincostFlow() {
        int flow = 0;
        while (true) {
            Arrays.fill(dist, BigInteger.ONE.shiftLeft(200).multiply(BigInteger.valueOf(-1)));
            Arrays.fill(link, 0);
            Arrays.fill(visit, false);
            queue[1] = vs;
            visit[vs] = true;
            dist[vs] = BigInteger.ZERO;
            for (int head = 0, tail = 1; head != tail; ) {
                head = head % Q + 1;
                int u = queue[head];
                visit[u] = false;
                for (int iter = first[u]; iter != 0; iter = g[iter].next) {
                    int v = g[iter].to;
                    if (g[iter].flow < g[iter].capa && dist[u].add(g[iter].cost).compareTo(dist[v]) > 0) {
                        dist[v] = dist[u].add(g[iter].cost);
                        link[v] = iter;
                        if (!visit[v]) {
                            visit[v] = true;
                            tail = tail % Q + 1;
                            queue[tail] = v;
                        }
                    }
                }
            }
            if (link[vt] == 0) {
                break;
            }
            int delta = INF;
            for (int u = vt, iter; u != vs; u = g[iter].from) {
                iter = link[u];
                delta = Math.min(delta, g[iter].capa - g[iter].flow);
            }
            for (int u = vt, iter; u != vs; u = g[iter].from) {
                iter = link[u];
                g[iter].flow += delta;
                g[M - iter].flow -= delta;
            }
            flow += delta;
        }
    }

    static int[] a = new int[N];
    static int[] b = new int[N];
    static int[] c = new int[N];
    static int n, m;

    public static void run() throws IOException {
        n = reader.nextInt();
        m = reader.nextInt();
        for (int i = 1; i <= n; ++ i) {
            a[i] = reader.nextInt();
            b[i] = reader.nextInt();
            c[i] = reader.nextInt();
        }
        vs = n + n + 1;
        vt = n + n + 2;
        int s = n + n + 3;
        add_edge(vs, s, m, BigInteger.ZERO);
        for (int i = 1; i <= n; ++ i) {
            add_edge(s, i, INF, BigInteger.ZERO);
            add_edge(i + n, vt, INF, BigInteger.ZERO);
            add_edge(i, i + n, 1, BigInteger.ONE.shiftLeft(n - i));
            for (int j = 1; j <= n; ++ j) {
                if (i != j && b[i] <= a[j] && c[i] <= c[j]) {
                    add_edge(i + n, j, INF, BigInteger.ZERO);
                }
            }
        }

        MincostFlow();
        boolean[] reach = new boolean[N];
        for (int i = 1; i <= n; ++ i) {
            for (int iter = first[i]; iter != 0; iter = g[iter].next) {
                if (g[iter].to == i + n) {
                    reach[i] = g[iter].flow > 0;
                    break;
                }
            }
        }
        for (int i = 1; i <= n; ++ i) {
            if (reach[i] == true) {
                writer.print("1");
            } else {
                writer.print("0");
            }
        }
        writer.println();
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
    
    Long nextLong() throws IOException {
        return Long.parseLong(next());
    }

    double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }
}
