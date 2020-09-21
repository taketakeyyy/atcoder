# -*- coding:utf-8 -*-

def solve():
    import numpy as np
    N, K = list(map(int, input().split()))
    grid = [[0 for _ in range(2*K)] for __ in range(K)]
    # grid = np.array(grid)

    for _ in range(N):
        x, y, c = input().split()
        x, y = int(x), int(y)
        # 全部Bに変換する
        if c == "W":
            x += K
        # x,yを[0,2K)の範囲に変換する
        x, y = x%(2*K), y%(2*K)
        # [(0,0), (K, 2K))の範囲に変換する。
        # (変換1) (x+K, y+K) -> (x, y)
        # (変換2) (x+K, y) -> (x, y+K)
        if x >= K and y >= K:
            x, y = x-K, y-K
        if x >= K:
            x, y = x-K, y+K
        grid[x][y] += 1  # 希望の位置を+1にする

    # 2次元累積和rを作る
    r = [[0 for _ in range(2*K+1)] for __ in range(K+1)]
    r[1][1] = grid[0][0]
    for x in range(1, K):
        r[x+1][0] = r[x][0] + grid[x][0]
    for y in range(1, 2*K):
        r[0][y+1] = r[0][y] + grid[0][y]

    for x in range(1, K):
        for y in range(1, 2*K):
            r[x+1][y+1] = r[x+1][y] + r[x][y+1] - r[x][y] + grid[x][y]

    def calc(x1, y1, x2, y2):
        """[(x1,y1), (x2,y2)]の範囲の累積和を返す"""
        return r[x2+1][y2+1] - r[x2+1][y1] - r[x1][y2+1] + r[x1][y1]

    # 答えを探索する
    ans = 0
    for x in range(K):
        for y in range(2*K):
            total = 0
            if y+K >= 2*K and x+K >= 2*K:
                # xとyが境界をまたぐとき
                x1, y1 = x, y
                x2, y2 = 2*K-1, 2*K-1
                total += calc(x1, y1, x2, y2)

            elif y+K >= 2*K:
                # yのみが境界をまたぐとき
                x1, y1 = x, y
                x2, y2 = x+K


if __name__ == "__main__":
    solve()
