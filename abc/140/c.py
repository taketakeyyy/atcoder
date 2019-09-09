# -*- coding:utf-8 -*-
import sys

"""
Bs[i] >= max(As[i], As[i+1]) を満たす条件で、

sum(As)の最大値を求める問題
"""

def solve():
    N = int(sys.stdin.readline())
    Bs = list(map(int, sys.stdin.readline().split()))

    if N == 2:
        print(Bs[0]*2)
        return

    # 初期値を決める
    As = [0] * N
    if Bs[0] <= Bs[1]:
        # As:  ?   ?   →   As: 10  10
        # Bs: 10  20   →   Bs: 10  20
        As[0] = As[1] = Bs[0]
    else:
        # As:  ?   ?   →   As: 20  10
        # Bs: 20  10   →   Bs: 20  10
        As[0], As[1] = Bs[0], Bs[1]

    # 貪欲法
    for i in range(1, N-2):
        if Bs[i] > Bs[i+1]:
            # As:   ■    ?  →  As:   ■    0
            # Bs: 153    0  →  Bs: 153    0
            As[i+1] = Bs[i+1]
        else:
            # As:   ■    ?  →  As:   ■  153
            # Bs: 153  160  →  Bs: 153  160
            As[i+1] = Bs[i]
    As[N-1] = Bs[N-2]

    print(sum(As))


if __name__ == "__main__":
    solve()
