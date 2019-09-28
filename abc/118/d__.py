import numpy as np

# 入力処理
num = [0, 2, 5, 5, 4, 5, 6, 3, 7, 6]
N, M = map(int, input().split())
A = [int(s) for s in input().split()]
A.sort(reverse = True)

#
dp = np.zeros(N+1, dtype = np.int)
MIN = -10**9
for i in range(1, N+1):
    mx = MIN
    for a in A:
        k = i-num[a]
        if k >= 0:
            mx = max(mx, dp[k] + 1)
    dp[i] = mx

d = dp[N]
n = N
s = []
for i in range(0, d):
    for a in A:
        tmp = n-num[a]
        if tmp >= 0 and dp[tmp] == dp[n]-1:
            s.append(str(a))
            n -= num[a]
            break
print("".join(s))
