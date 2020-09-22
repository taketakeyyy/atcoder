#-*- coding:utf-8 -*-

def solver():
    # rookzeno氏の回答
    a,b = map(int,input().split())
    c = list(map(int,input().split()))
    d = list(map(int,input().split()))

    # 逆に並び替える
    c = c[::-1]
    d = d[::-1]

    dp = [[0]*(a+1) for i in range(b+1)]

    # 左の山のみ
    for i in range(a):
      if (a+b-i)%2 == 1:
        # 先手
        dp[0][i+1] = c[i] + dp[0][i]
      else:
        # 後手
        dp[0][i+1] = dp[0][i]

    # 右の山のみ
    for i in range(b):
      if (a+b-i) %2 == 1:
        # 先手
        dp[i+1][0] = d[i] + dp[i][0]
      else:
        # 後手
        dp[i+1][0] = dp[i][0]

    # 左右の山からどうとるか
    for i in range(1,a+1):
      for j in range(1,b+1):
        if (a+b-i-j) %2 == 1:
          # 後手
          dp[j][i] = min(dp[j-1][i], dp[j][i-1])
        else:
          # 先手
          dp[j][i] = max(dp[j-1][i]+d[j-1], dp[j][i-1]+c[i-1])

    print(dp[b][a])

def solver2():
    A, B = list(map(int, input().split()))
    As = list(map(int, input().split()))
    Bs = list(map(int, input().split()))

    As = As[::-1]
    Bs = Bs[::-1]
    # dp[left][right] := 山にleft, right枚残っているときの、すぬけの最善価値
    dp = [[0 for l in range(B+1)] for r in range(A+1)]

    # 左の山
    for l in range(A):
        if (A+B-l)%2 == 1:
            # 先手
            dp[l+1][0] = dp[l][0] + As[l]
        else:
            # 後手
            dp[l+1][0] = dp[l][0]

    # 右の山
    for r in range(B):
        if (A+B-r)%2 == 1:
            dp[0][r+1] = dp[0][r] + Bs[r]
        else:
            dp[0][r+1] = dp[0][r]

    # 左右の山
    for l in range(1, A+1):
        for r in range(1, B+1):
            if(A+B-l-r)%2 == 0:
                # 先手
                dp[l][r] = max(dp[l-1][r]+As[l-1], dp[l][r-1]+Bs[r-1])
            else:
                # 後手
                dp[l][r] = min(dp[l-1][r], dp[l][r-1])

    # output
    print(dp[A][B])

if __name__ == "__main__":
    solver2()
