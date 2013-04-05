## Codeforces 258-D

Problem: 数列A，按顺序给出M次交换操作(x, y)，每次操作有50%概率不执行。求最终逆序对数量的期望。<br></br>
Solution: probability[x, y]表示A[x] > A[y]的概率。对于每个(x, y)对所有i进行更新，并保证probability[x, y] = probability[y, x] = 0.5.
