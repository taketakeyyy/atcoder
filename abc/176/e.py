# -*- coding:utf-8 -*-

def solve():
    import sys
    import numpy as np

    H, W, M = list(map(int, sys.stdin.readline().split()))
    grid = np.array([[0 for _ in range(W)] for _ in range(H)])
    for _ in range(M):
        h, w = list(map(int, sys.stdin.readline().split()))
        h, w = h-1, w-1
        grid[h][w] = 1

    cols = np.sum(grid, axis=0)  # 列ごとの合計値
    rows = np.sum(grid, axis=1)  # 行ごとの合計値
    print(cols)
    print(rows)
    print("---")

    ans = np.max(cols) + np.max(rows)
    print(np.max(cols))
    print(np.max(rows))
    print("====")
    col_i = np.argmax(cols)
    row_i = np.argmax(rows)
    print(col_i, row_i)

    if grid[row_i][col_i] == 1:
        print(ans-1)
    else:
        print(ans)

def solve2():
    import sys
    import numpy as np

    H, W, M = list(map(int, sys.stdin.readline().split()))
    grid = np.array([[0 for _ in range(W)] for _ in range(H)])
    for _ in range(M):
        h, w = list(map(int, sys.stdin.readline().split()))
        h, w = h-1, w-1
        grid[h][w] = 1

    L = np.zeros((H,W), dtype=int)
    R = np.zeros((H,W), dtype=int)
    U = np.zeros((H,W), dtype=int)
    D = np.zeros((H,W), dtype=int)

    # 自分より左の爆破数を数える（自分は含めない）
    for w in range(W):
        if w == 0:
            L[:, w] = 0
        else:
            L[:, w] = (L[:, w-1]) + grid[:, w-1]

    # 右の爆破数
    for w in range(W-1, -1, -1):
        if w == W-1:
            R[:, w] = 0
        else:
            R[:, w] = (R[:, w+1]) + grid[:, w+1]

    # 上の爆破数
    for h in range(H):
        if h == 0:
            U[h] = 0
        else:
            U[h] = (U[h-1]) + grid[h-1]

    # 下の爆破数
    for h in range(H-1, -1, -1):
        if h == H-1:
            D[h] = 0
        else:
            D[h] = (D[h+1]) + grid[h+1]

    # 答え
    ans = np.max(L+R+U+D+grid)
    print(ans)



if __name__ == "__main__":
    solve2()
