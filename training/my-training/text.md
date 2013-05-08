## Codeforces 258D Little Elephant and Broken Sorting

Problem: 数列A，按顺序给出M次交换操作(x, y)，每次操作有50%概率不执行。求最终逆序对数量的期望。<br></br>
Solution: probability[x, y]表示A[x] > A[y]的概率。对于每个(x, y)对所有i进行更新，并保证probability[x, y] = probability[y, x] = 0.5.

## ZOJ 3509 Island Communication

Problem: 无向图，三种操作：加边，删边，查询两点是否连通。删过的边不会再加进来。N < 500, M < 50000. <br></br>
Solution: 维护图中不存在环即可保证dfs的复杂度在O(N)。每次加边时如果形成了环，就在环里找到之后最早被删去的边并把他干掉。

## Codeforces 235B Let's Play Osu!

Problem: 连续进行N次操作，每次操作有prob[i]的概率画O，(1 - prob[i])的概率画X。对于操作完得到的序列，连续的x个O可以累加x^2的分数，序列总得分为每段连续的O的得分之和。求期望得分。N < 100000. <br></br>
Solution: dp[i]表示序列的前i项的期望得分，则dp[i] = dp[i - 1] + g[i]，其中g[i]为当前第i位的得分。显然，这一位有prob[i]的概率是一段O的末尾，得分应累加prob[i] * 1。在此基础上，有prob[i] * prob[i - 1]的概率是以OO作为末尾，此时最后一位的价值为4 - 1 = 3，其中有1分已经在prob[i]的部分算过，因此累加得分是prob[i] * prob[i - 1] * 2。以此类推，可以得到g[i] = prob[i] * 1 + prob[i] * prob[i - 1] * 2 + ... + PI(prob[j] j from 1 to i) * 2。这里g[i]可以从g[i - 1]推过来，总复杂度是O(n)。
