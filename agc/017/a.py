# -*- coding:utf-8 -*-

def solve():
    N, P = list(map(int, input().split()))
    As = list(map(int, input().split()))

    # 「取るか取らないかで調整する」典型問題
    # (1) 偶数個たべる必要があるパターン
    # 適当に奇数の袋を一つ選ぶ
    # 残ったN-1個のうち、好きに選んで食べても偶数個は食べれる
    # なぜなら、最初に選んだ袋を食べるか食べないかで偶数に調整可能だから
    even = 0
    odd = 0
    for a in As:
        if a%2==0:
            even += 1
        else:
            odd += 1

    if odd==0:
        # 調整不可能のとき
        if P==1:
            # 奇数個食べる必要があるとき
            print(0)
            return
        else:
            # 偶数個食べる必要があるとき
            print(pow(2,even))  # 0個たべるもOK
            return
    else:
        # 調整可能のとき
        print(pow(2,N-1))
        return


if __name__ == "__main__":
    solve()
