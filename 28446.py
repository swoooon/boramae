import sys
import collections
import math


def R(): return sys.stdin.readline().rstrip()


def MIS(): return map(int, R().split())


dic = {}
for _ in range(int(R())):
    a = list(MIS())
    if a[0] == 1:
        dic[a[2]] = a[1]
    else:
        print(dic[a[1]])
