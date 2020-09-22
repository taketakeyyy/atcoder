# -*- coding:utf-8 -*-
from fractions import gcd

def f(a, x):
    # 1~a以下の数で、xで割り切れるものの数を返す
    return a//x


def lcm(a, b):
    """ aとbの最小公倍数を返す """
    return a*b // gcd(a, b)


def solve():
    A,B,C,D = list(map(int, input().split()))
    A -= 1
    ans = (B - (f(B,C)+f(B,D)-f(B,lcm(C,D)))) - (A - (f(A,C)+f(A,D)-f(A,lcm(C,D))))
    print(ans)

if __name__ == "__main__":
    solve()
