# -*- coding:utf-8 -*-
"""
問題
https://atcoder.jp/contests/dp/tasks/dp_d

解説
https://qiita.com/drken/items/dc53c683d6de8aeacf5a#d-%E5%95%8F%E9%A1%8C---knapsack-1
"""

def solve():
    N, LIMIT = list(map(int, input().split()))
    W, V = [None], [None]
    for i in range(N):
        w, v = list(map(int, input().split()))
        W.append(w)
        V.append(v)
    
    # dp[i][w] := i個目までの品物を選んだ時の、重さがwのときの価値の最大値
    dp = [[w for w in range(LIMIT+1)] for i in range(N+1)]
    for w in range(LIMIT+1):
        dp[0][w] = 0
    
    #O(N*LIMIT) = O(10**7)
    for i in range(1, N+1):
        for w in range(LIMIT+1):
            if w-W[i] >= 0:
                dp[i][w] = max(dp[i-1][w], dp[i-1][w-W[i]] + V[i])
            else:
                dp[i][w] = dp[i-1][w]

    ans = 0
    for w in range(LIMIT+1):
        ans = max(ans, dp[N][w])

    print(ans)


if __name__ == "__main__":
    solve()
