# -*- coding:utf-8 -*-

"""解説
https://www.youtube.com/watch?v=nCHz87GMdpo



"""

def solve2():
    """ 全探索O(F**2) """
    A, B, C, D, E, F = list(map(int, input().split()))

    # 水をx, 砂糖をyとする
    sugars = []
    for i in range(0, F+1):
        for j in range(0, F+1):
            y = i*C + j*D
            if y <= F:
                # 作れる砂糖の量y[g]をメモする
                sugars.append(y)

    water = []
    for i in range(0, F+1):
        for j in range(0, F+1):
            x = 100*A*i + 100*B*j
            if x <= F:
                # 作れる水の量x[g]をメモする
                water.append(x)
    
    sugars.sort()
    water.sort()

    # 濃度
    concent = 0
    for x in water:
        for y in sugars:
            if x+y > F:
                break
            if x+y > 0 and y/(x+y) <= E/(100+E):
                if y/(x+y) >= concent:
                    concent = y/(x+y)
                    ans = "{} {}".format(x+y, y)
    print(ans)


def solve():
    """ WA 
    dp[i] := 砂糖水i[g]のときにつくれる最大の砂糖の量
    貰うDP

    *注意
    1 2 10 20 15 200
    つまりC=10でdp[10]のとき、水0[g]砂糖10[g]だが、このとき濃度は100%になってしまうが、これを許可するか？
    """
    A, B, C, D, E, F = list(map(int, input().split()))
    
    dp= [0]*(F+1)

    for i in range(0, F+1):
        tmp1, tmp2, tmp3, tmp4 = 0, 0, 0, 0
        if i-100*A >= 0:
            tmp1 = dp[i-100*A]
        if i-100*B >= 0:
            tmp2 = dp[i-100*B]
        if (i-C >= 0) and ((dp[i-C]+C)/i <= E/(100+E)):
            tmp3 = dp[i-C]+C
        if (i-D >= 0) and ((dp[i-D]+D)/i <= E/(100+E)):
            tmp4 = dp[i-D]+D
        dp[i] = max(tmp1, tmp2, tmp3, tmp4)
    # 各砂糖水に対して濃度を計算し、最大の濃度のときの砂糖水と砂糖の量が答え
    print(dp[110])
    max_noudo = 0
    for i in range(1, F+1):
        now_noudo = dp[i]/i
        if now_noudo <= E/(100+E) and now_noudo >= max_noudo:
            max_noudo = now_noudo
            ans = "{} {}".format(i, dp[i])

    print(ans)

if __name__ == "__main__":
    solve()
