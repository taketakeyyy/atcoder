# -*- coding:utf-8 -*-
import numpy as np


def solve():
    H, W = list(map(int, input().split()))
    grid = []
    for i in range(H):
        s = input()
        grid.append(list(s))
    grid = (np.array(grid) == ".") * 1  # ランプを置ける:1, 置けない:0

    L = np.zeros((H,W), dtype=int)
    R = np.zeros((H,W), dtype=int)
    U = np.zeros((H,W), dtype=int)
    D = np.zeros((H,W), dtype=int)

    # 左を照らせる数を数える
    for w in range(W):
        if w == 0:
            L[:, w] = grid[:, w]
        else:
            L[:, w] = (L[:, w-1]+1) * grid[:, w]

    # 右
    for w in range(W-1, -1, -1):
        if w == W-1:
            R[:, w] = grid[:, w]
        else:
            R[:, w] = (R[:, w+1]+1) * grid[:, w]

    # 上
    for h in range(H):
        if h == 0:
            U[h] = grid[h]
        else:
            U[h] = (U[h-1]+1) * grid[h]

    # 下
    for h in range(H-1, -1, -1):
        if h == H-1:
            D[h] = grid[h]
        else:
            D[h] = (D[h+1]+1) * grid[h]

    # 答え
    ans = np.max(L+R+U+D-3)
    print(ans)


if __name__ == "__main__":
    solve()
