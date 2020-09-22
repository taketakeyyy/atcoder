# -*- coding:utf-8 -*-

"""解説
http://drken1215.hatenablog.com/entry/2019/05/12/004500

N//m = N%m = k （kは約数。かつ余り）とすると、

N = mk + k
N = k(m+1)

k は MOD m の余りなので、m > k である。
よって、

N = k*(m+1) > k*k

よって、

N > k**2
√N > k

これに気づけばOK。あとはkについて全探索。O(√N)


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
    for k in range(1, math.floor(math.sqrt(N))+1):
        if N%k != 0: continue # kはNの約数より
        # N = k(m+1)
        # m = (N/k) - 1
        m = (N/k) - 1
        if m <= 0: continue
        if N//m == N%m:
            ans += m
    print(int(ans))


if __name__ == "__main__":
    solve()
