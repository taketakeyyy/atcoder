# -*- coding:utf-8 -*-
from decimal import Decimal, getcontext
getcontext().prec = 1000


def solve():
    L = int(input())
    a = Decimal(L/3)
    print(Decimal(a**3))


if __name__ == "__main__":
    solve()
