# -*- coding:utf-8 -*-
"""解説
dp[j][k][s] := x1,...,xjから k枚選んで xiの合計をsにするような選び方の総数

[@lilium氏]
https://atcoder.jp/contests/abc044/submissions/5887235
"""

def solve():
    N, A = list(map(int, input().split()))
    X = list(map(int, input().split()))

    max_x = max(X)
    dp = [[[0 for _ in range(4000+1)] for __ in range(N+1)] for ___ in range(N+1)]

    dp[0][0][0] = 1

    # dp[i][j][k] := i枚のうちj枚を選んで、和がkになる組み合わせ
    """
    dp[i][j][k] 
    i : i枚目のカード
    j : 選んだカードの数
    k : 選んだカードの総和
    """
    for i in range(N):
        for j in range(N):
            for k in range(4000+1):
                if dp[i][j][k] != 0:
                    dp[i+1][j][k] += dp[i][j][k]  # i枚目を選ばなかった
                    dp[i+1][j+1][k+X[i]] += dp[i][j][k]  # i枚目を選んだ

    ans = 0
    for j in range(1, N+1):
        ans += dp[N][j][j*A]
    print(ans)

if __name__ == "__main__":
    solve()
