# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))
    A = {}
    for i in range(1, N+1):
        A[i] = True  # 踏める
    for i in range(M):
        a = int(input())
        A[a] = False  # 踏めない
    MOD = 10**9+7

    # dp[i] := i段目までの場合の数
    dp = [0] * (N+1)
    dp[0] = 1

    for i in range(1, N+1):
        if A[i] is False: continue

        dp[i] += dp[i-1]
        if i-2 >= 0:
            dp[i] += dp[i-2]
        dp[i] %= MOD
    
    print(dp[N]%MOD)


if __name__ == "__main__":
    solve()
