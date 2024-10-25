# -*- coding:utf-8 -*-
def solve():
    import sys

    N, L = list(map(int, sys.stdin.readline().split()))
    Xs = list(map(int, sys.stdin.readline().split()))
    Ts = list(map(int, sys.stdin.readline().split()))
    Xs = set(Xs)

    dp = [[float("inf") for __ in range(2)] for _ in range(L+1)]  # dp[i][j] := 座標iまでの時点での、行動j中の最小時間
    dp[0][0] = 0
    dp[0][1] = 0

    for i in range(1, L+1):
        # 行動1
        dp[i][0] = dp[i-1][0] + Ts[0]
        if i in Xs:
            dp[i][0] += Ts[2]

        # 行動2
        if i-2 >= 0:
            if i in Xs:
                dp[i][0] = min(dp[i][0], dp[i-2][0] + Ts[0] + Ts[1] + Ts[2])  # 地面に足ついてる
            else:
                dp[i][0] = min(dp[i][0], dp[i-2][0] + Ts[0] + Ts[1])  # 地面に足ついてる

        # 行動3
        if i-4 >= 0:
            if i in Xs:
                dp[i][0] = min(dp[i][0], dp[i-4][0] + Ts[0] + Ts[1]*3 + Ts[2])
            else:
                dp[i][0] = min(dp[i][0], dp[i-4][0] + Ts[0] + Ts[1]*3)

    if L-3 >= 0:
        dp[L][1] = min(dp[L][1], dp[L-3][0]+Ts[0]//2+(Ts[1]//2)*5)
    if L-2 >= 0:
        dp[L][1] = min(dp[L][1], dp[L-2][0]+Ts[0]//2+(Ts[1]//2)*3)
    if L-1 >= 0:
        dp[L][1] = min(dp[L][1], dp[L-1][0]+Ts[0]//2+Ts[1]//2)

    ans = min(dp[L][0], dp[L][1])
    print(ans)



def solve2():
    import sys

    N, L = list(map(int, sys.stdin.readline().split()))
    Xs = list(map(int, sys.stdin.readline().split()))
    Ts = list(map(int, sys.stdin.readline().split()))
    Xs = set(Xs)

    dp = [[float("inf") for __ in range(2)] for _ in range(L+1)]  # dp[i][j] := 座標iまでの時点での、行動j中の最小時間
    dp[0][0] = 0
    dp[0][1] = 0

    for i in range(1, L+1):
        # 行動1
        dp[i][0] = dp[i-1][0] + Ts[0]
        if i in Xs:
            dp[i][0] += Ts[2]

    for i in range(L+1):
        # 行動2
        if i-2 >= 0:
            if i in Xs:
                dp[i][0] = min(dp[i][0], dp[i-2][0] + Ts[0] + Ts[1] + Ts[2])  # 地面に足ついてる
            else:
                dp[i][0] = min(dp[i][0], dp[i-2][0] + Ts[0] + Ts[1])  # 地面に足ついてる
        if i-1 >= 0:
            dp[i][1] = min(dp[i][1], dp[i-1][0] + Ts[0]//2 + Ts[1]//2)  # ジャンプ中

    for i in range(L+1):
        # 行動3
        if i-4 >= 0:
            if i in Xs:
                dp[i][0] = min(dp[i][0], dp[i-4][0] + Ts[0] + Ts[1]*3 + Ts[2])
            else:
                dp[i][0] = min(dp[i][0], dp[i-4][0] + Ts[0] + Ts[1]*3)
        if i-3 >= 0:
            dp[i][1] = min(dp[i][1], dp[i-3][0]+Ts[0]//2+(Ts[1]//2)*5)
        if i-2 >= 0:
            dp[i][1] = min(dp[i][1], dp[i-2][0]+Ts[0]//2+(Ts[1]//2)*3)
        if i-1 >= 0:
            dp[i][1] = min(dp[i][1], dp[i-1][0]+Ts[0]//2+Ts[1]//2)

    ans = min(dp[L][0], dp[L][1])
    print(ans)


if __name__ == "__main__":
    solve()
