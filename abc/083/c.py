# -*- coding:utf-8 -*-
import math
from decimal import *

def main():
    X, Y = list(map(int, input().split()))

    #implements
    # X*2*n < Y を満たす最大のnは？
    ans = 1
    while True:
        X = X*2
        if X > Y:
            break
        ans += 1
    print(ans)

def main2():
    # コーナーケースでWA 何が悪い?
    X, Y = list(map(int, input().split()))

    #implements
    # X*2**n < Y を満たす最大のnは？
    # n < log(y/x, 2)
    getcontext().prec = 28
    n = Decimal(math.log(Decimal(Y/X), 2))
    if n == int(n):
        n = int(n)
    else:
        n = math.floor(n)
    print(n+1)


if __name__ == "__main__":
    main()
