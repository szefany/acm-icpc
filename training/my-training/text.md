## Codeforces 258-D

Problem: 给定N个数和M次交换操作(x, y)，求最终逆序对数量的期望。

Solution: probability[x, y]表示element[x] > element[y]的概率。对于每个(x, y)对所有i进行更新，并保证probability[x, y] = probability[y, x] = 0.5.
