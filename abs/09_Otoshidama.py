#-*- coding:utf-8 -*-
import math

if __name__ == "__main__":
    """
    dp[i][yen] := i枚目のとき、yen円はあり得るかどうか（True/False）
    dp[i][yen] = dp[i-1][yen-10000] | dp[i-1][yen-5000] | dp[i-1][yen-1000]
    初期値:dp[0][0] = True
    求める:dp[N][Y]
    """
    """
    N, Y = list(map(int, input().split()))
    dp[[False for i in range(Y+1)] for j in range(N+1)]
    dp[0][0] = True
    for i in range(1, N+1):
        MIN_YEN = 1000 * i
        MAX_YEN = 10000 * i
        for yen in range(MIN_YEN, MAX_YEN+1, 1000):
            if yen >= 10000:
                dp[i][yen] = dp[i-1][yen-10000]
            if yen >= 5000:
                dp[i][yen] = dp[i-1][yen-5000]
            dp[i][yen] = dp[i-1][yen-1000]
    """
    # 回答する

    # x,y,zを全探索
    N, Y = list(map(int, input().split()))
    for x in range(N+1):
        for y in range(N+1-x):
            z = N-x-y
            yen = 10000*x + 5000*y + 1000*z
            if yen == Y:
                print("{} {} {}".format(x, y, z))
                exit()
    print("-1 -1 -1")
