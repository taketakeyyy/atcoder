# -*- coding:utf-8 -*-
import sys
from fractions import gcd

def f(a, x):
    """1以上a以下で、xで割り切れるものの数"""
    return a // x

def lcm(a, b):
    """ aとbの最小公倍数を返す """
    return a*b // gcd(a, b)

def solve():
    A, B, C, D = list(map(int, sys.stdin.readline().split()))
    A -= 1

    # CでもDでも割り切れないもの
    b = B - f(B, C) - f(B, D) + f(B, lcm(C, D))
    a = A - f(A, C) - f(A, D) + f(A, lcm(C, D))
    print(b-a)


if __name__ == "__main__":
    solve()
