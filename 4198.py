from bisect import bisect_left
import sys
import collections
import math


def R(): return sys.stdin.readline().rstrip()


def MIS(): return map(int, R().split())


N = int(R())
L = [int(R()) for _ in range(N)]
lis = [0]*N
lds = [0]*N

for x in range(N):
    dp = []
    for i in range(x, N):
        index = bisect_left(dp, L[i])
        if len(dp) <= index:
            dp.append(L[i])
        else:
            if index == 0:
                continue
            dp[index] = L[i]
        lis[x] = len(dp)

for i in range(N):
    L[i] = -L[i]

for x in range(N):
    dp = []
    for i in range(x, N):
        index = bisect_left(dp, L[i])
        if len(dp) <= index:
            dp.append(L[i])
        else:
            if index == 0:
                continue
            dp[index] = L[i]
        lds[x] = len(dp)
ans = 0
for i in range(N):
    ans = max(ans, lis[i]+lds[i]-1)
print(ans)
