# -*- coding:utf-8 -*-
import numpy as np

def solve():
    H, W = list(map(int, input().split()))
    grid = []
    for _ in range(H):
        grid.append(list(input()))
    grid = (np.array(grid) == ".")*1  # ランプが置ける：1, 障害物:0

    L = np.zeros((H,W), dtype=int)
    R = np.zeros((H,W), dtype=int)
    U = np.zeros((H,W), dtype=int)
    D = np.zeros((H,W), dtype=int)

    for i in range(W):
        if i == 0:
            L[:, i] = grid[:, i]
        else:
            L[:, i] = (L[:, i-1] + 1) * grid[:, i]

    for i in range(W-1, -1, -1):
        if i == W-1:
            R[:, i] = grid[:, i]
        else:
            R[:, i] = (R[:, i+1] + 1) * grid[:, i]

    for i in range(H):
        if i == 0:
            U[i, :] = grid[i, :]
        else:
            U[i, :] = (U[i-1, :] + 1) * grid[i, :]
    
    for i in range(H-1, -1, -1):
        if i == H-1:
            D[i, :] = grid[i, :]
        else:
            D[i, :] = (D[i+1, :] + 1) * grid[i, :]
    
    ans = np.max(L+R+U+D-3)
    print(ans)

if __name__ == "__main__":
    solve()
