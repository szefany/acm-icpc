## Codeforces 258D Little Elephant and Broken Sorting

Problem: 数列A，按顺序给出M次交换操作(x, y)，每次操作有50%概率不执行。求最终逆序对数量的期望。<br></br>
Solution: probability[x, y]表示A[x] > A[y]的概率。对于每个(x, y)对所有i进行更新，并保证probability[x, y] = probability[y, x] = 0.5.

## ZOJ 3509 Island Communication

Problem: 无向图，三种操作：加边，删边，查询两点是否连通。删过的边不会再加进来。N < 500, M < 50000. <br></br>
Solution: 维护图中不存在环即可保证dfs的复杂度在O(N)。每次加边时如果形成了环，就在环里找到之后最早被删去的边并把他干掉。

## Codeforces 235B Let's Play Osu!

Problem: 连续进行N次操作，每次操作有prob[i]的概率画O，(1 - prob[i])的概率画X。对于操作完得到的序列，连续的x个O可以累加x^2的分数，序列总得分为每段连续的O的得分之和。求期望得分。N < 100000. <br></br>
Solution: dp[i]表示序列的前i项的期望得分，则dp[i] = dp[i - 1] + g[i]，其中g[i]为当前第i位的得分。显然，这一位有prob[i]的概率是一段O的末尾，得分应累加prob[i] * 1。在此基础上，有prob[i] * prob[i - 1]的概率是以OO作为末尾，此时最后一位的价值为4 - 1 = 3，其中有1分已经在prob[i]的部分算过，因此累加得分是prob[i] * prob[i - 1] * 2。以此类推，可以得到g[i] = prob[i] * 1 + prob[i] * prob[i - 1] * 2 + ... + PI(prob[j] j from 1 to i) * 2。这里g[i]可以从g[i - 1]推过来，总复杂度是O(n)。

## Codeforces 229E Gifts

Problem: M种礼物，每种礼物若干个，有不同的价值，需要在所有礼物中选择N个出来。每选择一组中的s个，对方会在这一组中随机返回s个回来。选的时候采取最优策略，即选择一种取法，尽量使自己拿到最大的N个。如果有多种取法，在其中随机选择一种。问最终能拿到最大的N个礼物的概率。N, M < 1000.<br></br>

Solution: 注意到取法必然是这样子的：假设第N大的礼物价值是x，那么每一组当中所有大于x的都是必须取的，把个数记为must[i]。每一组中等于x的礼物是可选的，个数记为optional[i]。所有的optional[i]之和为total，我们需要在其中选择N - Sigma{must[i]}个出来。<br></br>

prob[i, j]表示前i组，已经取了j个optional的礼物的概率。很重要的一点是，已经取的optional的数量，会影响到当前这一组礼物是否取optional的概率。如果当前已经取了j个optional，那么当前取optional的概率为p = C[left - 1, total - j - 1] / C[left, total - j]，其中left是从当前组到最后一组还剩下的optional的数量。<br></br>

转移的时候分两种情况：  

1. optional[i] = 0:  prob[i, j] = prob[i - 1, j] / C[size, must]
2. optional[i] != 0: prob[i, j] = prob[i - 1, j - 1] * p / C[size, must + 1] + prob[i - 1, j] * p0 / C[size, must]

其中p0是在prob[i - 1, j]下不取当前组的概率。如果采用顺推的方法，应该可以避免p0 != 1 - p的这个问题，不过prob[i, j]的含义就应该变化为ij状态下，当前组还没取的概率。总复杂度是O(NM).

