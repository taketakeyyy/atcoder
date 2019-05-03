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

dp[i] := i本使うときの桁数のmax

dp[i] := max(dp[i-f(Aj)]+1 | j=1~M)

"""
from operator import attrgetter

class Number():
    def __init__(self, v, m):
        self.value = v
        self.match = m

def solve():
    N, M = list(map(int, input().split()))
    A = list(map(int, input().split()))

    num_dict = {}
    for a in A:
        if a == 1:
            num_dict[1] = 2
        elif a == 2:
            num_dict[2] = 5
        elif a == 3:
            num_dict[3] = 5
        elif a == 4:
            num_dict[4] = 4
        elif a == 5:
            num_dict[5] = 5
        elif a == 6:
            num_dict[6] = 6
        elif a == 7:
            num_dict[7] = 3
        elif a == 8:
            num_dict[8] = 7
        elif a == 9:
            num_dict[9] = 6

    # 消費マッチ棒が少ない順かつ、数字が大きい順
    num_matches = sorted(num_dict.items(), key=lambda x: x[0], reverse=True)
    num_matches = sorted(num_matches, key=lambda x: x[1])

    import copy
    if len(num_matches) >= 2:
        copied_num_matches = copy.deepcopy(num_matches)
        for i in range(len(copied_num_matches)-1):
            if copied_num_matches[i][1] == copied_num_matches[i+1][1]:
                # 消費マッチ数が同じなら、値が小さいやつは不要
                num_matches.remove(copied_num_matches[i+1])    

    # ・できるだけ桁数が大きいほうが良い
    # ・マッチ棒はちょうど使い切る必要がある
    while True:
        for num_i in range(len(num_matches)):
            now_num = num_matches[num_i][0]
            loop = N%now_num
            for loop_i in range(loop, 0, -1):
                nuw_num*loop_i


if __name__ == "__main__":
    solve()
