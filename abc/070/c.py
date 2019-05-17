# -*- coding:utf-8 -*-
"""解説

(例)
T0 = 2
T1 = 3

直感的に、最小公倍数が答え。
よって6。
"""
from fractions import gcd
from functools import reduce


def lcm(a, b):
    """ aとbの最小公倍数を返す """
    return a*b/gcd(a, b)

def solve():
    N = int(input())
    T = []
    for i in range(N):
        T.append(int(input()))
    ans = reduce(lcm, T)
    print(ans)


if __name__ == "__main__":
    solve()
