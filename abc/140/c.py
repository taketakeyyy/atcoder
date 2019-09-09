# -*- coding:utf-8 -*-
import sys

"""
A1 A2 A3 A4 A5
B1 B2 B3 B4
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
        As[0] = As[1] = Bs[0]
    else:
        As[0], As[1] = Bs[0], Bs[1]

    for i in range(1, N-2):
        if Bs[i] > Bs[i+1]:
            As[i+1] = Bs[i+1]
        else:
            As[i+1] = Bs[i]
    As[N-1] = Bs[N-2]

    print(sum(As))



if __name__ == "__main__":
    solve()
