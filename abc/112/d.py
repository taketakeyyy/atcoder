# -*- coding:utf-8 -*-

"""
解説動画
https://youtu.be/CURWJ1Dr44A?t=1708
"""

def solve():
    N, M = list(map(int, input().split()))

    divs = set()  # Mの約数を格納する

    # Mの約数をすべて調べる
    n = 1
    while n*n <= M:
        if M%n == 0:
            # nがMの約数ならば
            divs.add(n)
            divs.add(M//n)
        n += 1

    # Mの約数dの中で、d*N <= Mを満たす最大のものが答え
    ans = 0
    for d in divs:
        if d*N <= M:
            ans = max(ans, d)

    print(ans)


def solve2():
    N, M = list(map(int, input().split()))

    divs = set()

    n = 1
    while n <= M**(1/2):
        if M%n == 0:
            divs.add(n)
            divs.add(M//n)
        n += 1

    ans = 0
    for d in divs:
        if M >= d*N:
            ans = max(ans, d)
    print(ans)


if __name__ == "__main__":
    solve2()
