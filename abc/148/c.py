# -*- coding:utf-8 -*-
from fractions import gcd

def lcm(a, b):
    """ aとbの最小公倍数を返す """
    return a*b // gcd(a, b)

def solve():
    A, B = list(map(int, input().split()))

    print(lcm(A, B))

if __name__ == "__main__":
    solve()
