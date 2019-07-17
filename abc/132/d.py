# -*- coding:utf-8 -*-
import sys
sys.setrecursionlimit(100000)  # RecursionError対策

"""解説
(1) まず、赤いボールをN-K個一列に並べる

(2) 赤いボールと赤いボールの隙間をi箇所選んで、そこに青いボールをK個置くことを考える

 R R R R R
0 1 2 3 4 5

    この選び方は、(N-K+1)C(i)通り

(3) それぞれの選び方について、青いボールをそれぞれの隙間に何個割り当てるかを考える。
    それぞれ1個以上割り当てる必要があるので、決め方は(K-1)C(i-1)通り。


[入力例1]
B B B R R

・i=1
Bの塊を挿入する位置は、
 R R  |  R R  |  R R
^     |   ^   |     ^
の3通り

で、

Bを分配する場合の数はそれぞれの場合において1通り

よって、3*1 = 3通り


・i=2
 R R  |  R R   |  R R
^ ^   | ^   ^  |   ^ ^
の3通り

で、

Bを分配する場合の数はそれぞれの場合において、

- 少なくとも1個ずつ分配すると、自由におけるBの数は1個
- 2箇所に玉1つを分配する場合の数は
(2)C(1) = 2通り

よって3*2 = 6通り

・i=3
 R R
^ ^ ^
の1通り


[重複組み合わせの考え方]
http://www7b.biglobe.ne.jp/~math-tota/suA/tamahako.htm

B-i個の玉を、区別のできるi個の箱に分ける場合の数みたいな計算をしたい。これは言い換えると、
B-i個の玉と、i-1個の区切りの重複組み合わせ。

・6個の玉を、区別のできる3つの箱に分ける場合の数
6個の玉と、2個のしきりの重複組み合わせ

○○○○|○○| (4,2,0)の場合
|○○|○○○○ (0,2,4)の場合

「8個のオブジェクトのうち、2個を選んでしきりにする」と同じなので、(8)C(2) = 28

"""
from math import factorial

def combination_formula(n, r):
    return factorial(n) // (factorial(r)*factorial(n-r))

def solve():
    N, K = list(map(int, input().split()))
    B, R = K, N-K
    MOD = 10**9+7

    for i in range(1, K+1):
        if R+1-i < 0:
            print(0)
            continue
        
        # R+1から、i個選ぶ
        ans = combination_formula(R+1, i)
        if B-i == 0:
            print(ans%MOD)
            continue
        # B-i個の玉を、区別のできるi個の箱に分ける場合の数みたいな計算をしたい。これは言い換えると、
        # B-i個の玉と、i-1個の区切りの重複組み合わせ。
        if B-i+i-1-(i-1) >= 0:
            ans *= combination_formula(B-i+i-1, i-1)%MOD
        print(ans%MOD)



if __name__ == "__main__":
    solve()
