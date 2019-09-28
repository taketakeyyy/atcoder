# -*- coding:utf-8 -*-
import sys
from fractions import gcd
from collections import Counter


def prime_factorization(n):
    """nを素因数分解する

    Return d(dict):
        素因数をキー、素因数の指数部を値とするディクショナリを返す

    Example:
        n=140 -> d = {2: 2, 5: 1, 7: 1}
    """
    d = Counter()
    m = 2
    while m*m <= n:
        while n%m == 0:
            n //= m
            d[m] += 1
        m = m + 1 if m == 2 else m + 2

    if n > 1:
        d[n] += 1
    return d


def solve():
    A, B = list(map(int, sys.stdin.readline().split()))
    cd = gcd(A, B)

    if cd == 1:
        print(1)
        return

    """
    (素因数分解の素因数の個数)+1が答え
    """

    prime_d = prime_factorization(cd)
    print(len(prime_d)+1)


if __name__ == "__main__":
    solve()
