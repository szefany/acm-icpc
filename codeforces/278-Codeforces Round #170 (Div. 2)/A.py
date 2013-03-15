#!/usr/bin/env python

n = input()
elements = [0] + map(int, raw_input().split())
start, end = map(int, raw_input().split())

if (start > end):
    start, end = end, start

total = sum(elements[:])
current = sum(elements[i] for i in range(start, end))

print min(current, total - current)

