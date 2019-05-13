# -*- coding:utf-8 -*-

"""解説
N//m = N%m = k （kは約数。かつ余り）とすると、

N = mk + k ...(1)
N = k(m+1)

mを消すためにmに関する式に変形すると、
N = mk + k
mk = N-k
m = (N-k)/k
  = N/k - 1

(1)に代入して



これに気づけばOK。あとは全探索。O(√N)

mは、Nの約数で-1したもの。

Nの約数は、高々O(√N)個くらい（なんで？）



(例)
・N=8, m=3のとき
3*2 + 2 = 8
m*k + k = N

・N=8, m=7のとき
7*1 + 1 = 8
m*k + k = N

"""
import math

def solve():
    N = int(input())

    ans = 0
    for i in range(1, math.ceil(N**0.5)):
        if N%i==0 and i < (N//i-1):
            ans += N//i - 1
    print(ans)


if __name__ == "__main__":
    solve()
