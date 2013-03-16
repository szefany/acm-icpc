#/usr/bin/env python
import sys

elements = []

for line in sys.stdin:
    elements.extend(map(int, line.split()))

for value in reversed(elements):
    print "%.4f" % value ** 0.5

