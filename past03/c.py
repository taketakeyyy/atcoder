# -*- coding:utf-8 -*-


def solve():
    A, R, N = list(map(int, input().split()))
    LARGE = 10**9

    if A > LARGE:
        print("large")
        return
    if R > LARGE:
        print("large")
        return

    r = R
    n = 1
    while True:
        if r > LARGE or r*A > LARGE:
            print("large")
            return

        if n*2 >= (N-1):
            r *= R**(N-1-n)
            if r > LARGE:
                print("large")
                return

            r *= A
            if r > LARGE:
                print("large")
            else:
                print(r)
            return

        r = r*r
        n *= 2


def solve2():
    # AR^{N-1}が10^{9}より大きいか？
    LA = 10**9
    A, R, N = list(map(int, input().split()))

    if R == 1:
        if A > LA:
            print("large")
        else:
            print(A)
        return

    # R>=2のとき、
    # N>=31なら、A=1,R=2が最小の値だが、1*2^{30} > 10^{9} なので、常にLargeになる。
    if N>=31:
        print("large")
    else:
        # 単純に計算する
        v = A * pow(R, N-1)
        if v > LA:
            print("large")
        else:
            print(v)


if __name__ == "__main__":
    solve2()
