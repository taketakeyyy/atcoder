# -*- coding:utf-8 -*-
from fractions import gcd

def lcm(a, b):
    """ aとbの最小公倍数を返す """
    return a*b // gcd(a, b)

def f(a, x, y):
    """ a以下で、xでもyでも割り切れないものの数"""
    return a - (a//x + a//y - a//lcm(x,y))

def solve():
    A,B,C,D = list(map(int, input().split()))
    ans = f(B, C, D) - f(A-1, C, D)
    print(ans)

if __name__ == "__main__":
    solve()
