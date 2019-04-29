# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    MOD = 10**9 + 7

    """
    AGCTをそれぞれ、
    0123と置き換えて考える
    
    条件は
    ・文字0~3のみで構成される
    ・012を含まない
    ・隣同士をswapしても012を含まない

    出ちゃダメなパターンを考えると、
    ・012
    ・102
    ・021
    ・0?12
    ・01?2

    条件を満たしている部分文字列Sに対して、
    ・S+0 をしたときは大丈夫
    ・S+1 をしたとき、最後が021になるとダメ
    ・S+2 をしたとき、最後が012, 102, 0?12, 01?2になるとダメ
    ・S+3 をしたときは大丈夫
    
    と考えると、部分文字列の最後の3文字を見ると条件を満たしているかを判定できる

    dp[i][c1][c2][c3] := 部分文字列の長さiのときで、部分文字列の最後の文字列がc1c2c3のときの、条件を満たす個数
    """

    dp = [[[[0 for _ in range(4)] for __ in range(4)] for ___ in range(4)] for ____ in range(N+1)]

    for c1 in range(4):
        for c2 in range(4):
            for c3 in range(4):
                dp[0][c1][c2][c3] = 0
                dp[1][c1][c2][c3] = 0
                dp[2][c1][c2][c3] = 0
                dp[3][c1][c2][c3] = 1
    dp[3][0][2][1] = 0
    dp[3][0][1][2] = 0
    dp[3][1][0][2] = 0

    for i in range(3, N):
        for c1 in range(4):
            for c2 in range(4):
                for c3 in range(4):
                    if dp[i][c1][c2][c3] == 0:
                        # 0のやつは、何を足しても0
                        dp[i+1][c1][c2][c3] = 0
                        continue

                    for a in range(4):
                        # aは次に足す文字(0~3)
                        if ((c2==0 and c3==2 and a==1) or
                            (c2==0 and c3==1 and a==2) or
                            (c2==1 and c3==0 and a==2) or
                            (c1==0 and c3==1 and a==2) or
                            (c1==0 and c2==1 and a==2)):
                            # 021, 012, 102, 0?12, 01?2 になるとダメ
                            dp[i+1][c2][c3][a] = 0
                            continue

                        # それ以外の場合
                        dp[i+1][c2][c3][a] += dp[i][c1][c2][c3]
                        dp[i+1][c2][c3][a] %= MOD
    
    ans = 0
    for c1 in range(4):
        for c2 in range(4):
            for c3 in range(4):
                ans += dp[N][c1][c2][c3]
                ans %= MOD
    print(ans)


if __name__ == "__main__":
    solve()
