# -*- coding:utf-8 -*-
"""解説
https://qiita.com/drken/items/dc53c683d6de8aeacf5a#e-%E5%95%8F%E9%A1%8C---knapsack-2

・まず制約を見る
Wの最大値が10**9なので、dp[i][w] みたいにすると、間に合わない

N=100, viの最大値が10**3 なので、N+max(vi) = 10**5 なので、viを使うといけそう

dp[i][v] := i番目までを選んだ時の、価値がv以上のときの、重さの総和の最小値


・DPテーブル
      i   =   0      1      2      3      4      5
例: (w,v) = (2,3), (1,2), (3,6), (2,1), (1,3), (5,85)

i/v | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | ...
----------------------------------------------------------------------
0   | 0 | 2 | 2 | 2 | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞  | ∞  | ∞  | ∞  | ... 
1   | 0 | 1 | 1 | 2 | 3 | 3 | ∞ | ∞ | ∞ | ∞ | ∞  | ∞  | ∞  | ∞  | ...
2   | 0 | 1 | 1 | 2 | 3 | 3 | 3 | 4 | 4 | 5 | 6  | 6  | ∞  | ∞  | ...
3   |
4   |
5   |

     i    =    0        1        2        3
例: (w,v) = (1,100), (1,100), (1,100), (1,100)

i/v | 0 | 1 |...|100|101|...|200|201|...|300|301|...|400|401|...|500|501|...
----------------------------------------------------------------------------
0   | 0 | 1 | 1 | 1 | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ 
1   | 0 | 1 | 1 | 1 | 2 | 2 | 2 | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞
2   | 0 | 1 | 1 | 1 | 2 | 2 | 2 | 3 | 3 | 3 | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ | ∞
3   | 0 | 1 | 1 | 1 | 2 | 2 | 2 | 3 | 3 | 3 | 4 | 4 | 4 | ∞ | ∞ | ∞ | ∞ | ∞

"""

def solve():
    N, W = list(map(int, input().split()))
    Ws, Vs = [], []
    """
    for i in range(N):
        w, v = list(map(int, input().split()))
        Ws.append(w)
        Vs.append(v)
    """
    M = (10**3) * N
    
    # dp[i][v] := i番目までを選んだ時の、価値がv以上のときの、重さの総和の最小値
    dp = [[float("inf") for _ in range(0, M+1)] for __ in range(0, N)]

    # 初期値
    for i in range(0, N):
        dp[i][0] = 0 # 価値0の重さの最小値は0
    
    noww, nowv = list(map(int, input().split()))
    for v in range(1, M+1):
        if v <= nowv:
            dp[0][v] = noww
    
    # dpを埋める
    for i in range(1, N):
        noww, nowv = list(map(int, input().split()))
        for v in range(0, M+1):  
            if v-nowv >= 0:
                dp[i][v] = min(dp[i-1][v], dp[i-1][v-nowv]+noww)
            else:
                dp[i][v] = min(dp[i-1][v], noww)
            
            """
            if v-Vs[i] >= 0:
                dp[i][v] = min(dp[i][v], dp[i-1][v-Vs[i]]+Ws[i])  # 選んだとき
            dp[i][v] = min(dp[i][v], dp[i-1][v])
            """

    # 答えを出す
    for v in range(M, -1, -1):
        if dp[N-1][v] <= W:
            ans = v
            break
    """
    for v in range(0, 10**5+1):
        if dp[N-1][v] <= W:
            ans = v
    """
    print(ans)


if __name__ == "__main__":
    solve()
