#!/usr/bin/env python

n = input()
elements = map(int, raw_input().split())

number = [0 for i in range(5)]
for value in elements:
    number[value] += 1

answer = number[4]

answer += number[3]
number[1] -= min(number[1], number[3])

answer += (number[2] + 1) / 2
if (number[2] % 2):
    number[1] -= min(2, number[1])

answer += (number[1] + 3) / 4

print answer
