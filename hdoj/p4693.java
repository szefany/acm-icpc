import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static final String[] map = {
		"ACM-ICPC",
		"BIDU",
		"consonant:BCDFGHJKLMNPQRSTVXZWY",
		"D41D8CD98F00B204E9800998ECF8427E",
		"2.718281828459...",
		"0xFACEB00C",
		"1E100.net",
		"\\Huge{String}",
		"InternationalCollegiateProgrammingContest",
		"JinKeLa",
		"KeepItSimpleStupid",
		"1000mL",
		"Micro$oftCorp",
		"",
		"Oops",
		"pneumonoultramicroscopicsilicovolcanoconiosis",
		"A",
		"P",
		"M",
		"TheQuickBrownFoxJumpsOverTheLazyDog",
		"\\bigcup",
		"vowel:AEIOU",
		"WWW",
		"X-ray",
		"YOOOOOO!",
		"ZheJiangUniversity",
		""
	};

	public static final int N = 100 + 1;
	public static BigInteger[][] count = new BigInteger[26][];

    public static void run() throws IOException {
        for (int i = 0; i < 26; ++ i) {
			count[i] = new BigInteger[N];
			for (int j = 0; j < N; ++ j) {
				count[i][j] = BigInteger.ZERO;
			}
			count[i][0] = BigInteger.ONE;
		}
		for (int j = 1; j < N; ++ j) {
			for (int i = 0; i < 26; ++ i) {
				for (int k = 0; k < map[i].length(); ++ k) {
					char key = map[i].charAt(k);
					if (key >= 'A' && key <= 'Z') {
						count[i][j] = count[i][j].add(count[key - 'A'][j - 1]);
					} else {
						count[i][j] = count[i][j].add(BigInteger.ONE);
					}
				}
			}
		}
		String s;
		while ((s = reader.nextLine()) != null) {
			int n = reader.nextInt();
			int m = reader.nextInt();
			BigInteger k = new BigInteger(reader.next());

			BigInteger length = BigInteger.ZERO;
			for (int i = 0; i < s.length(); ++ i) {
				char key = s.charAt(i);
				if (key >= 'A' && key <= 'Z') {
					length = length.add(count[key - 'A'][n]);
				} else {
					length = length.add(BigInteger.ONE);
				}
			}
			for (int counter = 0; counter < m && k.compareTo(length) < 0; counter ++, k = k.add(BigInteger.ONE)) {
				BigInteger x = k.add(BigInteger.ONE);
				char answer = 0;
				map[26] = s;
				int u = 26;
				int current = n;
				while (current >= 1 && answer == 0) {
					BigInteger sum = BigInteger.ZERO, prev;
					for (int i = 0; i < map[u].length(); ++ i) {
						prev = sum;
						char key = map[u].charAt(i);
						if (key >= 'A' && key <= 'Z') {
							sum = sum.add(count[key - 'A'][current]);
						} else {
							sum = sum.add(BigInteger.ONE);
						}
						if (sum.compareTo(x) >= 0) {
							x = x.subtract(prev);
							current --;
							if (key >= 'A' && key <= 'Z') {
								u = key - 'A';
							} else {
								answer = key;
							}
							break;
						}
					}
				}
				if (answer == 0) {
					int pivot = x.intValue() - 1;
					System.out.print(map[u].charAt(pivot));
				} else {
					System.out.print(answer);
				}
			}
			System.out.println("");
		}
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

    String nextLine() throws IOException {
    	return reader.readLine();
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

