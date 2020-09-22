# -*- coding:utf-8 -*-
"""解説
dp[j][k][s] := x1,...,xjから k枚選んで xiの合計をsにするような選び方の総数

[@lilium氏]
https://atcoder.jp/contests/abc044/submissions/5887235
"""

def solve():
    N, A = list(map(int, input().split()))
    X = list(map(int, input().split()))

    dp = [[[0 for _ in range(50*50+1)] for __ in range(N+1)] for ___ in range(N+1)]
    dp[0][0][0] = 1  # 何も選んでない初期値

    """
    dp[i][j][k] := 左からi+1枚目までに、j枚のカードを選んで、選んだカードの総和がkになる選び方の総数
    i: 左からi+1枚目のカード
    j: j枚のカードを選んだ
    k: 選んだカードの総和
    """
    for i in range(0, N):
        for j in range(0, N):
            for k in range(50*50+1):
                dp[i+1][j][k] += dp[i][j][k]  # i枚目を選ばない
                if k-X[i] >= 0:
                    dp[i+1][j+1][k] += dp[i][j][k-X[i]]  # i枚目を選んだ

    ans = 0
    for j in range(1, N+1):  # 1枚以上選ぶ必要がある
        ans += dp[N][j][j*A]
    print(ans)

if __name__ == "__main__":
    solve()
