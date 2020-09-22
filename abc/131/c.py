# -*- coding:utf-8 -*-
"""解説
B以下の整数のうち、CでもDでも割り切れないものの個数をCountBとする
A以下の整数のうち、CでもDでも割り切れないものの個数をCountAとする

求める答えは、CountB - CountA

・CountBの求め方
B以下の整数のうち、Cで割り切れるものの個数はCountB_C = B//C
B以下の整数のうち、Dで割り切れるものの個数はCountB_D = B//D
B以下の整数のうち、CでもDでも割り切れるものの個数はCountB_CD = B//lcm(C,D)

CountB = B - (CountB_C + CountB_D - CountB_CD)

"""
from fractions import gcd
from math import floor

def solve():
    A, B, C, D = list(map(int, input().split()))
    def lcm(a, b):
        """ aとbの最小公倍数を返す """
        return a*b // gcd(a, b)

    def f(x):
        """ 1以上x以下の整数のうち、CでもDでも割り切れないものの個数を返す """
        #return x - (floor(x/C) + floor(x/D) - floor(x/lcm(C,D)))  # こっちだとWA
        return x - (x//C + x//D - x//lcm(C,D))  # こっちだとAC

    ans = f(B) - f(A-1)

    print(ans)


if __name__ == "__main__":
    solve()
