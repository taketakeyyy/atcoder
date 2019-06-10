# -*- coding:utf-8 -*-

def solve():
    L = input()
    MOD = 10**9+7
    n = len(L)
    dp = [[0 for j in range(2)] for i in range(n+1)]
    dp[0][0] = 1

    for i, D in enumerate(L):
        # Da + Db = 0
        if D == "0":
            dp[i+1][0] = dp[i][0]  # (0,0)
            dp[i+1][1] = dp[i][1]  # (0,0)
        else:
            dp[i+1][1] = (dp[i][0] + dp[i][1]) % MOD  # D="1"のとき、DaとDbの組み合わせはない

        # Da + Db = 1
        if D == "0":
            dp[i+1][1] += (dp[i][1]*2 % MOD)
            dp[i+1][1] %= MOD
        else:
            dp[i+1][0] += dp[i][0]*2 % MOD
            dp[i+1][1] += dp[i][1]*2 % MOD
            dp[i+1][0] %= MOD
            dp[i+1][1] %= MOD

    ans = (dp[n][0] + dp[n][1]) % MOD
    print(ans)


if __name__ == "__main__":
    solve()
