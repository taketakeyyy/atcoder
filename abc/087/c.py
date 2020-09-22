# -*- coding: utf-8 -*-

if __name__ == '__main__':
    N = int(input())
    line1 = list(map(int, input().split()))
    line2 = list(map(int, input().split()))
    # 1行目の累積和
    dp1 = [line1[0]]
    for i in range(1, N):
        dp1.append(dp1[i-1]+line1[i])
    # 2行目の累積和
    dp2 = [line2[0]]
    for i in range(1, N):
        dp2.append(dp2[i-1]+line2[i])
    # 最大を探す
    maxv = 0
    for i in range(N):
        if i == 0:
            candies = dp1[i] + dp2[N-1]
        else:
            candies = dp1[i] + (dp2[N-1]-dp2[i-1])
        if candies > maxv:
            maxv = candies
    print(maxv)
