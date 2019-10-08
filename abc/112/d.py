# -*- coding:utf-8 -*-

"""
解説動画
https://youtu.be/CURWJ1Dr44A?t=1708
"""

def solve():
    N, M = list(map(int, input().split()))

    # Mの約数をすべて調べる
    divs = set()  # Mの約数を格納する
    n = 1
    while n*n <= M:
        if M%n == 0:
            # nがMの約数ならば
            divs.add(n)
            divs.add(M//n)
        n += 1

    # Mの約数dの中で、M >= d*Nを満たす最大のものが答え
    ans = 0
    for d in divs:
        if M >= d*N:
            ans = max(ans, d)

    print(ans)


def solve2():
    N, M = list(map(int, input().split()))

    # Mの約数をすべて調べる
    divs = set()  # Mの約数を格納する
    n = 1
    while n <= M**(1/2):
        if M%n == 0:
            # nがMの約数ならば
            divs.add(n)
            divs.add(M//n)
        n += 1

    # Mの約数dの中で、M >= d*Nを満たす最大のものが答え
    ans = 0
    for d in divs:
        if M >= d*N:
            ans = max(ans, d)
    print(ans)


if __name__ == "__main__":
    solve2()
