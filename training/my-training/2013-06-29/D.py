n, m = map(int, raw_input().split())

a = [0 for i in xrange(m + 5)]
buffer = map(int, raw_input().split())
for i in xrange(m):
    a[i + 1] = buffer[i]

b = [0 for i in xrange(n + 5)]
if n > 1:
    buffer = map(int, raw_input().split())
    for i in xrange(n - 1):
        b[i + 2] = buffer[i]

if n == 1:
    print a[m]
elif m == 1:
    print b[n]
else:
    answer = 0
    sigma = []
    for i in xrange(2):
        sigma.append([0] * (m + 5))

    x, y = 0, 1
    for i in xrange(1, n + 1):
        x, y = y, x
        sigma[x][1] = 1
        j = 1
        if n - 1 == i:
            answer += a[m - j] * sigma[x][j]
        elif m - 1 == j:
            answer += b[n - i] * sigma[x][j]

        for j in xrange(2, m + 1):
            sigma[x][j] = sigma[y][j] + sigma[x][j - 1]
            if n - 1 == i:
                answer += a[m - j] * sigma[x][j]
            elif m - 1 == j:
                answer += b[n - i] * sigma[x][j]

    # answer = 0
    # for i in xrange(1, m + 1):
    #     answer += a[i] * sigma[n - 1][m - i]
    # for i in xrange(2, n + 1):
    #     answer += b[i] * sigma[n - i][m - 1]

    print answer
