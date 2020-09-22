# -*- coding:utf-8 -*-

def solve():
    N,A = list(map(int, input().split()))
    X = list(map(int, input().split()))

    # dp[i][j][k] := 左からi枚目までに、j枚を選んで、選んだカードの総和がk
    dp = [[[0 for _ in range(50*50+1)] for __ in range(N+1)] for ___ in range(N)]
    dp[0][0][0] = 1
    dp[0][1][X[0]] = 1

    for i in range(1, N):
        for j in range(0, N):
            for k in range(50*50+1):
                dp[i][j][k] += dp[i-1][j][k]
                if k+X[i] < 50*50+1:
                    dp[i][j+1][k+X[i]] += dp[i-1][j][k]
                    

    ans = 0
    for j in range(1, N+1):
        ans += dp[N-1][j][A*j]
    print(ans)


if __name__ == "__main__":
    solve()
