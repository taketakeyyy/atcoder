# -*- coding:utf-8 -*-
"""解説
https://www.youtube.com/watch?v=L8grWxBlIZ4

PDFに書いてある実装をする。

....#.
..#...
.#..#.

それぞれのマスについて、

・左マスを照らせる個数: L[i][j]
・右マスを照らせる個数: R[i][j]
・上マスを照らせる個数: U[i][j]
・下マスを照らせる個数: D[i][j]

をそれぞれ計算する。

左マスを照らす漸化式L[i][j]は、

・i行j列に障害物がある場合はL[i][j] = 0
・そうでないとき、j=1ならば、L[i][j] = 1
・そうでないとき、j>1ならば、L[i][j] = L[i][j-1] + 1

求める答えは、L[i][j]+R[i][j]+U[i][j]+D[i][j]-3 の最大値


計算量はO(HW)。

H,W = 2000なので、O(HW)はO(4*10**6)。 Pythonでこの計算量は無理だろと思って実装を諦めたが、いけるっぽい。認識を改めた。というかPyPyもあるし。

と思ったら普通に無理だった。

numpyを使ったらfor文を一個減らせる。計算量が減ったかどうかは内部処理によるので知らんけどACした。結論：numpyの行列計算は速い。

・参考にした他人のコード
https://atcoder.jp/contests/abc129/submissions/5861992

"""
import numpy as np

def solve():
    H, W = list(map(int, input().split()))
    grid = []
    for i in range(H):
        grid.append(list(input()))
    grid = (np.array(grid) == ".") * 1  # ランプをおける:1, 障害物:0

    L = np.zeros((H,W), dtype=int)
    R = np.zeros((H,W), dtype=int)
    U = np.zeros((H,W), dtype=int)
    D = np.zeros((H,W), dtype=int)
    
    for j in range(W):
        if j == 0:
            L[:, j] = grid[:, j]
        else:
            L[:, j] = (L[:, j-1] + 1) * grid[:, j]
    
    for j in range(W-1, -1, -1):
        if j == W-1:
            R[:, j] = grid[:, j]
        else:
            R[:, j] = (R[:, j+1] + 1) * grid[:, j]

    for i in range(H):
        if i == 0:
            U[i] = grid[i] * 1
        else:
            U[i] = (U[i-1] + 1) * grid[i]
    
    for i in range(H-1, -1, -1):
        if i == H-1:
            D[i] = grid[i]
        else:
            D[i] = (D[i+1] + 1) * grid[i]

    ans = np.max(L+R+U+D-3)
    print(ans)


if __name__ == "__main__":
    solve()
