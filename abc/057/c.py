# -*- coding:utf-8 -*-

"""考え方
[入力例１]
10000

N = A * B より

A=10000, B=1
A=5000, B=2
A=2500, B=4
A=1250, B=8
A=1000, B=10
A=500, B=20
A=250, B=40
A=200, B=50
A=125, B=80
A=100, B=100
A=50, B=200  <-- ここまで来ると、Bの桁数が大きくなるいっぽうなので、最小値が更新されることはもうない
...

つまり、i = 1 ~ √N までを全探索しても、N<=10**10なので、計算量は高々10**5 これは間に合う。

"""
import math

def F(A, B):
    """ 10進表記における、Aの桁数とBの桁数のうち大きい方を返す """
    def keta(n):
        """ 桁数を求める """
        ans = 1
        while True:
            n = n // 10
            if n == 0:
                break
            ans += 1
        return ans
    
    return max(keta(A), keta(B))
    

def solve():
    N = int(input())
    ans = float("inf")

    for i in range(1, math.ceil(math.sqrt(N))+1):
        A = i
        if N%A != 0: continue
        B = int(N/A)

        ans = min(ans, F(A, B))

    print(ans)

if __name__ == "__main__":
    solve()
