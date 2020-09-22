# -*- coding:utf-8 -*-
"""解説
GCD, DP, 累積和

「一つを選んで好きな数字に変えられる」とあるが、今回のケースでは「その数字を消す」と同じ。

すべてのGCDを試す

4 6 7 8 10 12 14

という数列が与えられたとき、

・4を消して、ほかの数字のGCDを計算

6 7 8 10 12 14

・6を消して、ほかの数字のGCDを計算

4 7 8 10 12 14

・7を消して、……

というのを全列挙するが、N=10**5なので、O(N**2)では計算が間に合わない。

なのでこれをもう少し高速でやりたい。

GCDは計算順序を問わない性質を利用する。

たとえば、8を消した場合

4 6 7 8 10 12 14
| 左 |× |   右  |

・左のGCD(4 6 7)
・右のGCD(10 12 14)
を計算し、GCD(左のGCD, 右のGCD)をやってもよい。

・左のGCDを考える
GCD(4) = L[1]
GCD(4 6) = L[2] = GCD(L[1], 6)
GCD(4 6 7) = L[3] = GCD(L[2], 7)
GCD(4 6 7 8) = L[4] = GCD(L[3], 8)
GCD(4 6 7 8 10) = L[5] = GCD(L[4], 10)

みたいな感じで計算できる。

・右のGCDについても同様に計算してやる。

この前計算ができたら、あとは累積和のように、どの数字を削除したときがGCDが最大になるのかを計算する。

"""
import copy

def solve():
    N = int(input())
    A = list(map(int, input().split()))

    def gcd(x, y):
        """ 最大公約数を求める """
        # x > y にしたい
        if y > x:
            x, y = y, x
        if y == 0:
            return x
        return gcd(x%y, y)

    # L[i] := A[i]が消されたときの左側のGCD
    L = [0]*(N+1)
    L[1] = A[0]
    for i in range(2, N):
        L[i] = gcd(L[i-1], A[i-1])

    # R[i] := A[i]が消されたときの右側のGCD
    R = [0]*(N+1)
    R[N-1] = 0
    R[N-2] = A[N-1]
    for i in range(N-3, -1, -1):
        R[i] = gcd(R[i+1], A[i+1])
    
    # 任意の数字を消したときの最大のGCDを求める
    ans = 0
    for i in range(N):
        tmp = gcd(L[i], R[i])
        ans = max(ans, tmp)

    print(ans)

if __name__ == "__main__":
    solve()
