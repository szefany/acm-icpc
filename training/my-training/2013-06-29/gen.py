#!/usr/bin/env python
from random import randint

n = 5000

print n, n

for i in xrange(n):
    print randint(1, 100),
print ""
for i in xrange(n - 1):
    print randint(1, 100),
print ""
