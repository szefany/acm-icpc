#!/usr/bin/env python
n = input()

if n < 3:
    print n
elif n % 2 == 1:
    print n * (n - 1) * (n - 2)
elif n % 6 == 0:
    print (n - 1) * (n - 2) * (n - 3)
else:
    print n * (n - 1) * (n - 3)
