# -*- coding:utf-8 -*-
from math import factorial

"""考察
・100!ってどのくらい？

100! = 93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000


・6の約数について

6を素因数分解すると、3^1 * 2^1

よって、6の約数の種類は、

3^0 * 2^0 = 1
3^0 * 2^1 = 2
3^1 * 2^0 = 3
3^1 * 2^1 = 6

すなわち、1,2,3,6 の4つ


・つまり約数が75あるとは？

ある数Nを素因数分解したら

N = a1^e1 * a2^e2 * ... * ak^ek

になるとすると、

(e1+1) * (e2+1) * ... * (ek+1) = (約数の個数)

つまり、約数の個数が75ある数とは、

(e1+1) * (e2+1) * ... * (ek+1) = 75 である数のこと。


"""

"""解き方
・解説動画
https://youtu.be/umpChc0eKeM?t=2354

・matsudo840氏
https://atcoder.jp/contests/abc114/submissions/6920128

"""
from collections import defaultdict

def solve():
    N = int(input())

    d = defaultdict(int)

    # N!を素因数分解をする
    for i in range(2, N+1):
        for j in range(2, i):
            while i%j == 0:
                d[j] += 1
                i = i//j
            if i == 1:
                break

    print(d)

    c74, c24, c14, c4, c2 = 0, 0, 0, 0, 0

    for v in d.values():  # vは、素因数の指数部の値
        if v >= 74:
            c74 += 1
        if v >= 24:
            c24 += 1
        if v >= 14:
            c14 += 1
        if v >= 4:
            c4 += 1
        if v >= 2:
            c2 += 1

    # 答え
    ans = 0
    ans += c74
    ans += c24*(c2-1)
    ans += c14*(c4-1)
    ans += c4*(c4-1)//2*(c2-2)
    print(ans)


if __name__ == "__main__":
    solve()
