import sys
import collections
import math


def R(): return sys.stdin.readline().rstrip()


def MIS(): return map(int, R().split())


N, M, K, S, T = MIS()
dp = [[-1]*(K+1) for _ in range(N+1)]
adj = [[] for _ in range(N+1)]
radj = [[] for _ in range(N+1)]

for _ in range(M):
    a, b, t = MIS()
    adj[a].append((b, t))
    radj[b].append((a, t))

dp[S][0] = 0

for time in range(0, K+1):
    for i in range(1, N+1):
        if dp[i][time] == -1:
            continue
        for nxt, t in adj[i]:
            dp[nxt][time] = max(dp[nxt][time], dp[i][time] + t)
        if time+1 <= K:
            for prv, t in radj[i]:
                dp[prv][time+1] = max(dp[prv][time+1], dp[i][time])

ans = -1
for i in range(0, K+1):
    ans = max(ans, dp[T][i])
print(ans)
