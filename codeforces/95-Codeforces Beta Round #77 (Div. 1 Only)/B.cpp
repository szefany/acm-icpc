// Codeforces Beta Round #77 (Div. 1 Only)
// Problem B, Lucky Numbers
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

char str[100005];

void output (int pivot, int number, int count_4, int count_7) {
    for (int i = 0; i <= pivot; ++ i) {
        putchar (str[i]);
    }
    if (count_7 >= count_4) {
        for (int i = 1; i <= count_7 - count_4; ++ i) {
            putchar ('4');
            number --;
        }
        for (int i = 1; i <= number / 2; ++ i) {
            putchar ('4');
        }
        for (int i = 1; i <= number / 2; ++ i) {
            putchar ('7');
        }
        puts ("");
        return;
    }
    int seven = (number + count_4 - count_7) / 2;
    int four = number - seven;
    for (int i = 1; i <= four; ++ i) {
        putchar ('4');
    }
    for (int i = 1; i <= seven; ++ i) {
        putchar ('7');
    }
    puts ("");
    return;
}

int main () {
    scanf ("%s", str);
    int len = strlen (str);
    if (len & 1) {
        len ++;
        for (int i = 1; i <= len / 2; ++ i) {
            putchar ('4');
        }
        for (int i = 1; i <= len / 2; ++ i) {
            putchar ('7');
        }
        puts ("");
        return 0;
    }
    int count_4 = 0, count_7 = 0, last = -1, pivot = -2;
    for (int i = 0; i < len; ++ i) {
        if (str[i] == '4') {
            count_4 ++;
            last = i;
            continue;
        }
        if (str[i] == '7') {
            count_7 ++;
            continue;
        }
        if (str[i] < '4') {
            pivot = i - 1;
        }
        else if (str[i] < '7') {
            str[i] = '7';
            count_7 ++;
            pivot = i;
        }
        else {
            if (last == -1) {
                len += 2;
                for (int i = 1; i <= len / 2; ++ i) {
                    putchar ('4');
                }
                for (int i = 1; i <= len / 2; ++ i) {
                    putchar ('7');
                }
                puts ("");
                return 0;
            }
            count_7 ++;
            count_4 --;
            str[last] = '7';
            pivot = last;
        }
        break;
    }
    if (pivot == -2) {
        pivot = len - 1;
    }
    int number = len - pivot - 1;
    if (abs (count_7 - count_4) <= number) {
        output (pivot, number, count_4, count_7);
        return 0;
    }
    for (int i = pivot; i >= 0; -- i) {
        if (str[i] == '4') {
            str[i] = '7';
            count_4 --;
            if (abs (count_7 + 1 - count_4) <= number) {
                output (i, number, count_4, count_7 + 1);
                return 0;
            }
        }
        else if (str[i] == '7') {
            count_7 --;
        }
        number ++;
    }
    len += 2;
    for (int i = 1; i <= len / 2; ++ i) {
        putchar ('4');
    }
    for (int i = 1; i <= len / 2; ++ i) {
        putchar ('7');
    }
    puts ("");
    return 0;
}
