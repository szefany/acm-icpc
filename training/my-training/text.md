## Codeforces 258-D

Problem: 数列A，按顺序给出M次交换操作(x, y)，每次操作有50%概率不执行。求最终逆序对数量的期望。<br></br>
Solution: probability[x, y]表示A[x] > A[y]的概率。对于每个(x, y)对所有i进行更新，并保证probability[x, y] = probability[y, x] = 0.5.

## ZOJ 3509 Island Communication

Problem: 无向图，三种操作：加边，删边，查询两点是否连通。删过的边不会再加进来。$N \leq 500, M \leq 50000$.
Solution: 维护图中不存在环即可保证dfs的复杂度在O(N)。每次加边时如果形成了环，就在环里找到之后最早被删去的边并把他干掉。
