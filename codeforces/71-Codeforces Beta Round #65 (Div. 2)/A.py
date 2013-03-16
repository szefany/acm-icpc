#!/usr/bin/env python

test_count = input()

for t in range(test_count):
    string = raw_input()
    length = len(string)
    if length <= 10:
        print string
    else:
        print string[0] + str(length - 2) + string[length - 1]

