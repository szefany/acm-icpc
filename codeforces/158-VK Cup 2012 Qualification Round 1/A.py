#!/usr/bin/env python

n, m = map(int, raw_input().split())
elements = [0] + map(int, raw_input().split())

answer = sum(elements[i] >= elements[m] and elements[i] > 0 for i in range(1, n + 1))
print answer

