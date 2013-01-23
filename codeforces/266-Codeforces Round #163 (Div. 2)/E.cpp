// Codeforces Round #163 (Div. 2)
// Problem E, More Queries to Array
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 100005;
const int MOD = 1000000000 + 7;

struct Tree {
	int l, r, lch, rch, cover;
	int values[6], square[6];
} T[N << 1];
int first[N], nodeCount, root;

int elements[N];
int n, m;

#define L T[u].lch
#define R T[u].rch

void update (int u) {
	for (int i = 0; i < 6; ++ i) {
		T[u].values[i] = ((long long)T[L].values[i] + T[R].values[i]) % MOD;
	}
}

void update_square (int u) {
	for (int i = 0; i < 6; ++ i) {
		T[u].square[i] = ((long long)T[L].square[i] + T[R].square[i]) % MOD;
	}
}

void build (int &u, int l, int r) {
	u = ++ nodeCount;
	T[u].l = l, T[u].r = r, T[u].cover = -1;
	if (l == r) {
		T[u].cover = elements[l];
		T[u].values[0] = elements[l];
		T[u].square[0] = 1;
		for (int i = 1; i < 6; ++ i) {
			T[u].square[i] = (long long)T[u].square[i - 1] * (l + 1) % MOD;
			T[u].values[i] = (long long)elements[l] * T[u].square[i] % MOD;
		}
		return;
	}
	build (T[u].lch, l, l + r >> 1);
	build (T[u].rch, l + r + 2 >> 1, r);
	update (u);
	update_square (u);
}

void down_cover (int u) {
	int key = T[u].cover;
	for (int i = 0; i < 6; ++ i) {
		T[L].values[i] = (long long)key * T[L].square[i] % MOD;
		T[R].values[i] = (long long)key * T[R].square[i] % MOD;
	}
	T[L].cover = T[R].cover = T[u].cover;
	T[u].cover = -1;
}

void cover (int u, int l, int r, int key) {
	if (l <= T[u].l && r >= T[u].r) {
		T[u].cover = key;
		for (int i = 0; i < 6; ++ i) {
			T[u].values[i] = (long long)key * T[u].square[i] % MOD;
		}
		return;
	}
	if (T[u].cover != -1) {
		down_cover (u);
	}
	if (l < T[R].l) cover (L, l, r, key);
	if (r > T[L].r) cover (R, l, r, key);
	update (u);
}

int mod (long long x) {
	return (x % MOD + MOD) % MOD;
}

long long trans (long long a, int pivot, int u) {
	return mod ((long long)mod (a) * T[u].values[pivot]);
}

int query (int u, int l, int r, int k, int left) {
	if (l <= T[u].l && r >= T[u].r) {
		int result;
		if (k == 0) {
			result = mod (trans (1, 0, u));
		}
		else if (k == 1) {
			result = mod (trans (1, 1, u) - trans (left, 0, u));
		}
		else if (k == 2) {
			result = mod (trans (1, 2, u) - trans (2 * left, 1, u) + trans ((long long)left * left, 0, u));
		}
		else if (k == 3) {
			result = mod (trans (1, 3, u) - trans (3 * left, 2, u) + trans ((long long)3 * left * left, 1, u) - trans ((long long)left * left * left, 0, u));
		}
		else {
			int l4 = mod ((long long)mod ((long long)left * left) * (long long)mod ((long long)left * left));
			if (k == 4) {
				result = mod (trans (1, 4, u) - trans (4 * left, 3, u) + trans ((long long)6 * left * left, 2, u) - trans ((long long)4 * left * left * left, 1, u)
					+ trans (l4, 0, u));
			}
			else if (k == 5) {
				int l5 = mod ((long long)l4 * left);
				result = mod (trans (1, 5, u) - trans (5 * left, 4, u) + trans ((long long)10 * left * left, 3, u) - trans ((long long)10 * left * left * left, 2, u)
					+ trans ((long long)5 * l4, 1, u) - trans (l5, 0, u));
			}
		}
		return result;
	}
	if (T[u].cover != -1) {
		down_cover (u);
	}
	int result;
	if (r < T[R].l) result = query (L, l, r, k, left);
	else if (l > T[L].r) result = query (R, l, r, k, left);
	else result = mod (query (L, l, r, k, left) + query (R, l, r, k, left));
	update (u);
	return result;
}

int main () {
	freopen ("input.txt", "r", stdin);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		scanf ("%d", &elements[i]);
	}
	build (root, 1, n);
	while (m --) {
		char buffer[2];
		int l, r, key;
		scanf ("%s %d%d%d", buffer, &l, &r, &key);
		if (*buffer == '=') {
			cover (root, l, r, key);
		}
		else {
			printf ("%d\n", query (root, l, r, key, l));
		}
	}
	return 0;
}