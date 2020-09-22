# -*- coding:utf-8 -*-
import itertools

def main():
    """RE"""
    N, X = list(map(int, input().split()))
    xs = list(map(int, input().split()))

    if len(xs) == 1:
        print(abs(xs[0] - X))
        exit()

    low = 0
    high = 10**9+1
    for x in xs:
        if x < X:
            low = max(x, low)
            continue
        if x > X:
            high = min(x, high)
            continue

    Ds = []
    if low != 0: Ds.append(X - low)
    if high != 10**9+1: Ds.append(high - X)
    for d in Ds:
        failed = False
        for x in xs:
            if abs(X-x)%d == 0:
                continue
            else:
                failed = True
                break
        if failed:
            continue
        else:
            print(d)
            exit()
    print(1)


def main2():
    """RE"""
    def gcd(*numbers):
        return reduce(math.gcd, numbers)

    import math
    from functools import reduce
    N, X = list(map(int, input().split()))
    xs = list(map(int, input().split()))

    if len(xs) == 1:
        print(abs(xs[0] - X))
        exit()

    diffs = []
    for x in xs:
        diffs.append(abs(x-X))
    print(gcd(*diffs))

def main3():
    """RE"""
    def gcd(*numbers):
        return reduce(math.gcd, numbers)

    import math
    from functools import reduce
    N, X = list(map(int, input().split()))
    xs = list(map(int, input().split()))

    if len(xs) == 1:
        print(abs(xs[0] - X))
        exit()

    xs.append(X)
    xs.sort()
    diffs = []
    for i in range(len(xs)-1):
        diffs.append(xs[i+1] - xs[i])
    print(gcd(*diffs))

def main4():
    import fractions
    N, X = list(map(int, input().split()))
    xs = list(map(int, input().split()))

    diffs = []
    for x in xs:
        diffs.append(abs(X-x))

    if len(diffs) == 1:
        print(diffs[0])
        exit()

    ans = 10**9+1
    for i in range(len(diffs)-1):
        ans = min(fractions.gcd(diffs[i], diffs[i+1]), ans)
    print(ans)

if __name__ == "__main__":
    main4()
