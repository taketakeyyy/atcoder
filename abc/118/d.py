# -*- coding:utf-8 -*-
""" 解説
DP

dp[i] := i本使ってできる最大の数

優先順位
1. 文字列の長さが長いほう
2. 文字列として比較

f(x) := xをつくるために使うマッチの本数

dp = max(dp[i-f(Aj)]+Aj | j=1~M)

"""

""" 解説2
DP

f(x) := xをつくるために使うマッチの本数

dp[i] := i本使うときの桁数のmax

dp[i] := max(dp[i-f(Aj)]+1 | j=1~M)

"""
from operator import attrgetter

def num2match(x):
    # 1,2,3,4,5,6,7,8,9を 1つ作るには、それぞれちょうど 2,5,5,4,5,6,3,7,6本のマッチを使う
    if x == 1:
        return 2
    elif x == 2:
        return 5
    elif x == 3:
        return 5
    elif x == 4:
        return 4
    elif x == 5:
        return 5
    elif x == 6:
        return 6
    elif x == 7:
        return 3
    elif x == 8:
        return 7
    elif x == 9:
        return 6


def solve():
    N, M = list(map(int, input().split()))
    A = list(map(int, input().split()))
    A.sort()

    # dp[i] := マッチi本使うときの最大桁数
    dp = [0] * (N+1)
    dp[1] = 0

    for i in range(2, N+1):
        tmp = 0
        for a in A:
            if i-num2match(a) >= 0:
                tmp = max(tmp, dp[i-num2match(a)] + 1)
        dp[i] = tmp
    
    ans = ""
    remain = dp[N] # 残りの桁数
    match = N # 残りのマッチ本数
    while(match > 0):
        for i in range(M-1, -1, -1):
            if dp[match-num2match(A[i])] == remain-1:
                ans += str(A[i])
                match -= num2match(A[i])
                remain -= 1
    print(ans)

    

if __name__ == "__main__":
    solve()
