# -*- coding:utf-8 -*-

def solve():
    N, A = list(map(int, input().split()))
    X = list(map(int, input().split()))

    dp = [[[0 for _ in range(4000+1)] for __ in range(N+1)] for ___ in range(N+1)]

    """
    dp[i][j][k] := i枚のうち、k枚のカードを選んで、選んだカードの総和がkになる選び方の総数
    i: i枚目のカード
    j: j枚のカードを選んだ
    k: 選んだカードの総和
    """
    dp[0][0][0] = 1

    for i in range(N):
        for j in range(N):
            for k in range(4000+1):
                if (k+X[i] < 4000+1) :  # TLEして草
                    dp[i+1][j][k] += dp[i][j][k]  # i枚目を選ばなかった
                    dp[i+1][j+1][k+X[i]] += dp[i][j][k]  # i枚目を選んだ

    ans = 0
    for j in range(1, N+1):
        ans += dp[N][j][j*A]
    print(ans)


if __name__ == "__main__":
    solve()
