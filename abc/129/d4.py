# -*- coding:utf-8 -*-
import sys
import numpy as np

def solve():
    H, W = list(map(int, sys.stdin.readline().split()))
    grid = []
    for _ in range(H):
        grid.append(list(input()))
    grid = (np.array(grid) == ".")*1  # ランプが置ける:1, 障害物:0

    #print(grid)

    L = np.zeros((H,W), dtype=int)  # 左方向に照らせるマスの数
    R = np.zeros((H,W), dtype=int)  # 右方向に照らせるマスの数
    U = np.zeros((H,W), dtype=int)  # 上方向に照らせるマスの数
    D = np.zeros((H,W), dtype=int)  # 下方向に照らせるマスの数

    # 左方向に照らせるマスの数のDPを埋める
    for i in range(W):
        if i == 0:
            L[:, i] = grid[:, i]
        else:
            L[:, i] = (L[:, i-1] + 1) * grid[:, i]

    # 右方向に照らせるマスの数のDPを埋める
    for i in range(W-1, -1, -1):
        if i == W-1:
            R[:, i] = grid[:, i]
        else:
            R[:, i] = (R[:, i+1] + 1) * grid[:, i]

    # 上方向に照らせるマスの数のDPを埋める
    for i in range(H):
        if i == 0:
            U[i] = grid[i]
        else:
            U[i] = (U[i-1] + 1) * grid[i]

    # 下の方向に照らせるマスの数のDPを埋める
    for i in range(H-1, -1, -1):
        if i == H-1:
            D[i] = grid[i]
        else:
            D[i] = (D[i+1] + 1) * grid[i]

    # 全方向すべてのDPを埋めた。
    # よって、i行j列目に明かりを設置したとき、全方向に照らせるマスの数を格納した ans_grid は、
    ans_grid = L + R + U + D - 3
    ans = np.max(ans_grid)
    print(ans)


if __name__ == "__main__":
    solve()
